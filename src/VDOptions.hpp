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

#ifndef VORILON_VDOPTIONS_HPP_
#define VORILON_VDOPTIONS_HPP_
#include <boost/program_options.hpp>
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
namespace po = boost::program_options;

namespace Vorilon{
	typedef std::pair<std::string, std::string> KeyValueEntry_t;
	
	//Config Data, manages a Configuration file as well as user switches
	//on the program
	class VDOptions {
	public:
		VDOptions();
		virtual ~VDOptions();
		void ReadData(int*, char*[]);
					
	private:
		po::options_description cmdline_options;
		po::options_description config_options;
		std::string CFile;
		std::list<fs::path> CFPaths;
		
		
		//fs::path CheckForConf();
		//fs::path CheckForConf(std::string);
		
		void GeneralOptions();
		//void ReadConfigFile(std::string);
		//void LoadConfigFile(fs::path);
	};
}




#endif /* VORILON_VDOPTIONS_HPP_ */
