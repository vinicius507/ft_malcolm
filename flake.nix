{
  inputs = {
    nixpkgs.url = "nixpkgs";
    libft = {
      url = "github:vinicius507/libft";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = {
    self,
    nixpkgs,
    libft,
  }: let
    allSystems = [
      "x86_64-linux"
      "aarch64-linux"
    ];
    forEachSystem = f:
      nixpkgs.lib.genAttrs allSystems (system:
        f {
          pkgs = import nixpkgs {
            inherit system;
            overlays = [
              libft.overlays.libft
              libft.overlays.devshell
              self.overlays.ft_malcolm
              self.overlays.minunit
            ];
          };
        });
  in {
    checks = forEachSystem ({pkgs}: {
      tests = import ./nix/checks/tests.nix {
        inherit (pkgs) stdenv libft minunit;
      };
    });
    packages = forEachSystem ({pkgs}: {
      default = self.packages.${pkgs.system}.ft_malcolm;
      ft_malcolm = import ./nix/pkgs/ft_malcolm.nix {
        inherit (pkgs) lib libft;
        inherit (pkgs.llvmPackages_12) stdenv;
      };
      minunit = import ./nix/pkgs/minunit.nix {
        inherit (pkgs) lib fetchFromGitHub;
        stdenv = pkgs.stdenvNoCC;
      };
    });
    overlays = {
      ft_malcolm = final: _: {
        ft_malcolm = self.packages.${final.system}.ft_malcolm;
      };
      minunit = final: _: {
        minunit = self.packages.${final.system}.minunit;
      };
    };
    devShells = forEachSystem ({pkgs}: {
      default = pkgs.mkShell {
        packages = with pkgs; [
          bear
          clang-tools_12
          gnumake
          minunit
          norminette
          valgrind
          pkgs.libft
        ];
      };
    });
  };
}
