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

#ifndef FlatRenderDx9_Im5b0fc51m122c45fb3b7mm7e5f_H
#define FlatRenderDx9_Im5b0fc51m122c45fb3b7mm7e5f_H

#include <d3d9.h>
#include <d3dx9tex.h>
#include <vector>
#include <map>
#include <algorithm>
#include "DateType.h"
#include "..\Win32\ConvertType.h"
#include "..\Win32\EditBitMap.h"

const int D3DFVF_VERTEX_BLEND = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const int D3DFVF_VERTEX = (D3DFVF_XYZ | D3DFVF_TEX1);
const int MAX_LAYER = 6;
//���`�����I���c

enum SaveFormat
{
	BMP,JPG,PNG,TGA,DDS
};

class FlatRenderDx9 
{
public:
	FlatRenderDx9() {};
	FlatRenderDx9(LPDIRECT3DDEVICE9 device);
	~FlatRenderDx9();
	void SetRenderRect(RECT rect);
	bool LoadPicture(const wchar_t* filepath, const wchar_t* id);
	bool LoadBmpMem(unsigned char *BmpPic, int w, int h, int per_bytes, const wchar_t* id);
	bool LoadTgaMem(unsigned char *TgaPic, int w, int h, int per_bytes, const wchar_t* id);
	bool LoadMapMem(EditBitMap &bitmap, const wchar_t* id);
	void SaveNow(int w, int h, int picFormat, const wchar_t* id);	
	//�}�l��V
	void BeginRender();
	//�t�d�C�V����V
	void RenderFrame();
	//������V
	void EndRender();		
	void ReSetDevice(LPDIRECT3DDEVICE9 device);
	//�M���Ϥ��]�w
	void ClearSet();
	void ClearLoadPic();
	void SetFillPicture(const wchar_t* id, int layer);
	//id�O���J�ɧ��誺id�Aangle�O���ɰw���઺���סAreverse�O�n½�઺�����Aorigin�O�n���઺���I�A
	//blend_colors�O�n�V���C��
	//�x�ο�J��+������I
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle);
	//�x�ο�J��+������I
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle, fpoint origin);
	//�x�ΩMblend color 4���J��(a,r,g,b)+½��
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle);
	//�x�ΩMblend color 4���J��(a,r,g,b)+������I+½��
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle, fpoint origin);

	//�|�I����J��+������I
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle);
	//�|�I����J��+������I
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle, fpoint origin);
	//�|�I���Mblend color 4���J��(a,r,g,b)+½��
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle);
	//�|�I���Mblend color 4���J��(a,r,g,b)+������I+½��
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin);

	//�h��ϧΪ��x�ο�J��+������I
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle);
	//�h��ϧΪ��x�ο�J��+������I
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, fpoint origin);
	//�h��ϧΪ��x�ΩMblend color 4���J��(a,r,g,b)+½��
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle);
	//�h��ϧΪ��x�ΩMblend color 4���J��(a,r,g,b)+������I+½��
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, fpoint origin);

	//�h��ϧΪ��|�I����J��+������I
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle);
	//�h��ϧΪ��|�I����J��+������I
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, fpoint origin);
	//�h��ϧΪ��|�I���Mblend color 4���J��(a,r,g,b)+½��
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle);
	//�h��ϧΪ��|�I���Mblend color 4���J��(a,r,g,b)+������I+½��
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin);

	//��J���@���C��A�Pı�N���[�W�o����
	void AddColorShade(unsigned char blend_colors[4]);
	//��J��-256~255�A�ĪG�O�¥ե�
	void AddLightShade(short level);
	//����J��V�M���ת�
	void SetSpotLight(int layer, fpoint begPos, float direction,
		unsigned char begColors[3], short begAlpha, unsigned char endColors[3], 
		short endAlpha,	float angle, float lightlen);
	//��J�����I��
	void SetSpotLight(int layer, fpoint begPos, fpoint endPos,
		unsigned char begColors[3], short begAlpha, unsigned char endColors[3], 
		short endAlpha,	float angle);
private:
	LONG	m_Width,	m_Height;
	float	m_HandledWidth,	m_HandledHeight;
	HWND	m_hWnd;
	LPDIRECT3DDEVICE9 m_device;
	LPDIRECT3DVERTEXBUFFER9 m_lpVertexBuffer;
	std::map<const wchar_t* const,LPDIRECT3DTEXTURE9*, wcharcmp > m_TextureMap;
	std::map<const wchar_t* const,LPDIRECT3DTEXTURE9*, wcharcmp >::iterator m_MapPos;		
	std::vector<PicInfo> m_vPicInfo[6];
	std::vector<PicInfo_Blend> m_vPicInfo_Blend[6];
	std::vector<PicInfo>::iterator m_vPicInfoPos;
	std::vector<PicInfo_Blend>::iterator m_vPicInfoPos_Blend;
	std::vector<stSpotLight> m_SpotLightInfo[6];
	std::vector<stSpotLight>::iterator m_SpotLightInfoPos;

	void VectorRotate(fpoint point1, fpoint point2, fpoint &newpoint, float angle );
	void SetPointData(stPicD3DVertex_Blend *pointdata, fpoint point2Ds[4],
		int reverse, float angle, fpoint origin);
	void SetPointData(stPicD3DVertex *pointdata, fpoint point2Ds[4], 
		int reverse, float angle, fpoint origin);
	void BlendSet(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void BasicSet(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin);
	void MulBlendSet(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void MulBasicSet(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin);
	void SetMulPointData(stPicD3DVertex *pointdata, fpoint point2Ds[4], 
		Position position, Position maxPosition, int reverse, float angle, fpoint origin);
	void SetMulPointData(stPicD3DVertex_Blend *pointdata, fpoint point2Ds[4], 
		Position position, Position maxPosition, int reverse, float angle, fpoint origin);
	void fSwap(float &f1, float &f2);
	void TurnTrianglePoint(fpoint tripoint[3], fpoint begPos, float direction,
		float lightlen, float angle);
	//��Y�ӻE���Orender
	void RenderSpotLight(stSpotLight* linofo);
};
#endif // FlatRenderDx9_Im5b0fc51m122c45fb3b7mm7e5f_H
