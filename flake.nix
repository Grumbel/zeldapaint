{
  description = "Very simple tile editor";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        packages = rec {
          default = zeldapaint;

          zeldapaint = pkgs.stdenv.mkDerivation {
            pname = "zeldapaint";
            version = "0.0.0";

            src = ./.;

            enableParallelBuilding = true;

            nativeBuildInputs = with pkgs; [
              cmake
              pkg-config
            ];

            buildInputs = with pkgs; [
              allegro4
            ];
           };
        };
      }
    );
}
