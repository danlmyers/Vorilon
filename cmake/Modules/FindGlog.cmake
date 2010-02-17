# Copyright (C) 2009  Daniel Myers <dan@moird.com>
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
# along with this program.  If not, see <http://www.gnu.org/licenses/>
#
# Try to find Google Logging (glog)
# This will define:
# GLOG_FOUND - system has glog
# GLOG_INCLUDE_DIRS - The Glog include directories
# GLOG_LIBRARIES - link libraries
#
# See documentation on how to write CMake scripts at
# http://www.cmake.org/Wiki/Cmake:How_To_Find_Libraries

include (LibFindMacros)

libfind_pkg_check_modules(GLOG_PKGCONF glog)

# Include Directory
find_path(GLOG_INCLUDE_DIR
	NAMES glog/logging.h
	PATHS ${GLOG_PKGCONF_INCLUDE_DIRS})

# Find the Library
find_library(GLOG_LIBRARY
	NAMES glog
	PATHS ${GLOG_PKGCONF_LIBRARY_DIRS})

# Set the include dir variables and the libraries and let libfind_process do the rest.
set (Glog_PROCESS_INCLUDES Glog_INCLUDE_DIR Glog_INCLUDE_DIRS)
set (Glog_PROCESS_LIBS Glog_LIBRARY Glog_LIBRARIES)
libfind_process(Glog)	
