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
		GeneralOptions();
	}

	VDOptions::~VDOptions(){}

	//Setup command line and config file options.
	void VDOptions::GeneralOptions(){
		po::options_description generic("General Options");
		generic.add_options()
			("version,v", "Print version for Vorilond")
			("help,h", "Print this help message")
			("config,c", po::value<std::string>(&cmdCFile), "Name of a vorilond configuration file IE. vorilond.conf")
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
	void VDOptions::ReadData(int argc, char* argv[]){
		
		po::variables_map vm;
		store(po::command_line_parser(argc, argv).options(cmdline_options).run(), vm);
		notify(vm);

		if (vm.count("help")) {
			std::cout << cmdline_options << std::endl;
			BOOST_THROW_EXCEPTION(Error::Exit());
		}
		
		if (vm.count("version")) {
			std::cout << "vorilon version 0" << std::endl;
			BOOST_THROW_EXCEPTION(Error::Exit());
		}
		
		if (vm.count("config")) {
			CFPaths.push_front(cmdCFile);
		}
		
		fs::ifstream cfin(CheckForConf());
		if (!cfin) {
			BOOST_THROW_EXCEPTION(Error::File_IO() << Error::file_name_info("Config file is not Readable"));
		} else {
			store(parse_config_file(cfin, config_options), vm);
			notify(vm);
		}

		
		//Report info on the port number
		Log::Msg(Log::INFO, "Vorilond listening on port: " + boost::lexical_cast<std::string>(ServerData::PORT));
	}
	
	
	//Check for Config file on CFPaths return a string of the path
	fs::path VDOptions::CheckForConf(){
		BOOST_FOREACH(fs::path tmpCFile, CFPaths){
			if (fs::exists(tmpCFile)) {
				Log::Msg(Log::INFO, "Found Config File at: " + tmpCFile.string());
				return tmpCFile;
			}
		}
		//if we have gotten this far then no config file was found
		BOOST_THROW_EXCEPTION(Error::File_Not_Found() << Error::file_name_info("A Proper Config file was not found or specified"));
		return NULL;
		
	}
	
	
}
