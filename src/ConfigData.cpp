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

#include "ConfigData.hpp"

namespace Vorilon{
	ConfigData::ConfigData(ServerData *servD){
		sData = *servD;
		
		//Paths to Config File and Config file name
		CFile = "vorilond.conf";
		
		//While in Debug mode also look for a config in the sources/server folder
		//Cause im lazy and I don't want to copy the config file while loading up
		//Vorilond for testing everytime I wipe out the cmake files
#if DEBUG
		CFPaths.push_back(VORILOND_DEBUGCONFPATH + CFile);
#endif /*DEBUG*/
		CFPaths.push_back("./" + CFile);
		CFPaths.push_back("~/.vorilond/" + CFile);
		CFPaths.push_back("/etc/" + CFile);
	}

	ConfigData::~ConfigData(){}

	void ConfigData::ReadData(){
		try{
			LoadConfigFile(CheckForConf());
		}
		catch (Error::File_Not_Found & e){
			if (std::string *file=boost::get_error_info<Error::file_name_info>(e)){
				std::cerr << *file << std::endl;
			}

			Log::Msg(diagnostic_information(e));
			BOOST_THROW_EXCEPTION(Error::Exit_Command());
		}


		//Load Values from config file into ServerData
		//TODO Error Checking!
		sData.Port(boost::lexical_cast<unsigned short>(KeyValue.find("port")->second));
		Log::Msg("Config Port: " + boost::lexical_cast<std::string>(sData.Port()));
	}
	
	fs::path ConfigData::CheckForConf(){
		BOOST_FOREACH(fs::path path, CFPaths){
			if(fs::exists(path)){
				Log::Msg("Config file found: " + path.string());
				return path;
			}
		}

		//If we made it this far, then the config file wasn't found at all.
		BOOST_THROW_EXCEPTION(Error::File_Not_Found() << Error::file_name_info("vorilond.conf Not found"));
		return NULL;
	}

	fs::path ConfigData::CheckForConf(std::string conf){
		fs::path tmpPath = conf;
		if(fs::exists(tmpPath)){
			Log::Msg("Config file found: " + tmpPath.string());
			return tmpPath;
		}else{
			BOOST_THROW_EXCEPTION(Error::File_Not_Found() << Error::file_name_info("vorilond.conf Not Found"));
		}
		return NULL;
	}

	void ConfigData::LoadConfigFile(fs::path ConfFile){
		//At this point we know there is a Config File, but we need some error handling
		//TODO Error Checking
		std::string cfline;
		fs::ifstream cFin(ConfFile);
		while(getline(cFin, cfline)){
			ReadConfigFile(cfline);
		}
		cFin.close();
	}

	void ConfigData::ReadConfigFile(std::string cfline){
		if(cfline[0] == '#' || cfline == "/n"){
			return;
		}
		int pos = cfline.find("=");
		std::string Key = cfline.substr(0,pos);
		std::string Value = cfline.substr(++pos);
		KeyValue.insert(KeyValueEntry_t (Key,Value));
	}
}
