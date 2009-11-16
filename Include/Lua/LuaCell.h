//���{���X�ݩ� �ѫGdamody,�l����W.S.C. �Ρu�C���ѫG�ɡv���C���}�o�ζ����{���v�@�P�Ҧ�
/*�����O�ȹ�lua��²��]�ˡA�B�������󪺿��~�B�z�A�Цۦ�ΤU�C�T�Ө�ƨ��˴�
bool checkLua_ValueIsNil(const char* variable);
bool checkLua_TableValueIsNil(const char* table, const char* variable);
bool checkLua_TableTableValueIsNil(const char* table1, const char* table2, const char* variable);
�����O�̦h�u�i�ާ@��h��table�C
*/
#ifndef LuaCell_Im42c45f58m1233b1a3831mm7e5f_H
#define LuaCell_Im42c45f58m1233b1a3831mm7e5f_H
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#pragma comment(lib, "Include/Lua/lua5.1.lib")
#include "..\DX9\DateType.h"

class LuaCell
{
public:
	LuaCell();
	~LuaCell();
	bool callLua_Function(const char* functionName);
	bool callLua_Function(const char* functionName, const char* signString, ...);
	bool InputLuaFile(const char* path);
	int   getLua_Int(const char* signString, ...);
	float getLua_Float(const char* signString, ...);
	const char* getLua_CharPtr(const char* signString, ...);
	int   getLua_TableInt(const char* table, const char* variable);
	int   getLua_TableInt(const char* table, const int variable);
	float getLua_TableFloat(const char* table, const char* variable);
	float getLua_TableFloat(const char* table, const int variable);
	const char* getLua_TableCharPtr(const char* table, const char* variable);
	const char* getLua_TableCharPtr(const char* table, const int variable);
	int   getLua_TableTableInt(const char* table1, const char* table2, const char* variable);	
	int   getLua_TableTableInt(const char* table1, const char* table2, const int variable);	
	int   getLua_TableTableInt(const char* table1, const int table2, const char* variable);
	float getLua_TableTableFloat(const char* table1, const char* table2, const char* variable);
	float getLua_TableTableFloat(const char* table1, const char* table2, const int variable);
	float getLua_TableTableFloat(const char* table1, const int table2, const char* variable);
	const char* getLua_TableTableCharPtr(const char* table1, const char* table2, const char* variable);
	const char* getLua_TableTableCharPtr(const char* table1, const char* table2, const int variable);
	const char* getLua_TableTableCharPtr(const char* table1, const int table2, const char* variable);
	fRect getLua_fRect(const char* rect);
	fRect getLua_TablefRect(const char* table, const char* rect);
	fRect getLua_TableTablefRect(const char* table1, const char* table2, const char* rect);
	fRect getLua_TableTablefRect(const char* table1, const int table2, const char* rect);
	void setLua_Int(const char* variable, int value);
	void setLua_Float(const char* variable, float value);
	void setLua_CharPtr(const char* variable, const char* value);
	void setLua_TableInt(const char* table, const char* variable, int value);
	void setLua_TableFloat(const char* table, const char* variable, float value);
	void setLua_TableCharPtr(const char* table, const char* variable, const char* value);
	void setLua_TableTableInt(const char* table1, const char* table2, const char* variable, int value);
	void setLua_TableTableFloat(const char* table1, const char* table2, const char* variable, float value);
	void setLua_TableTableCharPtr(const char* table1, const char* table2, const char* variable, const char* value);
	bool setLua_NewTable(const char* table);
	bool checkLua_ValueIsNil(const char* variable);
	bool checkLua_TableValueIsNil(const char* table, const char* variable);
	bool checkLua_TableValueIsNil(const char* table, const int variable);
	bool checkLua_TableTableValueIsNil(const char* table1, const char* table2, const char* variable);
	bool checkLua_TableTableValueIsNil(const char* table1, const int table2, const char* variable);
	bool checkLua_TableTableValueIsNil(const char* table1, const char* table2, const int variable);
private:
	lua_State* m_LuaState;
};

#endif // LuaCell_Im42c45f58m1233b1a3831mm7e5f_H

