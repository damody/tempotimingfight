/*
Copyright (C) 2009  ¹CÀ¸¤Ñ«G¬É

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ConvertType.h"
#include <windows.h>
std::vector<char*> ConvertType::array_char;
std::vector<wchar_t*> ConvertType::array_wchar_t;

void ConvertType::UnicodeToAnsi(const wchar_t *unicode, char *ansi)
{
	int n;
	n = WideCharToMultiByte(CP_ACP, 0, unicode, -1, ansi, 0, NULL, FALSE);
	WideCharToMultiByte(CP_ACP, 0, unicode, -1, ansi, n, NULL, FALSE);
}

void ConvertType::AnsiToUnicode(wchar_t *unicode, const char *ansi)
{
	int n;
	n = MultiByteToWideChar(CP_ACP, 0, ansi, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ansi, -1, unicode, n);
} 

const wchar_t* ConvertType::ReturnUnicode( const char *ansi )
{
	wchar_t* unicode = new wchar_t[strlen(ansi)+1];
	AnsiToUnicode(unicode, ansi);
	array_wchar_t.push_back(unicode);
	return unicode;
}

wchar_t* ConvertType::ReturnUnicode( const wchar_t* unicode )
{
	int len = wcslen(unicode)+1;
	wchar_t* unicode2 = new wchar_t[len];
	wcsncpy_s(unicode2, len, unicode, len);
	array_wchar_t.push_back(unicode2);
	return unicode2;
}
const char* ConvertType::ReturnAnsi( const wchar_t *unicode )
{
	char* ansi = new char[wcslen(unicode)+1];
	UnicodeToAnsi(unicode, ansi);
	array_char.push_back(ansi);
	return ansi;
}

char* ConvertType::ReturnAnsi( const char* ansi )
{
	int len = strlen(ansi)+1;
	char* ansi2 = new char[len];
	strncpy_s(ansi2, len, ansi, len);
	array_char.push_back(ansi2);
	return ansi2;
}
void ConvertType::FreeAllMemory()
{
	std::vector<char*>::iterator i;
	for (i = array_char.begin();i != array_char.end();i++)
	{
		delete[] *i;
	}
	array_char.clear();
	std::vector<wchar_t*>::iterator j;
	for (j = array_wchar_t.begin();j != array_wchar_t.end();j++)
	{
		delete[] *j;
	}
	array_wchar_t.clear();
}