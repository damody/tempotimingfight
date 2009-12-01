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
#ifndef Role_I19428d04m124428f972bmm7e46_H
#define Role_I19428d04m124428f972bmm7e46_H

#include "Fight_defines.h"
#include <vector>
#include "../Include/Lua/LuaCell.h"
#include "../Include/Win32/ConvertType.h"

class Role 
{
public:
	Role();
	Role(const wchar_t* luaFilePate);
	void Update();
	void Render();
private:
	LuaCell m_LuaRole;
};

#endif // Role_I19428d04m124428f972bmm7e46_H

