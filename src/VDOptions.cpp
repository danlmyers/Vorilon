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
	VDOptions::VDOptions(ServerData *servD){
		sData = *servD;
		
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

	void VDOptions::generaloptions(){
		po::options_description generic("General Options");
		generic.add_options()
			("version,v", "Print version for Vorilond")
			("help,h", "Print this help message")
			("config,c", po::value<std::string>(&CFile)->default_value("vorilond.conf"), "Name of a vorilond configuration file")
			;
		po::options_description config("Config File Options");
		config.add_options()
		("port", po::value(boost::lexical_cast<unsigned short>(sData.Port()))->default_value(52000), "Port that Vorilond listens on.")
		;
		
	}
	
	void VDOptions::ReadData(){
		try{
			LoadConfigFile(CheckForConf());
		}
		catch (Error::File_Not_Found & e){
			if (std::string *file=boost::get_error_info<Error::file_name_info>(e)){
				Log::Msg(Log::ERROR, *file);
			}
			
			Log::Msg(Log::DEBUG, diagnostic_information(e));
			BOOST_THROW_EXCEPTION(Error::Exit_Command());
		}


		//Load Values from config file into ServerData
		//TODO Error Checking!
		sData.Port(boost::lexical_cast<unsigned short>(KeyValue.find("port")->second));
		Log::Msg(Log::INFO, "Config Port: " + boost::lexical_cast<std::string>(sData.Port()));
	}
	
	fs::path VDOptions::CheckForConf(){
		BOOST_FOREACH(fs::path path, CFPaths){
			if(fs::exists(path)){
				Log::Msg(Log::INFO, "Config file found: " + path.string());
				return path;
			}
		}

		//If we made it this far, then the config file wasn't found at all.
		BOOST_THROW_EXCEPTION(Error::File_Not_Found() << Error::file_name_info("vorilond.conf Not found"));
		return NULL;
	}

	fs::path VDOptions::CheckForConf(std::string conf){
		fs::path tmpPath = conf;
		if(fs::exists(tmpPath)){
			Log::Msg(Log::INFO, "Config file found: " + tmpPath.string());
			return tmpPath;
		}else{
			BOOST_THROW_EXCEPTION(Error::File_Not_Found() << Error::file_name_info("vorilond.conf Not Found"));
		}
		return NULL;
	}

	void VDOptions::LoadConfigFile(fs::path ConfFile){
		//At this point we know there is a Config File, but we need some error handling
		//TODO Error Checking
		std::string cfline;
		fs::ifstream cFin(ConfFile);
		while(getline(cFin, cfline)){
			ReadConfigFile(cfline);
		}
		cFin.close();
	}

	void VDOptions::ReadConfigFile(std::string cfline){
		if(cfline[0] == '#' || cfline == "/n"){
			return;
		}
		int pos = cfline.find("=");
		std::string Key = cfline.substr(0,pos);
		std::string Value = cfline.substr(++pos);
		KeyValue.insert(KeyValueEntry_t (Key,Value));
	}
}
