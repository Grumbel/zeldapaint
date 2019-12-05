# ZeldaPaint - A simple tile editor
# Copyright (C) 2019 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.6)
project(zeldapaint VERSION 0.1.0)

include(GNUInstallDirs)

# configure
find_package(PkgConfig REQUIRED)
pkg_search_module(ALLEGRO REQUIRED allegro IMPORTED_TARGET)

# build
add_executable(zeldapaint src/zeldapnt.c src/zelda.c)
target_link_libraries(zeldapaint PkgConfig::ALLEGRO)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/zeldapaint.sh.in
  ${CMAKE_BINARY_DIR}/zeldapaint.sh)

file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

# install
install(TARGETS zeldapaint
  RUNTIME DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})

install(PROGRAMS
  ${CMAKE_BINARY_DIR}/zeldapaint.sh
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RENAME zeldapaint)

install(DIRECTORY ${CMAKE_BINARY_DIR}/data/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

# EOF #
