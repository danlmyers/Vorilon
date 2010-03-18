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

#include "VDOptions.hpp"

namespace Vorilon{
	VDOptions::VDOptions(){
		
		//Paths to Config File and Config file name
		CFile = "vorilond.conf";
		
		//While in Debug mode also look for a config in the sources/server folder
		//Cause im lazy and I don't want to copy the config file while loading up
		//Vorilond for testing everytime I wipe out the cmake files
#if DEBUG_MODE
		CFPaths.push_back(VORILOND_DEBUGCONFPATH + CFile);
#endif /*DEBUG_MODE*/
		CFPaths.push_back("./" + CFile);
		CFPaths.push_back("~/.vorilond/" + CFile);
		CFPaths.push_back("/etc/" + CFile);
		
	}

	VDOptions::~VDOptions(){}

	//Setup command line and config file options.
	void VDOptions::GeneralOptions(){
		po::options_description generic("General Options");
		generic.add_options()
			("version,v", "Print version for Vorilond")
			("help,h", "Print this help message")
			("config,c", po::value<std::string>(&CFile)->default_value("vorilond.conf"), "Name of a vorilond configuration file")
			;
		po::options_description config("Config File Options");
		config.add_options()
			("port", po::value<unsigned short>(&ServerData::PORT)->default_value(52000), "Port that Vorilond listens on. Default: 52000")
			;
		
		//command line options will accept generic commands and all config file commands
		cmdline_options.add(generic).add(config);
		
		//config file processing will only accept config file options
		config_options.add(config);
	}
	
	//Process the command line and config file
	void VDOptions::ReadData(int* argc, char* argv[]){
		


		//Load Values from config file into ServerData
		Log::Msg(Log::INFO, "Config Port: " + boost::lexical_cast<std::string>(ServerData::PORT));
	}
	
	
}
