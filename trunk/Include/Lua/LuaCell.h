/*
Copyright (C) 2009  �C���ѫG��

This program is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*�����O�ȹ�lua��²��]�ˡA�B�������󪺿��~�B�z�A�Цۦ�ΤU�C�T�Ө�ƨ��˴�
bool checkLua_ValueIsNil(const char* variable);
bool checkLua_TableValueIsNil(const char* table, const char* variable);
bool checkLua_TableTableValueIsNil(const char* table1, const char* table2, const char* variable);
�U�@����table�令�ǤJ"table1/table2/table3","name" ���שΥk�׳��i�H
�����O�̦h�u�i�ާ@��h��table�C
*/
#ifndef LuaCell_Im42c45f58m1233b1a3831mm7e5f_H
#define LuaCell_Im42c45f58m1233b1a3831mm7e5f_H
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#pragma comment(lib, "Include/Lua/lua5.1.lib")

class LuaCell
{
public:
	LuaCell();
	~LuaCell();
	bool callLua_Function(const char* functionName);
	bool callLua_Function(const char* functionName, const char* signString, ...);
	bool InputLuaFile(const char* path);
	int		getLua_Int(const char* signString, ...);
	double		getLua_Double(const char* signString, ...);
	const char*	getLua_CharPtr(const char* signString, ...);
	int		getLua_Int(const char* signString);
	double		getLua_Double(const char* signString);
	const char*	getLua_CharPtr(const char* signString);
	void setLua_Int(const char* variable, int value);
	void setLua_Double(const char* variable, float value);
	void setLua_CharPtr(const char* variable, const char* value);
	void setLua_Int(const char* variable, int value, ...);
	void setLua_Double(const char* variable, float value, ...);
	void setLua_CharPtr(const char* variable, const char* value, ...);
	bool setLua_NewTable(const char* table);
	bool checkLua_ValueIsNil(const char* variable);
	bool checkLua_ValueIsNil(const char* variable, ...);
private:
	lua_State* m_LuaState;
};

#endif // LuaCell_Im42c45f58m1233b1a3831mm7e5f_H

