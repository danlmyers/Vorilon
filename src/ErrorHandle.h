/*Vorilon is a VOIP Conferencing system
 * Copyright (C) 2009  Daniel Myers <dan@moird.com>
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
#ifndef ERRORHANDLE_H_
#define ERRORHANDLE_H_
#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp>
#include <errno.h>
#include <string>
#include <iostream>

//Vorilon's Specific exception/error handling
namespace Vorilon {
	namespace Error {
		
		typedef boost::error_info<struct tag_errno,int> errno_info; //General information
		typedef boost::error_info<struct tag_function,std::string> function_info; //Name of the Function
		typedef boost::error_info<struct tag_file_name,std::string> file_name_info; //The file name of a failed file operator
		
		class error_ : public std::exception, boost::exception {
		public:
			char const * what() const throw(){
				return "Vorilon Standard Error";
			}
			
		protected:
			~error_() throw(){}
		};
		
		class general_error_ : public error_{};
		class variable_error : public general_error_{};
		
		
		class Msg{
		public:
			Msg(boost::exception const & x){
				std::cout << "------------------------------------------------------" << std::endl;
				file_info(x);
				clib_info(x);
				std::cout << std::endl << "Diagnostic Info: " << std::endl;
				std::cout << diagnostic_information(x);
			}
			virtual ~Msg(){}
			
		private:
			void file_info(boost::exception const & x){
				if( boost::shared_ptr<std::string const> fn = boost::get_error_info<file_name_info>(x) )
					std::cout << "File Name: " << *fn << std::endl;
			}
			
			void clib_info(boost::exception const & x){
				if( boost::shared_ptr<int const> err=boost::get_error_info<errno_info>(x))
					std::cout << "OS Error: " << *err << std::endl;
				if( boost::shared_ptr<std::string const> fn=boost::get_error_info<function_info>(x))
					std::cout << "Failed Function: " << *fn << std::endl;
			}
		};
	}
}




#endif /* ERRORHANDLE_H_ */