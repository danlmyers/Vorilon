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

#include <boost/exception/all.hpp>
#include <stdexcept>
#include <errno.h>
#include <iostream>
#include "ConfigData.h"
#include "ServerData.h"
#include "ErrorHandle.h"
#include "DebugHandle.h"

namespace VR = Vorilon;
int main(int argc, char* argv[]){
	try{
		VR::ServerData sData;
		VR::ConfigData ConD(&sData);
		ConD.ReadData();
		throw VR::Error::general_error() << VR::Error::errno_info(2);
	}
	catch (boost::exception & e) {
		VR::Debug::ConsoleMsg("Boost Error");
		VR::Debug::ConsoleMsg(diagnostic_information(e));
	}
	
	return 0;
}