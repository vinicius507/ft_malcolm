{
  stdenv,
  libft,
  minunit,
}:
stdenv.mkDerivation {
  name = "tests";
  src = ../../ft_malcolm;
  doCheck = true;
  buildInputs = [
    libft
    minunit
  ];
  buildPhase = ''
    make tests
  '';
  installPhase = ''
    cp ./run_tests $out
  '';
}
