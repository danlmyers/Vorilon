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

#ifndef VORILON_LOGINT_HPP_
#define VORILON_LOGINT_HPP_
#include <string>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "VDconfig.hpp"
#ifdef HAVE_SYSLOG_H_
#include <syslog.h>
#endif

namespace bt = boost::posix_time;

//Very simple print out messages while in debug mode
namespace Vorilon {
	namespace Log {
	
		enum LOG_LEVEL {
			ERROR,
			WARNING,
			INFO,
			DEBUG
		};
		
		class Msg{
		public:
			Msg(LOG_LEVEL lvl, const std::string& sMsg){
				bt::ptime ct(bt::second_clock::local_time());
				std::string log_str[] = {"Error","Warning","Info","Debug"};
#ifdef DEBUG_MODE
				std::cout << "[" << bt::to_simple_string(ct) << "]" << log_str[lvl] << ": " << sMsg << std::endl;
#endif /* DEBUG_MODE */
			}

			virtual ~Msg(){}
		
		};
	}
}
#endif /* VORILON_LOGINT_HPP_ */
