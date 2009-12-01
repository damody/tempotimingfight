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
#ifndef _ConvertType_H
#define _ConvertType_H
#include <vector>
class ConvertType
{
public:
	static void UnicodeToAnsi(const wchar_t* unicode, char* ansi);
	static void AnsiToUnicode(wchar_t* unicode, const char* ansi);
	static const wchar_t* ReturnUnicode(const char* ansi);
	static wchar_t* ReturnUnicode(const wchar_t* ansi);
	static const char* ReturnAnsi(const wchar_t* ansi);
	static char* ReturnAnsi(const char* ansi);
	static void FreeAllMemory();
private:
	static std::vector<char*> array_char;
	static std::vector<wchar_t*> array_wchar_t;
};


#endif // _ConvertType_H