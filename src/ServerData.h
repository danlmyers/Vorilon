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

#ifndef SERVERDATA_H_
#define SERVERDATA_H_

namespace Vorilon {
	class ServerData{
	public:
		ServerData();
		virtual ~ServerData();
		
		void Port(unsigned short);
		unsigned short Port();
		
	private:
		unsigned short Port_;
	};
}


#endif /* SERVERDATA_H_ */
