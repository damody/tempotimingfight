//此程式碼屬於 天亮damody,翼光城W.S.C. 及「遊戲天亮界」的遊戲開發團隊的程式師共同所有
#include "LuaCell.h"
#include <cstdio>
#include <stdarg.h>
#include <assert.h>

LuaCell::LuaCell()
{
	m_LuaState = luaL_newstate();
	luaL_openlibs(m_LuaState);
}

LuaCell::~LuaCell()
{
	lua_close(m_LuaState);
}

bool LuaCell::callLua_Function(const char* functionName)
{
	lua_getglobal(m_LuaState, functionName);
	if (lua_isfunction(m_LuaState, -1))
	{
		if (lua_pcall(m_LuaState, 0, 0, 0) != 0)
		{
			return false;
		}
		else
		{
			return true;
		}		
	}
	return false;
}

bool LuaCell::callLua_Function( const char* functionName, const char* signString, ... )
{
	va_list v1;
	int narg, nres;
	va_start(v1, signString);
	lua_getglobal(m_LuaState, functionName);

	for (narg = 0; *signString; narg++)
	{
		luaL_checkstack(m_LuaState, 1, "too many arguments");
		switch (*signString++)
		{
		case 'f':
			lua_pushnumber(m_LuaState, (double)va_arg(v1, float));
			break;
		case 'i':
			lua_pushinteger(m_LuaState, va_arg(v1, int));
			break;
		case 's':
			lua_pushstring(m_LuaState, va_arg(v1, char*));
			break;
		case '>':
			goto emdargs;
		default:
#if _DEBUG
			assert(0 && "callLua_Function args error!");
#endif
			break;
		}
	}
emdargs:
	nres = strlen(signString);
	if (lua_pcall(m_LuaState, narg, nres, 0) != 0)
	{
		return false;
	}

	nres = -nres;
	while (*signString)
	{
		switch (*signString++)
		{
		case 'f':
			*va_arg(v1, float *) = (float)lua_tonumber(m_LuaState, nres);
			break;
		case 'i':
			*va_arg(v1, int *) = lua_tointeger(m_LuaState, nres);
			break;
		case 's':
			*va_arg(v1, const char **) = lua_tostring(m_LuaState, nres);
			break;
		default:
			printf("callLua_Function result args error!\n");
		}
		nres++;
	}

	va_end(v1);
	return true;
}
bool LuaCell::InputLuaFile(const char* path)
{
	if (luaL_loadfile(m_LuaState, path) || lua_pcall(m_LuaState, 0, 0, 0)) return false;
	return true;
}


// int LuaCell::getLua_Int(const char* variable)
// {
// 	lua_getglobal(m_LuaState, variable);
// 	int value = lua_tointeger(m_LuaState, -1);
// 	lua_pop(m_LuaState, 1);
// 	return value;
// }

int LuaCell::getLua_Int( const char* signString, ... )
{
	va_list v1;
	int narg;
	va_start(v1, signString);
	lua_getglobal(m_LuaState, va_arg(v1, char*));
	for (narg = 0; *signString; narg++)
	{
		if (narg == 0)
		{
			*signString++;
			continue;
		}
		switch (*signString++)
		{
		case 'i':
			lua_pushinteger(m_LuaState, va_arg(v1, int));
			lua_gettable(m_LuaState, -2);
			break;
		case 's':
			lua_pushstring(m_LuaState, va_arg(v1, char*));
			lua_gettable(m_LuaState, -2);
			break;
		default:
#ifdef _DEBUG
			assert(0 && "getLua_Int args error!");
#endif
			break;
		}
	}
	va_end(v1);
	int value = lua_tointeger(m_LuaState, -1);
	lua_pop(m_LuaState, narg);
	return value;
}

// float LuaCell::getLua_Float(const char* variable)
// {
// 	lua_getglobal(m_LuaState, variable);
// 	float value = (float)lua_tonumber(m_LuaState, -1);
// 	lua_pop(m_LuaState, 1);
// 	return value;
// }

float LuaCell::getLua_Float( const char* signString, ... )
{
	va_list v1;
	int narg;
	va_start(v1, signString);
	lua_getglobal(m_LuaState, va_arg(v1, char*));
	for (narg = 0; *signString; narg++)
	{
		if (narg == 0)
		{
			*signString++;
			continue;
		}
		switch (*signString++)
		{
		case 'i':
			lua_pushinteger(m_LuaState, va_arg(v1, int));
			lua_gettable(m_LuaState, -2);
			break;
		case 's':
			lua_pushstring(m_LuaState, va_arg(v1, char*));
			lua_gettable(m_LuaState, -2);
			break;
		default:
#ifdef _DEBUG
			assert(0 && "getLua_Int args error!");
#endif
			break;
		}
	}
	va_end(v1);
	float value = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, narg);
	return value;
}

// const char* LuaCell::getLua_CharPtr(const char* variable)
// {
// 	lua_getglobal(m_LuaState, variable);
// 	const char* value = lua_tostring(m_LuaState, -1);
// 	lua_pop(m_LuaState, 1);
// 	return value;
// }

const char* LuaCell::getLua_CharPtr( const char* signString, ... )
{
	va_list v1;
	int narg;
	va_start(v1, signString);
	lua_getglobal(m_LuaState, va_arg(v1, char*));
	for (narg = 0; *signString; narg++)
	{
		if (narg == 0)
		{
			*signString++;
			continue;
		}
		switch (*signString++)
		{
		case 'i':
			lua_pushinteger(m_LuaState, va_arg(v1, int));
			lua_gettable(m_LuaState, -2);
			break;
		case 's':
			lua_pushstring(m_LuaState, va_arg(v1, char*));
			lua_gettable(m_LuaState, -2);
			break;
		default:
#ifdef _DEBUG
			assert(0 && "getLua_Int args error!");
#endif
			break;
		}
	}
	va_end(v1);
	const char* value = lua_tostring(m_LuaState, -1);
	lua_pop(m_LuaState, narg);
	return value;
}

int LuaCell::getLua_TableInt(const char* table, const char* variable)
{
	lua_getglobal(m_LuaState, table);
	// 	if (!lua_istable(m_LuaState,-1)) //錯誤處理
	// 	{
	// 		lua_pop(m_LuaState, 1);
	// 		return NULL;		
	// 	}
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	int value = lua_tointeger(m_LuaState, -1);
	lua_pop(m_LuaState, 2);
	return value;
}

int LuaCell::getLua_TableInt( const char* table, const int variable )
{
	lua_getglobal(m_LuaState, table);
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	int value = lua_tointeger(m_LuaState, -1);
	lua_pop(m_LuaState, 2);
	return value;
}

float LuaCell::getLua_TableFloat(const char* table, const char* variable)
{
	lua_getglobal(m_LuaState, table);
	if (!lua_istable(m_LuaState,-1)) return NULL;
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	float value = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 2);
	return value;
}

float LuaCell::getLua_TableFloat( const char* table, const int variable )
{
	lua_getglobal(m_LuaState, table);
	if (!lua_istable(m_LuaState,-1)) return NULL;
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	float value = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 2);
	return value;
}
const char* LuaCell::getLua_TableCharPtr(const char* table, const char* variable)
{
	lua_getglobal(m_LuaState, table);
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	const char* value = lua_tostring(m_LuaState, -1);
	lua_pop(m_LuaState, 2);
	return value;
}

const char* LuaCell::getLua_TableCharPtr( const char* table, const int variable )
{
	lua_getglobal(m_LuaState, table);
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	const char* value = lua_tostring(m_LuaState, -1);
	lua_pop(m_LuaState, 2);
	return value;
}
int LuaCell::getLua_TableTableInt(const char* table1, const char* table2, const char* variable)
{
	lua_getglobal(m_LuaState, table1);
	// 	if (!lua_istable(m_LuaState,-1)) //錯誤處理
	// 	{
	// 		lua_pop(m_LuaState, 1);
	// 		return NULL;		
	// 	}
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	// 	if (!lua_istable(m_LuaState,-1)) //錯誤處理
	// 	{
	// 		lua_pop(m_LuaState, 1);
	// 		return NULL;		
	// 	}
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	int value = lua_tointeger(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}

int LuaCell::getLua_TableTableInt( const char* table1, const char* table2, const int variable )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	int value = lua_tointeger(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}

int LuaCell::getLua_TableTableInt( const char* table1, const int table2, const char* variable )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushinteger(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	int value = lua_tointeger(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}
float LuaCell::getLua_TableTableFloat(const char* table1, const char* table2, const char* variable)
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	float value = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}

float LuaCell::getLua_TableTableFloat( const char* table1, const char* table2, const int variable )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	float value = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}

float LuaCell::getLua_TableTableFloat( const char* table1, const int table2, const char* variable )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushinteger(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	float value = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}
const char* LuaCell::getLua_TableTableCharPtr(const char* table1, const char* table2, const char* variable)
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	const char* value = lua_tostring(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}

const char* LuaCell::getLua_TableTableCharPtr( const char* table1, const char* table2, const int variable )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	const char* value = lua_tostring(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}

const char* LuaCell::getLua_TableTableCharPtr( const char* table1, const int table2, const char* variable )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushinteger(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	const char* value = lua_tostring(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return value;
}
fRect LuaCell::getLua_TablefRect( const char* table, const char* rect )
{
	lua_getglobal(m_LuaState, table);
	lua_pushstring(m_LuaState, rect);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, "left");
	lua_gettable(m_LuaState, -2);
	fRect result;
	result.left = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "right");
	lua_gettable(m_LuaState, -2);
	result.right = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "top");
	lua_gettable(m_LuaState, -2);
	result.top = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "bottom");
	lua_gettable(m_LuaState, -2);
	result.bottom = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return result;
}

fRect LuaCell::getLua_TableTablefRect( const char* table1, const char* table2, const char* rect )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, rect);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, "left");
	lua_gettable(m_LuaState, -2);
	fRect result;
	result.left = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "right");
	lua_gettable(m_LuaState, -2);
	result.right = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "top");
	lua_gettable(m_LuaState, -2);
	result.top = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "bottom");
	lua_gettable(m_LuaState, -2);
	result.bottom = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 4);
	return result;
}

fRect LuaCell::getLua_TableTablefRect( const char* table1, const int table2, const char* rect )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushinteger(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, rect);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, "left");
	lua_gettable(m_LuaState, -2);
	fRect result;
	result.left = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "right");
	lua_gettable(m_LuaState, -2);
	result.right = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "top");
	lua_gettable(m_LuaState, -2);
	result.top = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "bottom");
	lua_gettable(m_LuaState, -2);
	result.bottom = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 4);
	return result;
}
fRect LuaCell::getLua_fRect( const char* rect )
{
	lua_getglobal(m_LuaState, rect);
	lua_pushstring(m_LuaState, "left");
	lua_gettable(m_LuaState, -2);
	fRect result;
	result.left = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "right");
	lua_gettable(m_LuaState, -2);
	result.right = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "top");
	lua_gettable(m_LuaState, -2);
	result.top = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 1);
	lua_pushstring(m_LuaState, "bottom");
	lua_gettable(m_LuaState, -2);
	result.bottom = (float)lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, 3);
	return result;
}

void LuaCell::setLua_Int(const char* variable, int value)
{
	lua_pushinteger(m_LuaState, value);
	lua_setglobal(m_LuaState, variable);
}

void LuaCell::setLua_Float(const char* variable, float value)
{
	lua_pushnumber(m_LuaState, value);
	lua_setglobal(m_LuaState, variable);
}

void LuaCell::setLua_CharPtr( const char* variable, const char* value )
{
	lua_pushstring(m_LuaState, value);
	lua_setglobal(m_LuaState, variable);
}

void LuaCell::setLua_TableInt( const char* table, const char* variable, int value )
{
	lua_getglobal(m_LuaState, table);
	// 	if (lua_istable(m_LuaState,-1)) //錯誤處理
	// 	{
	lua_pushinteger(m_LuaState, value);
	lua_setfield(m_LuaState, -2, variable);
	lua_pop(m_LuaState, 1);
	// 	}
	// 	lua_pop(m_LuaState, 1);
	// 	return false;
}

void LuaCell::setLua_TableFloat( const char* table, const char* variable, float value )
{
	lua_getglobal(m_LuaState, table);
	lua_pushnumber(m_LuaState, value);
	lua_setfield(m_LuaState, -2, variable);
	lua_pop(m_LuaState, 1);
}

void LuaCell::setLua_TableCharPtr( const char* table, const char* variable, const char* value )
{
	lua_getglobal(m_LuaState, table);
	lua_pushstring(m_LuaState, value);
	lua_setfield(m_LuaState, -2, variable);
	lua_pop(m_LuaState, 1);
}

void LuaCell::setLua_TableTableInt( const char* table1, const char* table2, const char* variable, int value )
{
	lua_getglobal(m_LuaState, table1);
	// 	if (lua_istable(m_LuaState,-1)) //錯誤處理
	// 	{
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	// 		if (lua_istable(m_LuaState,-1))
	// 		{
	lua_pushinteger(m_LuaState, value);
	lua_setfield(m_LuaState, -2, variable);
	lua_pop(m_LuaState, 2);
	// 		}
	// 	}
	// 	lua_pop(m_LuaState, 1);
	// 	return false;
}

void LuaCell::setLua_TableTableFloat( const char* table1, const char* table2, const char* variable, float value )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushnumber(m_LuaState, value);
	lua_setfield(m_LuaState, -2, variable);
	lua_pop(m_LuaState, 2);
}

void LuaCell::setLua_TableTableCharPtr( const char* table1, const char* table2, const char* variable, const char* value )
{
	lua_getglobal(m_LuaState, table1);
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	lua_pushstring(m_LuaState, value);
	lua_setfield(m_LuaState, -2, variable);
	lua_pop(m_LuaState, 2);
}

bool LuaCell::setLua_NewTable(const char* table)
{
	lua_getglobal(m_LuaState, table);
	if (lua_istable(m_LuaState,-1))
	{
		lua_pop(m_LuaState, 1);
		return false;
	}
	else
	{
		lua_newtable(m_LuaState);
		lua_setglobal(m_LuaState, table);
		return true;
	}	
}

bool LuaCell::checkLua_ValueIsNil(const char* variable)
{
	lua_getglobal(m_LuaState, variable);
	bool answer = true;
	if (lua_isnil(m_LuaState, -1))
		answer = true;
	else
		answer = false;
	lua_pop(m_LuaState, 1);
	return answer;
}

bool LuaCell::checkLua_TableValueIsNil(const char* table, const char* variable)
{
	lua_getglobal(m_LuaState, table);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 1);
		return true;		
	}
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	bool answer = true;
	if (lua_isnil(m_LuaState, -1))
		answer = true;
	else
		answer = false;
	lua_pop(m_LuaState, 2);
	return answer;	
}

bool LuaCell::checkLua_TableValueIsNil( const char* table, const int variable )
{
	lua_getglobal(m_LuaState, table);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 1);
		return true;		
	}
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	bool answer = true;
	if (lua_isnil(m_LuaState, -1))
		answer = true;
	else
		answer = false;
	lua_pop(m_LuaState, 2);
	return answer;	
}
bool LuaCell::checkLua_TableTableValueIsNil(const char* table1, const char* table2, const char* variable)
{
	lua_getglobal(m_LuaState, table1);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 1);
		return true;		
	}
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 2);
		return true;		
	}
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	bool answer = true;
	if (lua_isnil(m_LuaState, -1))
		answer = true;
	else
		answer = false;
	lua_pop(m_LuaState, 3);
	return answer;
}

bool LuaCell::checkLua_TableTableValueIsNil( const char* table1, const int table2, const char* variable )
{
	lua_getglobal(m_LuaState, table1);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 1);
		return true;		
	}
	lua_pushinteger(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 2);
		return true;		
	}
	lua_pushstring(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	bool answer = true;
	if (lua_isnil(m_LuaState, -1))
		answer = true;
	else
		answer = false;
	lua_pop(m_LuaState, 3);
	return answer;
}

bool LuaCell::checkLua_TableTableValueIsNil( const char* table1, const char* table2, const int variable )
{
	lua_getglobal(m_LuaState, table1);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 1);
		return true;		
	}
	lua_pushstring(m_LuaState, table2);
	lua_gettable(m_LuaState, -2);
	if (!lua_istable(m_LuaState,-1)) 
	{
		lua_pop(m_LuaState, 2);
		return true;		
	}
	lua_pushinteger(m_LuaState, variable);
	lua_gettable(m_LuaState, -2);
	bool answer = true;
	if (lua_isnil(m_LuaState, -1))
		answer = true;
	else
		answer = false;
	lua_pop(m_LuaState, 3);
	return answer;
}