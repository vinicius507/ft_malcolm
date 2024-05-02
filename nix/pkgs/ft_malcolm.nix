{
  lib,
  stdenv,
  libft,
}:
stdenv.mkDerivation {
  pname = "ft_malcolm";
  version = "0.1.0";
  src = ../../ft_malcolm;
  buildInputs = [
    libft
  ];
  installPhase = ''
    mkdir -p $out/bin
    cp ft_malcolm $out/bin
  '';
  meta = with lib; {
    license = licenses.agpl3;
    mainProgram = "ft_malcolm";
  };
}
