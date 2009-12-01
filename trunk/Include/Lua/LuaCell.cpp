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
#include "LuaCell.h"
#include <cstdio>
#include <stdarg.h>
#include <assert.h>
#include <cstring>

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
//format： callLua_Function("GetTime", "fis>ii", 1.0f, 2, "3", *int, *int);
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
			*va_arg(v1, double *) = lua_tonumber(m_LuaState, nres);
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
//if success return true
bool LuaCell::InputLuaFile(const char* path)
{
	if (luaL_loadfile(m_LuaState, path) || lua_pcall(m_LuaState, 0, 0, 0)) return false;
	return true;
}

// int LuaCell::getLua_Int(const char* variable)
// {
// 	lua_getglobal(m_LuaState, variable);
// 	int result = lua_tointeger(m_LuaState, -1);
// 	lua_pop(m_LuaState, 1);
// 	return result;
// }

//format： getLua_Int("is", 2, "3");
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
		case 's':
			lua_pushstring(m_LuaState, va_arg(v1, char*));
			lua_gettable(m_LuaState, -2);
			break;
		case 'i':
			lua_pushinteger(m_LuaState, va_arg(v1, int));
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
	int result = lua_tointeger(m_LuaState, -1);
	lua_pop(m_LuaState, narg);
	return result;
}

double LuaCell::getLua_Double( const char* signString, ... )
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
	double result = lua_tonumber(m_LuaState, -1);
	lua_pop(m_LuaState, narg);
	return result;
}

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
	const char* result = lua_tostring(m_LuaState, -1);
	lua_pop(m_LuaState, narg);
	return result;
}

void LuaCell::setLua_Int(const char* variable, int result)
{
	lua_pushinteger(m_LuaState, result);
	lua_setglobal(m_LuaState, variable);
}
//從 table1\table2\table3\varableName 這樣的路徑中得到資料的函數
int LuaCell::getLua_Int( const char* pathString )
{
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	int result;
	for (pos = pathString;pos != '\0';pos++)
	{
		if (*pos == '\\' || *pos == '//')
		{
			++pathLayer;
			*target = '\0';
			lua_pushstring(m_LuaState, path);
			lua_gettable(m_LuaState, -2);
			memset(path,0,sizeof(path));
			target = path;
		}
		else if (*pos == '\0')
		{
			++pathLayer;
			lua_pushstring(m_LuaState, path);
			result = lua_tointeger(m_LuaState, -1);
		}
		else
		{
			*target = *pos;
			++target;
		}
	}
	lua_pop(m_LuaState, pathLayer);
	return result;
}

double LuaCell::getLua_Double( const char* pathString )
{
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	double result;
	for (pos = pathString;pos != '\0';pos++)
	{
		if (*pos == '\\' || *pos == '//')
		{
			++pathLayer;
			*target = '\0';
			lua_pushstring(m_LuaState, path);
			lua_gettable(m_LuaState, -2);
			memset(path,0,sizeof(path));
			target = path;
		}
		else if (*pos == '\0')
		{
			++pathLayer;
			lua_pushstring(m_LuaState, path);
			result = lua_tonumber(m_LuaState, -1);
		}
		else
		{
			*target = *pos;
			++target;
		}
	}
	lua_pop(m_LuaState, pathLayer);
	return result;
}

const char* LuaCell::getLua_CharPtr( const char* pathString )
{
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = pathString;pos != '\0';pos++)
	{
		if (*pos == '\\' || *pos == '//')
		{
			++pathLayer;
			*target = '\0';
			lua_pushstring(m_LuaState, path);
			lua_gettable(m_LuaState, -2);
			memset(path,0,sizeof(path));
			target = path;
		}
		else if (*pos == '\0')
		{
			++pathLayer;
			lua_pushstring(m_LuaState, path);
			const char* result = lua_tostring(m_LuaState, -1);
			lua_pop(m_LuaState, pathLayer);
			return result;
		}
		else
		{
			*target = *pos;
			++target;
		}
	}
	return NULL;
}

void LuaCell::setLua_Int( const char* pathString, int data, ... )
{
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = pathString; pos != '\0';pos++)
	{
		if (*pos == '\\' || *pos == '//')
		{
			++pathLayer;
			*target = '\0';
			lua_pushstring(m_LuaState, path);
			lua_gettable(m_LuaState, -2);
			memset(path,0,sizeof(path));
			target = path;
		}
		else if (*pos == '\0')
		{
			++pathLayer;			
			lua_pushinteger(m_LuaState, data);
			lua_setfield(m_LuaState, -2, path);
			lua_pop(m_LuaState, pathLayer);
		}
		else
		{
			*target = *pos;
			++target;
		}
	}
}
void LuaCell::setLua_Double(const char* variable, float result)
{
	lua_pushnumber(m_LuaState, result);
	lua_setglobal(m_LuaState, variable);
}

void LuaCell::setLua_Double( const char* pathString, float data, ... )
{
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = pathString; pos != '\0';pos++)
	{
		if (*pos == '\\' || *pos == '//')
		{
			++pathLayer;
			*target = '\0';
			lua_pushstring(m_LuaState, path);
			lua_gettable(m_LuaState, -2);
			memset(path,0,sizeof(path));
			target = path;
		}
		else if (*pos == '\0')
		{
			++pathLayer;			
			lua_pushnumber(m_LuaState, data);
			lua_setfield(m_LuaState, -2, path);
			lua_pop(m_LuaState, pathLayer);
		}
		else
		{
			*target = *pos;
			++target;
		}
	}
}
void LuaCell::setLua_CharPtr( const char* variable, const char* result )
{
	lua_pushstring(m_LuaState, result);
	lua_setglobal(m_LuaState, variable);
}

void LuaCell::setLua_CharPtr( const char* pathString, const char* data, ... )
{
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = pathString; pos != '\0';pos++)
	{
		if (*pos == '\\' || *pos == '//')
		{
			++pathLayer;
			*target = '\0';
			lua_pushstring(m_LuaState, path);
			lua_gettable(m_LuaState, -2);
			memset(path,0,sizeof(path));
			target = path;
		}
		else if (*pos == '\0')
		{
			++pathLayer;		
			lua_pushstring(m_LuaState, data);
			lua_setfield(m_LuaState, -2, path);
			lua_pop(m_LuaState, pathLayer);
		}
		else
		{
			*target = *pos;
			++target;
		}
	}
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
