# - Try to find Google Log include dirs and libraries
# Copyright (C) 2009  Daniel Myers <dan@moird.com>
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

libfind_package(Glog)

# Include Directory
find_path(Glog_INCLUDE_DIR
	NAMES glog/logging.h
	PATHS ${Glog_PKGCONF_INCLUDE_DIRS})

# Find the Library
find_library(Glog_LIBRARY
	NAMES glog
	PATHS ${Glog_PKGCONF_LIBRARY_DIRS})

# Set the include dir variables and the libraries and let libfind_process do the rest.
set (Glog_PROCESS_INCLUDES Glog_INCLUDE_DIR Glog_INCLUDE_DIRS)
set (Glog_PROCESS_LIBS Glog_LIBRARY Glog_LIBRARIES)
libfind_process(Glog)	
