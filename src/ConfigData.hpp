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

#ifndef CONFIGDATA_H_
#define CONFIGDATA_H_
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <list>
#include <iostream>
#include <map>
#include "ServerData.hpp"
#include "LogInt.hpp"
#include "ErrorHandle.hpp"
#include "VDconfig.hpp"

namespace fs = boost::filesystem;

namespace Vorilon{
	typedef std::pair<std::string, std::string> KeyValueEntry_t;
	
	//Config Data, manages a Configuration file as well as user switches
	//on the program
	class ConfigData {
	public:
		ConfigData(ServerData*);
		virtual ~ConfigData();
		void ReadData();
					
	private:
		std::string CFile;
		std::list<fs::path> CFPaths;
		ServerData sData;
		
		std::map<std::string, std::string> KeyValue;
		
		fs::path CheckForConf();
		fs::path CheckForConf(std::string);
		void ReadConfigFile(std::string);
		void LoadConfigFile(fs::path);
	};
}




#endif /* CONFIGDATA_H_ */
