#This file is part of Vorilon
#Copyright (C) 2009,2010  Daniel Myers dan<at>moird.com
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>

#Source Files
set(VORILOND_SRC vorilond.cpp	LogInt.hpp
	VDOptions.cpp	VDOptions.hpp
	ServerData.cpp	ServerData.hpp
	ErrorHandle.hpp)

#Additional Options
option(DEBUG_MODE "Build Vorilon with Debugging code" ON)

#Check for Syslog.h
check_include_file("syslog.h" HAVE_SYSLOG_H_)

#VDConfig.h Creation
configure_file(${CMAKE_SOURCE_DIR}/src/VDconfig.hpp.cmake
				${CMAKE_BINARY_DIR}/src/VDconfig.hpp)


#Boost Libraries
set(Boost_ADDITIONAL_VERSIONS "1.42" "1.42.0")
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost 1.42 REQUIRED COMPONENTS system regex date_time 
			filesystem program_options)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

#Add Executable
include_directories(${CMAKE_BINARY_DIR}/src)
add_executable ( vorilond ${VORILOND_SRC})
target_link_libraries( vorilond ${LIBS})
