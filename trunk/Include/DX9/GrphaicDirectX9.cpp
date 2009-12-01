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
#include "GrphaicDirectX9.h"
#include <cassert>

GrphaicDirectX9::GrphaicDirectX9( HWND hWnd ):m_hWnd(hWnd),m_pD3D(NULL),m_pD3DDevice(NULL)
{
}

GrphaicDirectX9::~GrphaicDirectX9( void )
{
	ReleaseGraphicsDevice();
}

bool GrphaicDirectX9::InitDevice()
{
	RECT rect;
	GetWindowRect(m_hWnd, &rect);

	LONG w = rect.right - rect.left;
	LONG h = rect.bottom - rect.top;
	if ( w==0 || h==0 )
		return false;

	int multisamples = 2;

	// `���o�@��D3D9����, �����ߤ@�\�άO�h�}�үu���i�H����ø�Ϫ�D3D9 Device.`
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return false;

	ZeroMemory( &m_pD3DPresent, sizeof(m_pD3DPresent) );
	m_pD3DPresent.Windowed = true;
	m_pD3DPresent.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pD3DPresent.BackBufferFormat = D3DFMT_UNKNOWN;
	m_pD3DPresent.BackBufferCount = 1; // `���Ѥ@��backbuffer`
	m_pD3DPresent.EnableAutoDepthStencil = TRUE;
	m_pD3DPresent.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_pD3DPresent.MultiSampleType = (D3DMULTISAMPLE_TYPE) multisamples;
	m_pD3DPresent.hDeviceWindow = m_hWnd;
	m_pD3DPresent.BackBufferWidth = 1280;
	m_pD3DPresent.BackBufferHeight = 800;
	bool device_initialized = false;
	/*

	`�յۥ�4�ؤ��P��k�Ӷ}��d3d9`
	1. D3DDEVTYPE_HAL + D3DCREATE_HARDWARE_VERTEXPROCESSING 
	`�������GPU�B�z`
	2. D3DDEVTYPE_HAL + D3DCREATE_MIXED_VERTEXPROCESSING	
	`Vertex�i��CPU��GPU�ӳB�z, �䥦�OGPU.`
	3. D3DDEVTYPE_HAL + D3DCREATE_SOFTWARE_VERTEXPROCESSING 
	`Vertex�OCPU, �䥦�OGPU.`
	4. D3DDEVTYPE_REF + D3DCREATE_SOFTWARE_VERTEXPROCESSING	
	`������CPU�B�z, �o�O�ӫD�`�C���Ҧ�.`

	*/

	const int device_types = 4;

	struct sDeviceType
	{
		D3DDEVTYPE type;
		DWORD behavior;
	};

	sDeviceType device_type[device_types] = 
	{
		{D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING},
		{D3DDEVTYPE_HAL, D3DCREATE_MIXED_VERTEXPROCESSING},
		{D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING},
		{D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING}
	};

	for ( int type=0; type<device_types; type++ )
	{
		// `�յۥh�}�Ҥ@��Direct3D9�˸m`
		if( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, device_type[type].type, m_hWnd,
			device_type[type].behavior, &m_pD3DPresent, &m_pD3DDevice )==D3D_OK )
		{
			device_initialized = true;
			break;
		}
	}

	return device_initialized;
}

bool GrphaicDirectX9::ResetDevice( void )
{
	RECT rect;
	GetWindowRect( m_hWnd, &rect);
	
	LONG w = rect.right - rect.left;
	LONG h = rect.bottom - rect.top;
	if ( w==0 || h==0 )
		return false;

	m_pD3DPresent.BackBufferWidth = 0;
	m_pD3DPresent.BackBufferHeight = 0;
	m_pD3DPresent.BackBufferCount = 1; // `���Ѥ@��backbuffer`

	if ( D3D_OK==m_pD3DDevice->Reset(&m_pD3DPresent) )
		return true;
	else
		return false;
}

bool GrphaicDirectX9::ReleaseGraphicsDevice( void )
{
	if ( m_pD3DDevice )
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	if ( m_pD3D )
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
	return true;
}

LPDIRECT3DDEVICE9 GrphaicDirectX9::GetGraphicsDevice( void )
{
	return m_pD3DDevice;
}

LPDIRECT3DVERTEXSHADER9 GrphaicDirectX9::LoadVertexShader_HLSL( const wchar_t *fullpath, const char *entry, const char *profile )
{
	LPD3DXBUFFER pShader = NULL;
	LPD3DXBUFFER pErrorMsg = NULL;
	DWORD flags = 0;
#ifdef _DEBUG
	flags |= D3DXSHADER_DEBUG;
#endif

	HRESULT result = D3DXCompileShaderFromFileW(
		fullpath,
		NULL,
		NULL,
		entry,
		profile,
		flags,
		&pShader,
		&pErrorMsg,
		NULL
		);

	if ( result != S_OK )
	{
		if ( pErrorMsg )
		{
			pErrorMsg->Release();
		}
		return NULL;
	}

	LPDIRECT3DVERTEXSHADER9 pVertexShader = NULL;
	result = m_pD3DDevice->CreateVertexShader( (DWORD*)pShader->GetBufferPointer(), &pVertexShader);
	if ( result!=S_OK )
	{
	}

	pShader->Release();

	return pVertexShader;
}

LPDIRECT3DPIXELSHADER9 GrphaicDirectX9::LoadPixelShader_HLSL( const wchar_t *fullpath, const char *entry, const char *profile )
{
	LPD3DXBUFFER pShader = NULL;
	LPD3DXBUFFER pErrorMsg = NULL;
	DWORD flags = 0;
#ifdef _DEBUG
	flags |= D3DXSHADER_DEBUG;
#endif

	HRESULT result = D3DXCompileShaderFromFileW(
		fullpath,
		NULL,
		NULL,
		entry,
		profile,
		flags,
		&pShader,
		&pErrorMsg,
		NULL
		);

	if ( result != S_OK )
	{
		if ( pErrorMsg )
		{
			pErrorMsg->Release();
		}
		return NULL;
	}

	LPDIRECT3DPIXELSHADER9 pPixelShader = NULL;
	result = m_pD3DDevice->CreatePixelShader( (DWORD*)pShader->GetBufferPointer(), &pPixelShader);
	if ( result!=S_OK )
	{
	}

	pShader->Release();

	return pPixelShader;
}

LPDIRECT3DVERTEXSHADER9 GrphaicDirectX9::LoadVertexShader_ASM( const wchar_t *fullpath )
{
	LPD3DXBUFFER pShader = NULL;
	LPD3DXBUFFER pErrorMsg = NULL;
	DWORD flags = 0;
#ifdef _DEBUG
	flags |= D3DXSHADER_DEBUG;
#endif

	HRESULT result = D3DXAssembleShaderFromFile(
		fullpath,
		NULL,
		NULL,
		flags,
		&pShader,
		&pErrorMsg
		);

	if ( result != S_OK )
	{
		if ( pErrorMsg )
		{
			pErrorMsg->Release();
		}
	}

	LPDIRECT3DVERTEXSHADER9 pVertexShader = NULL;
	result = m_pD3DDevice->CreateVertexShader( (DWORD*)pShader->GetBufferPointer(), &pVertexShader);
	if ( result!=S_OK )
	{
	}

	pShader->Release();

	return pVertexShader;
}

LPDIRECT3DPIXELSHADER9 GrphaicDirectX9::LoadPixelShader_ASM( const wchar_t *fullpath )
{
	LPD3DXBUFFER pShader = NULL;
	LPD3DXBUFFER pErrorMsg = NULL;
	DWORD flags = 0;
#ifdef _DEBUG
	flags |= D3DXSHADER_DEBUG;
#endif

	HRESULT result = D3DXAssembleShaderFromFile(
		fullpath,
		NULL,
		NULL,
		flags,
		&pShader,
		&pErrorMsg
		);

	if ( result != S_OK )
	{
		if ( pErrorMsg )
		{
			pErrorMsg->Release();
		}
	}

	LPDIRECT3DPIXELSHADER9 pPixelShader = NULL;
	result = m_pD3DDevice->CreatePixelShader( (DWORD*)pShader->GetBufferPointer(), &pPixelShader);
	if ( result!=S_OK )
	{
	}

	pShader->Release();

	return pPixelShader;
}

LPD3DXEFFECT GrphaicDirectX9::LoadFXShader( const wchar_t *fullpath )
{
	LPD3DXEFFECT pEffect;
	LPD3DXBUFFER pErrorMsg = NULL;
	DWORD flags = 0;
#ifdef _DEBUG
	flags |= D3DXSHADER_DEBUG;
#endif

	if ( D3D_OK!=D3DXCreateEffectFromFile(m_pD3DDevice, fullpath, NULL, NULL, flags, NULL, &pEffect, &pErrorMsg) )
	{
		if ( pErrorMsg )
		{
		}
	}

	SAFE_RELEASE(pErrorMsg);

	return pEffect;
}


LPDIRECT3D9 GrphaicDirectX9::GetD3D9( void )
{
	return m_pD3D;
}

int GrphaicDirectX9::CheckDevice()
{
	HRESULT hr;
	assert(m_pD3DDevice != NULL); //fail device
	//���տW�e�Ҧ��A�аѾ\DX8���
	if( FAILED( hr = m_pD3DDevice->TestCooperativeLevel() ) )
	{
		// �p�G�˸m�򥢡A���nRender�A��ܳQ�ϥΪ̡������X�h�����F�H
		if( D3DERR_DEVICELOST == hr )
			return DeviceState(LOST);
		// �p�G�ݭn���m(�S���^�ӤF�H)�N���m
		if( D3DERR_DEVICENOTRESET == hr )
		{
			return DeviceState(RESET);
		}
	}
	return DeviceState(NORMAL);
}