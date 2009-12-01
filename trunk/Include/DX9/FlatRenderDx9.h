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
//正常版頂點結構

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
	//開始渲染
	void BeginRender();
	//負責每幀的渲染
	void RenderFrame();
	//結束渲染
	void EndRender();		
	void ReSetDevice(LPDIRECT3DDEVICE9 device);
	//清除圖片設定
	void ClearSet();
	void ClearLoadPic();
	void SetFillPicture(const wchar_t* id, int layer);
	//id是載入時材質的id，angle是順時針旋轉的角度，reverse是要翻轉的種類，origin是要旋轉的原點，
	//blend_colors是要混的顏色
	//矩形輸入版+旋轉原點
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle);
	//矩形輸入版+旋轉原點
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, float angle, fpoint origin);
	//矩形和blend color 4色輸入版(a,r,g,b)+翻轉
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle);
	//矩形和blend color 4色輸入版(a,r,g,b)+旋轉原點+翻轉
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fRect rect, int reverse, float angle, fpoint origin);

	//四點型輸入版+旋轉原點
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle);
	//四點型輸入版+旋轉原點
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], float angle, fpoint origin);
	//四點型和blend color 4色輸入版(a,r,g,b)+翻轉
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle);
	//四點型和blend color 4色輸入版(a,r,g,b)+旋轉原點+翻轉
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetPicture(const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin);

	//多格圖形的矩形輸入版+旋轉原點
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle);
	//多格圖形的矩形輸入版+旋轉原點
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, fpoint origin);
	//多格圖形的矩形和blend color 4色輸入版(a,r,g,b)+翻轉
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle);
	//多格圖形的矩形和blend color 4色輸入版(a,r,g,b)+旋轉原點+翻轉
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, fpoint origin);

	//多格圖形的四點型輸入版+旋轉原點
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle);
	//多格圖形的四點型輸入版+旋轉原點
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, fpoint origin);
	//多格圖形的四點型和blend color 4色輸入版(a,r,g,b)+翻轉
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle);
	//多格圖形的四點型和blend color 4色輸入版(a,r,g,b)+旋轉原點+翻轉
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4]);
	void SetMulPicture(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin);

	//輸入為一種顏色，感覺就像加上濾光片
	void AddColorShade(unsigned char blend_colors[4]);
	//輸入為-256~255，效果是純白光
	void AddLightShade(short level);
	//有輸入方向和長度版
	void SetSpotLight(int layer, fpoint begPos, float direction,
		unsigned char begColors[3], short begAlpha, unsigned char endColors[3], 
		short endAlpha,	float angle, float lightlen);
	//輸入結束點版
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
	//把某個聚光燈render
	void RenderSpotLight(stSpotLight* linofo);
};
#endif // FlatRenderDx9_Im5b0fc51m122c45fb3b7mm7e5f_H
