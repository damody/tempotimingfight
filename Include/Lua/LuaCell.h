/*
Copyright (C) 2009  遊戲天亮界

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
/*本類別僅對lua做簡單包裝，且不做任何的錯誤處理，請自行用下列三個函數來檢測
bool checkLua_ValueIsNil(const char* variable);
bool checkLua_TableValueIsNil(const char* table, const char* variable);
bool checkLua_TableTableValueIsNil(const char* table1, const char* table2, const char* variable);
下一版的table改成傳入"table1/table2/table3","name" 左斜或右斜都可以
本類別最多只可操作兩層的table。
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

