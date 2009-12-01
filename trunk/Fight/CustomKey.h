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

#ifndef CUSTOMKEY_H
#define CUSTOMKEY_H
#include <map>

class CustomKey
{
public:
	void	SetKeyEvent(int key,int BackValue);
	int	TransformKey(int key);
	int	operator()(int key);
private:
	typedef std::map<int,int> Keymap;
	Keymap m_table;
	Keymap::iterator m_pos;
};

#endif //CUSTOMKEY_H