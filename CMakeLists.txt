#This file is part of Vorilon
#Copyright (C) 2009,2010  Daniel Myers dan<at>moird.com
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>

#General requirements
cmake_minimum_required(VERSION 2.6)
include (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)

#require Out of source build
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" VORILON_IN_SOURCE)
if(VORILON_IN_SOURCE)
	message(FATAL_ERROR "Vorilon Requires an out of source build.  Please create a separate build directory and run 'cmake path_to_vorilon [options]' there.")
endif(VORILON_IN_SOURCE)

#Main Program Parts
project(Vorilon)
add_subdirectory(src)
