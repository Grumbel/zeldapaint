{
  description = "Very simple tile editor";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    nix.inputs.nixpkgs.follows = "nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nix, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        packages = flake-utils.lib.flattenTree {
          zeldapaint = pkgs.stdenv.mkDerivation {
            pname = "zeldapaint";
            version = "0.0.0";
            src = nixpkgs.lib.cleanSource ./.;
            enableParallelBuilding = true;
            nativeBuildInputs = [
              pkgs.cmake
              pkgs.pkg-config
            ];
            buildInputs = [
              pkgs.allegro4
            ];
           };
        };
        defaultPackage = packages.zeldapaint;
      });
}
