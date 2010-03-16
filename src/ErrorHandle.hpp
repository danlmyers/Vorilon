/*This file is part of Vorilon
 * Copyright (C) 2009,2010  Daniel Myers dan<at>moird.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#ifndef VORILON_ERRORHANDLE_HPP_
#define VORILON_ERRORHANDLE_HPP_
#include <boost/exception/all.hpp>
#include <errno.h>
#include <stdexcept>
#include <string>

//Vorilon's Specific exception/error handling
namespace Vorilon {
	namespace Error {
		
		//Additional Error Information
		typedef boost::error_info<struct tag_errno,int> errno_info; //General information
		typedef boost::error_info<struct tag_function,std::string> function_info; //Name of the Function
		typedef boost::error_info<struct tag_file_name,std::string> file_name_info; //The file name of a failed file operator
		
		//Error identifiers
		struct General : virtual boost::exception, virtual std::exception { };
		struct Variable : virtual General{};
		struct Exit_Command : virtual General{};
		struct File_Not_Found : virtual General{};
		struct File_IO : virtual General{};
		
	}
}




#endif /* VORILON_ERRORHANDLE_HPP_ */
