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

#ifndef GrphaicDirectX9_Im5fa52b0cm122a159526cmm7e5f_H
#define GrphaicDirectX9_Im5fa52b0cm122a159526cmm7e5f_H

#define DIRECTINPUT_VERSION 0x0800
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define SAFE_RELEASE(x) if (x) { x->Release(); x=NULL; }
#define RELEASE_ARRAY(x) if (x) { delete [] x; x=NULL; }

enum DeviceState
{
	NORMAL,LOST,RESET
};

class GrphaicDirectX9 
{
public:
	GrphaicDirectX9(HWND hWnd);
	~GrphaicDirectX9(void);
	bool InitDevice();
	int  CheckDevice();
	bool ResetDevice(void);
	bool ReleaseGraphicsDevice(void);
	LPDIRECT3DDEVICE9 GetGraphicsDevice(void);
	LPDIRECT3D9 GetD3D9(void);
	LPDIRECT3DVERTEXSHADER9 LoadVertexShader_HLSL(const wchar_t *fullpath, const char *entry, const char *profile);
	LPDIRECT3DPIXELSHADER9 LoadPixelShader_HLSL(const wchar_t *fullpath, const char *entry, const char *profile);
	LPDIRECT3DVERTEXSHADER9 LoadVertexShader_ASM(const wchar_t *fullpath);
	LPDIRECT3DPIXELSHADER9 LoadPixelShader_ASM(const wchar_t *fullpath);
	LPD3DXEFFECT LoadFXShader(const wchar_t *filename);
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DPRESENT_PARAMETERS m_pD3DPresent;
	HWND m_hWnd;
};

#endif // GrphaicDirectX9_Im5fa52b0cm122a159526cmm7e5f_H

