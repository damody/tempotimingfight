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

#ifndef Win32Window_Im40eda407m1229c278a93mm7e5f_H
#define Win32Window_Im40eda407m1229c278a93mm7e5f_H

// Windows 標頭檔:
#include <windows.h>

class Win32Window
{	
public:
	Win32Window();
	~Win32Window();
	HWND	ToCreateWindow(int x, int y, int width, int height, const wchar_t *title, LRESULT (_stdcall *wndporc)(HWND, UINT, WPARAM, LPARAM) = &Win32Window::Proc);
	HWND	ToFullScreen(int width, int height, LRESULT (_stdcall *wndporc)(HWND, UINT, WPARAM, LPARAM) = &Win32Window::Proc);
	MSG	HandlePeekMessage(void);
	HWND	GetHandle(void);
	HINSTANCE	GetInstance(void);
	RECT	GetRect(void);
	void	GetMouseState(int &x, int &y, int button[3]);
	void	ToShow(void);
	void	ToHide(void);
	void	ToMove(UINT x, UINT y, UINT nWidth, UINT nHeight, bool bRepaint = true);
	DWORD	GetStyle() {return m_style;}
	void	SetStyle(DWORD style) {m_style = style;}
	DWORD	GetExStyle() {return m_EX_style;}
	void	SetExStyle(DWORD style) {m_EX_style = style;}
	void	Get_W_H(int &w, int &h) {w = m_Width; h = m_Height;}
	static LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
private:
	int m_Height,m_Width;
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	DWORD m_style;
	DWORD m_EX_style;
};


#endif // Win32Window_Im40eda407m1229c278a93mm7e5f_H

