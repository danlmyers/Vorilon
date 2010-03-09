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

#include <iostream>
#include "ConfigData.hpp"
#include "ServerData.hpp"
#include "ErrorHandle.hpp"
#include "LogInt.hpp"

namespace VR = Vorilon;
int main(int argc, char* argv[]){
	try{
		VR::ServerData sData;
		VR::ConfigData ConD(&sData);
		ConD.ReadData();
	}
	catch (VR::Error::Exit_Command & e) {
		VR::Debug::ConsoleMsg("Exit Command");
		VR::Debug::ConsoleMsg(diagnostic_information(e));
		return 0;
	}
	catch (boost::exception & e) {
		VR::Debug::ConsoleMsg("Vorilon Standard Exception");
		VR::Debug::ConsoleMsg(diagnostic_information(e));
	}
	catch (std::exception & e){
		std::cerr << "Vorilon has experienced an error and is now exiting." << std::endl;
		VR::Debug::ConsoleMsg(e.what());
	}
	catch (...){
		std::cerr << "Vorilon as experienced a default unhandled exception and has exited." << std::endl <<
			boost::current_exception_diagnostic_information();
	}
	return 0;
}