/*
Copyright (C) 2009  ¹CÀ¸¤Ñ«G¬É

This program is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FightManger_I19428d04m124428f972bmm7e5f_H
#define FightManger_I19428d04m124428f972bmm7e5f_H
#include "Fight_defines.h"
#include "Scenery.h"
#include <vector>
#include "UI.h"

class FightManger 
{
public:
	/////////////////////////////////////////////////////
	// public associations
	/////////////////////////////////////////////////////
	FightManger();
	
private:
	/////////////////////////////////////////////////////
	// private attributes
	/////////////////////////////////////////////////////
	char m_KeyState[256];
	Role *m_Roles[2];
	std::vector<Skill*> m_Skills;
	Scenery m_Scenery;
	UI m_UI;

};

#endif // FightManger_I19428d04m124428f972bmm7e5f_H

