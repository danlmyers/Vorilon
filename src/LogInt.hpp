/*Vorilon is a VOIP Conferencing system
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

#ifndef VORILON_LOGINT_HPP_
#define VORILON_LOGINT_HPP_
#include <string>
#include <iostream>
#include "VDconfig.hpp"
#ifdef HAVE_SYSLOG_H_
#include <syslog.h>
#endif

//Very simple print out messages while in debug mode
namespace Vorilon {
	namespace Log {
		class Msg{
		public:
#ifdef DEBUG
			Msg(const std::string& sMsg){
				std::cout << "Debug: " << sMsg << std::endl;
			}
#else
			Msg(const std::string& sMsg){}
#endif /*DEBUG*/
			virtual ~Msg(){}
		
		};
	}
}
#endif /* VORILON_LOGINT_HPP_ */
