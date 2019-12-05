;; ZeldaPaint - A simple tile editor
;; Copyright (C) 2019 Ingo Ruhnke <grumbel@gmail.com>
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

(set! %load-path
  (cons* "/ipfs/QmZdLjyRm29uL4Eh4HqkZHvwMMus6zjwQ8EdBtp5JUPT99/guix-cocfree_0.0.0-52-ga8e1798"
         %load-path))

(use-modules (guix build-system cmake)
             (guix gexp)
             (guix git-download)
             ((guix licenses) #:prefix license:)
             (guix packages)
             (gnu packages game-development)
             (gnu packages pkg-config)
             (guix-cocfree utils))

(define %source-dir (dirname (current-filename)))

(define-public zeldapaint
  (package
   (name "zeldapaint")
   (version (version-from-source %source-dir))
   (source (source-from-source %source-dir))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #f))
   (native-inputs
    `(("pkg-config" ,pkg-config)))
   (inputs
    `(("allegro-4" ,allegro-4)))
   (synopsis "Very simple tile editor")
   (description "A very simple tile editor written back in August of
1997 with Allegro. It uses tiles from Zelda: A Links Awakening and
allows the creation of GameBoy-screen sized maps.")
   (home-page "https://gitlab.com/grumbel/zeldapaint")
   (license license:zlib)))

zeldapaint

;; EOF ;;
