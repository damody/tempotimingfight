/*
Copyright (C) 2009  ¹CÀ¸¤Ñ«G¬É

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
#include "InputState.h"

InputState::InputState( GetDirectXInput *DxInput ) :m_lpDxInput(DxInput)
{
	memset(m_NowKeyState,0,sizeof(m_NowKeyState));
	memset(m_LastKeyState,0,sizeof(m_LastKeyState));
}

bool InputState::isKeyDown( int index )
{
	if ( m_NowKeyState[index] && !m_LastKeyState[index] ) // key down
		return true;
	return false;
}

bool InputState::isKeyUP( int index )
{
	if ( !m_NowKeyState[index] && m_LastKeyState[index] ) // key up
		return true;
	return false;	
}

bool InputState::isKeyHold( int index )
{
	if ( m_NowKeyState[index] && m_LastKeyState[index] ) // key hold
		return true;
	return false;	
}

bool InputState::isKeyPress( int index )
{
	if ( m_NowKeyState[index] ) // key pressed
		return true;
	return false;
}

void InputState::GetInput()
{
	memcpy(m_LastKeyState, m_NowKeyState, sizeof(m_LastKeyState));
	m_lpDxInput->ReadKeyboard(m_NowKeyState);	
}

