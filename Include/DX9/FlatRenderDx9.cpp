//���{���X�ݩ� �ѫGdamody,�l����W.S.C. �Ρu�C���ѫG�ɡv���C���}�o�ζ����{���v�@�P�Ҧ�
//#include "stdafx.h"
#include "FlatRenderDx9.h"
#include <iostream> // not required by most systems
#include <assert.h>
#define SAFE_RELEASE(x) if (x) { x->Release(); x=NULL; }
#define RELEASE_ARRAY(x) if (x) { delete [] x; x=NULL; }


const float MATH_PI = 3.141592653f;
FlatRenderDx9::FlatRenderDx9(LPDIRECT3DDEVICE9 device):m_device(device)
{
	m_device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

void FlatRenderDx9::SetRenderRect(RECT rect)
{
	m_Width = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;
	m_HandledWidth = 2 / (float)m_Width;
	m_HandledHeight = 2 / (float)m_Height;
}
bool FlatRenderDx9::LoadPicture(const wchar_t* filepath, const wchar_t* id)
{
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos == m_TextureMap.end())
	{
		//�����J����
		LPDIRECT3DTEXTURE9 *tmpTexture = new LPDIRECT3DTEXTURE9;
		int len = wcslen(id)+1;
		wchar_t* wid = new wchar_t[len];
		wcsncpy_s(wid, len, id, len);
		if(D3DXCreateTextureFromFileEx(m_device, filepath, 
			D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, 
			D3DPOOL_MANAGED, D3DX_DEFAULT, 
			D3DX_DEFAULT, 0, NULL, NULL,
			tmpTexture) != D3D_OK) return false;
		//��id�O�U
		m_TextureMap.insert(std::make_pair(wid,tmpTexture));
	}	
	return true;
}


bool FlatRenderDx9::LoadMapMem( EditBitMap &bitmap, const wchar_t* id )
{
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos == m_TextureMap.end())
	{
		//�����J����
		LPDIRECT3DTEXTURE9 *tmpTexture = new LPDIRECT3DTEXTURE9;
		int len = wcslen(id)+1;
		wchar_t* wid = new wchar_t[len];
		wcsncpy_s(wid, len, id, len);
		if ( D3D_OK!=m_device->CreateTexture(bitmap.iWidth, bitmap.iHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, tmpTexture, NULL) )
			return false;
		// ����K�ϸ��
		D3DLOCKED_RECT locked_rect;
		(*tmpTexture)->LockRect(0, &locked_rect, NULL, 0);
		memcpy(locked_rect.pBits,bitmap.pImage,sizeof(unsigned char)*bitmap.lImageSize);
		(*tmpTexture)->UnlockRect(0);
		//��id�O�U
		m_TextureMap.insert(std::make_pair(wid,tmpTexture));
	}	
	return true;
}

bool FlatRenderDx9::LoadBmpMem(unsigned char *BmpPic, int w, int h, int per_bytes, const wchar_t* id)
{
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos == m_TextureMap.end())
	{
		//�����J����
		LPDIRECT3DTEXTURE9 *tmpTexture = new LPDIRECT3DTEXTURE9;
		int len = wcslen(id)+1;
		wchar_t* wid = new wchar_t[len];
		wcsncpy_s(wid, len, id, len);
		if ( D3D_OK!=m_device->CreateTexture(w, h, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, tmpTexture, NULL) )
			return false;
		// ����K�ϸ��
		D3DLOCKED_RECT locked_rect;
		(*tmpTexture)->LockRect(0, &locked_rect, NULL, 0);
		unsigned char *target = (unsigned char *)locked_rect.pBits;
		unsigned char *source = BmpPic;
		if (per_bytes == 3)
		{
			for ( int y=0; y<h; y++ )
			{
				for ( int x=0; x<w;x++ )
				{
					target[0] = source[0];
					target[1] = source[1];
					target[2] = source[2];
					target[3] = 255;
					target+=4;
					source+=3;
				}
			}
		}
		else if (per_bytes == 4)
		{
			for ( int y=0; y<h; y++ )
			{
				for ( int x=0; x<w;x++ )
				{
					target[0] = source[0];
					target[1] = source[1];
					target[2] = source[2];
					target[3] = 255;
					target+=4;
					source+=4;
				}
			}
		}
		(*tmpTexture)->UnlockRect(0);
		//��id�O�U
		m_TextureMap.insert(std::make_pair(wid,tmpTexture));
	}	
	return true;
}

bool FlatRenderDx9::LoadTgaMem( unsigned char *TgaPic, int w, int h, int per_bytes, const wchar_t* id )
{
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos == m_TextureMap.end())
	{
		//�����J����
		LPDIRECT3DTEXTURE9 *tmpTexture = new LPDIRECT3DTEXTURE9;
		int len = wcslen(id)+1;
		wchar_t* wid = new wchar_t[len];
		wcsncpy_s(wid, len, id, len);
		if ( D3D_OK!=m_device->CreateTexture(w, h, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, tmpTexture, NULL) )
			return false;
		// ����K�ϸ��
		D3DLOCKED_RECT locked_rect;
		(*tmpTexture)->LockRect(0, &locked_rect, NULL, 0);
		unsigned char *target = (unsigned char *)locked_rect.pBits;
		unsigned char *source = TgaPic;
		if (per_bytes == 4)
		{
			for ( int y=0; y<h; y++ )
			{
				for ( int x=0; x<w; x++ )
				{
					// D3DFMT_A8R8G8B8���O����ƦC���ǬOBGRA
					// �n���RGBA�ƦC���O���鰵�ഫ
					target[0] = source[2];
					target[1] = source[1];
					target[2] = source[0];
					target[3] = source[3];

					target+=4;
					source+=4;
				}
			}
		}
		else if (per_bytes == 3)
		{
			for ( int y=0; y<h; y++ )
			{
				for ( int x=0; x<w; x++ )
				{
					// D3DFMT_A8R8G8B8���O����ƦC���ǬOBGRA
					// �n���RGBA�ƦC���O���鰵�ഫ
					target[0] = source[2];
					target[1] = source[1];
					target[2] = source[0];
					target[3] = 255;

					target+=4;
					source+=3;
				}
			}
		}
		(*tmpTexture)->UnlockRect(0);
		//��id�O�U
		m_TextureMap.insert(std::make_pair(wid,tmpTexture));
	}	
	return true;
}

void FlatRenderDx9::ClearLoadPic()
{
	for (m_MapPos = m_TextureMap.begin();m_MapPos != m_TextureMap.end();m_MapPos++)
	{
		delete[] m_MapPos->first;
		SAFE_RELEASE((*(m_MapPos->second)));
	}
	m_TextureMap.clear();
}

_inline void FlatRenderDx9::BlendSet( const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	stPicD3DVertex_Blend objData[6];
	SetPointData(objData, points, reverse, angle, origin);
	for (int i=0; i<6; i++)
	{
		objData[i].color_a = blend_colors[0];
		objData[i].color_r = blend_colors[1];
		objData[i].color_g = blend_colors[2];
		objData[i].color_b = blend_colors[3];
		objData[i].x=objData[i].x*m_HandledWidth-1;
		objData[i].y=-objData[i].y*m_HandledHeight+1;
	}
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos != m_TextureMap.end())
	{
		PicInfo_Blend tmpPicInfo_Blend;
		memcpy(&tmpPicInfo_Blend, objData, sizeof(objData));
		tmpPicInfo_Blend.lpTexture = m_MapPos->second;
		m_vPicInfo_Blend[layer].push_back(tmpPicInfo_Blend);
	}
}

void FlatRenderDx9::BasicSet( const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin )
{
	stPicD3DVertex objData[6];
	SetPointData(objData, points, reverse, angle, origin);
	for (int forx=0; forx<6; forx++)
	{
		objData[forx].x=objData[forx].x*m_HandledWidth-1;
		objData[forx].y=-objData[forx].y*m_HandledHeight+1;
	}
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos != m_TextureMap.end())
	{
		PicInfo tmpPicInfo;
		memcpy(&tmpPicInfo, objData, sizeof(objData));
		tmpPicInfo.lpTexture = m_MapPos->second;
		m_vPicInfo[layer].push_back(tmpPicInfo);
	}
}
void FlatRenderDx9::MulBlendSet(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4])
{
	stPicD3DVertex_Blend objData[6];
	SetMulPointData(objData, points, position, maxPosition, reverse, angle, origin);
	for (int i=0; i<6; i++)
	{
		objData[i].color_a = blend_colors[0];
		objData[i].color_r = blend_colors[1];
		objData[i].color_g = blend_colors[2];
		objData[i].color_b = blend_colors[3];
		objData[i].x=objData[i].x*m_HandledWidth-1;
		objData[i].y=-objData[i].y*m_HandledHeight+1;
	}
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos != m_TextureMap.end())
	{
		PicInfo_Blend tmpPicInfo_Blend;
		memcpy(&tmpPicInfo_Blend, objData, sizeof(objData));
		tmpPicInfo_Blend.lpTexture = m_MapPos->second;
		m_vPicInfo_Blend[layer].push_back(tmpPicInfo_Blend);
	}
}
_inline void FlatRenderDx9::MulBasicSet(const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin)
{
	stPicD3DVertex objData[6];
	SetMulPointData(objData, points, position, maxPosition, reverse, angle, origin);
	for (int forx=0; forx<6; forx++)
	{
		objData[forx].x=objData[forx].x*m_HandledWidth-1;
		objData[forx].y=-objData[forx].y*m_HandledHeight+1;
	}
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos != m_TextureMap.end())
	{
		PicInfo tmpPicInfo;
		memcpy(&tmpPicInfo, objData, sizeof(objData));
		tmpPicInfo.lpTexture = m_MapPos->second;
		m_vPicInfo[layer].push_back(tmpPicInfo);
	}
}

//�C�V����V
void FlatRenderDx9::RenderFrame()
{
// 			// �}��Alpha Test�\��
// 			m_device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
// 			// �]�wAlpha Test���ձ���
// 			m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
// 			// �]�wAlpha Test������˥���
// 			m_device->SetRenderState(D3DRS_ALPHAREF, 127);
//			// ����Alpha Test�\��
//			m_device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// �}�ҲV��\��
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// source_blend_factor = source_color.a
	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// dest_blend_factor = (1 - source_color.a)
	m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �V�⤽�� = source_color.rgba * (source_color.a) + dest_color.rgba * (1 - source_color.a)
	// direct3D���w�|������X�K��alpha��, �⥦�令���Ialpha�Ȭۭ�.
	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	for (int nowLayer= 0; nowLayer < 6; nowLayer++)
	{
		if (m_vPicInfo[nowLayer].size()!=0)
		{
			m_device->SetFVF(D3DFVF_VERTEX);
			UINT uSize = sizeof(stPicD3DVertex) * 6 * m_vPicInfo[nowLayer].size();
			m_device->CreateVertexBuffer(uSize, 0,
				D3DFVF_VERTEX, D3DPOOL_DEFAULT, &m_lpVertexBuffer, NULL);		
			stPicD3DVertex *ptr;
			m_lpVertexBuffer->Lock(0, uSize,(void**)&ptr, 0);
			int iMove = 0;
			for (m_vPicInfoPos = m_vPicInfo[nowLayer].begin();m_vPicInfoPos != m_vPicInfo[nowLayer].end();m_vPicInfoPos++)
			{
				memcpy(ptr + iMove, &(*m_vPicInfoPos), sizeof(stPicD3DVertex) * 6);
				iMove += 6;
			}
			m_lpVertexBuffer->Unlock();
			m_device->SetStreamSource(0, m_lpVertexBuffer, 0, sizeof(stPicD3DVertex));
			iMove = 0;
			for (m_vPicInfoPos = m_vPicInfo[nowLayer].begin();m_vPicInfoPos != m_vPicInfo[nowLayer].end();m_vPicInfoPos++)
			{
				m_device->SetTexture(0,*(m_vPicInfoPos->lpTexture));
				m_device->DrawPrimitive(D3DPT_TRIANGLELIST, iMove, 2);
				iMove += 6;
			}			
			m_lpVertexBuffer->Release();
		}
		if (m_vPicInfo_Blend[nowLayer].size()!=0)
		{
			m_device->SetFVF(D3DFVF_VERTEX_BLEND);
			UINT uSize = sizeof(stPicD3DVertex_Blend) * 6 * m_vPicInfo_Blend[nowLayer].size();
			m_device->CreateVertexBuffer(uSize, 0,
				D3DFVF_VERTEX_BLEND, D3DPOOL_DEFAULT, &m_lpVertexBuffer, NULL);		
			stPicD3DVertex_Blend *ptr;
			m_lpVertexBuffer->Lock(0, uSize,(void**)&ptr, 0);
			int iMove = 0;
			for (m_vPicInfoPos_Blend = m_vPicInfo_Blend[nowLayer].begin(); 
				m_vPicInfoPos_Blend != m_vPicInfo_Blend[nowLayer].end();m_vPicInfoPos_Blend++)
			{
				memcpy(ptr + iMove, &(*m_vPicInfoPos_Blend), sizeof(stPicD3DVertex_Blend) * 6);
				iMove += 6;
			}
			m_lpVertexBuffer->Unlock();
			m_device->SetStreamSource(0, m_lpVertexBuffer, 0, sizeof(stPicD3DVertex_Blend));
			iMove = 0;
			for (m_vPicInfoPos_Blend = m_vPicInfo_Blend[nowLayer].begin();
				m_vPicInfoPos_Blend != m_vPicInfo_Blend[nowLayer].end();m_vPicInfoPos_Blend++)
			{

				m_device->SetTexture(0,*(m_vPicInfoPos_Blend->lpTexture));
				m_device->DrawPrimitive(D3DPT_TRIANGLELIST, iMove, 2);
				iMove += 6;
			}			
			m_lpVertexBuffer->Release();
		}		
		if (m_SpotLightInfo[nowLayer].size() != 0)
		{
			m_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
			for (m_SpotLightInfoPos = m_SpotLightInfo[nowLayer].begin();
				m_SpotLightInfoPos != m_SpotLightInfo[nowLayer].end();m_SpotLightInfoPos++)
			{
				RenderSpotLight(&(*m_SpotLightInfoPos));
			}
		}
	}
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); //�����V��
}
void FlatRenderDx9::BeginRender()
{
	m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0 );
	m_device->BeginScene();	
}
void FlatRenderDx9::EndRender()
{
	m_device->EndScene();
	m_device->Present( NULL, NULL, NULL, NULL );
}
void FlatRenderDx9::AddColorShade(unsigned char blend_colors[4]) //���� a,r,g,b �n�A�[�@��SetColorShade
{
	m_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	stLightPolygon g[]={
		{-1.0f, -1.0f, 0.0f, blend_colors[3], blend_colors[2], blend_colors[1], blend_colors[0]},
		{-1.0f, 1.0f, 0.0f, blend_colors[3], blend_colors[2], blend_colors[1], blend_colors[0]},
		{1.0f, -1.0f, 0.0f, blend_colors[3], blend_colors[2], blend_colors[1], blend_colors[0]},
		{1.0f, -1.0f, 0.0f, blend_colors[3], blend_colors[2], blend_colors[1], blend_colors[0]},
		{1.0f, 1.0f, 0.0f, blend_colors[3], blend_colors[2], blend_colors[1], blend_colors[0]},
		{-1.0f, 1.0f, 0.0f, blend_colors[3], blend_colors[2], blend_colors[1], blend_colors[0]}
	};
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	
	m_device->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_ARGB(blend_colors[0],blend_colors[0],blend_colors[0],blend_colors[0]) );
	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR );
	m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		
	m_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, g, sizeof(stLightPolygon));
}
//-256~255
void FlatRenderDx9::AddLightShade(short level) //�n�A�[�@��SetLightShade
{
	unsigned char mete;
	if (level < 0)
		mete = (unsigned char)(level);
	else
		mete = (unsigned char)(256 + level);
	m_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	stLightPolygon g[]={
		{-1.0f, -1.0f, 0.0f, mete, mete, mete, mete},
		{-1.0f, 1.0f, 0.0f, mete, mete, mete, mete},
		{1.0f, -1.0f, 0.0f, mete, mete, mete, mete},
		{1.0f, -1.0f, 0.0f, mete, mete, mete, mete},
		{1.0f, 1.0f, 0.0f, mete, mete, mete, mete},
		{-1.0f, 1.0f, 0.0f, mete, mete, mete, mete}
	};
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		
	if (level < 0)
	{
		m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
		m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);
	}
	else
	{
		m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
		m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
	}
	m_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, g, sizeof(stLightPolygon));
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
FlatRenderDx9::~FlatRenderDx9()
{
	for (m_MapPos = m_TextureMap.begin();m_MapPos != m_TextureMap.end();m_MapPos++)
	{
		delete (m_MapPos->second);
	}
}	
void FlatRenderDx9::ReSetDevice( LPDIRECT3DDEVICE9 device )
{
	m_device = device;
}

//�H�V�q���覡���I����
void FlatRenderDx9::VectorRotate(fpoint p1, fpoint p2, fpoint &picPoints, float angle )
{
	if (fabs(angle)<0.00001f){
		//�p�G���פӤp�Ϊ����0�N����
		picPoints.x=p2.x;
		picPoints.y=p2.y;
	}else{
		float vectorX,vectorY;
		//���D�X�����I���������V�q
		vectorX =p2.x -p1.x;
		vectorY =p2.y -p1.y;
		//�ι��˱��ऽ����X����᪺�V�q,�A�[�W���I�N�O����᪺�I��m
		picPoints.x =vectorX * cos(angle) - vectorY * sin(angle) + p1.x;
		picPoints.y =vectorX * sin(angle) + vectorY * cos(angle) + p1.y;
	}
}
void FlatRenderDx9::ClearSet()
{
	for (int i= 0; i < 6; i++)
	{
		m_vPicInfo[i].clear();
		m_vPicInfo_Blend[i].clear();
		m_SpotLightInfo[i].clear();
	}		
}

void FlatRenderDx9::SetPointData(stPicD3DVertex_Blend *pointdata, fpoint point2Ds[4], 
				 int reverse/* =NOREVERSE */, float angle/* =0.0f */, fpoint origin/* = */)
{
	fpoint tPoints[4];
	switch (reverse)
	{
	case HORIZONTAL:
		//����½��,�⥿�`���K�Ϯy�Ъ�x�ϦV(1 <-> 0)
		tPoints[0].x=1.0f; tPoints[0].y=0.0f;
		tPoints[1].x=1.0f; tPoints[1].y=1.0f;
		tPoints[2].x=0.0f; tPoints[2].y=0.0f;
		tPoints[3].x=0.0f; tPoints[3].y=1.0f;
		break;
	case VERTICAL:
		//����½��,�⥿�`���K�Ϯy�Ъ�y�ϦV(1 <-> 0)
		tPoints[0].x=0.0f; tPoints[0].y=1.0f;
		tPoints[1].x=0.0f; tPoints[1].y=0.0f;
		tPoints[2].x=1.0f; tPoints[2].y=1.0f;
		tPoints[3].x=1.0f; tPoints[3].y=0.0f;
		break;
	case DIAGONAL:
		//�﨤½��,�⥿�`���K�Ϯy�Ъ�x,y�ϦV(1 <-> 0)
		tPoints[0].x=1.0f; tPoints[0].y=1.0f;
		tPoints[1].x=1.0f; tPoints[1].y=0.0f;
		tPoints[2].x=0.0f; tPoints[2].y=1.0f;
		tPoints[3].x=0.0f; tPoints[3].y=0.0f;
		break;
	default:
		tPoints[0].x=0.0f; tPoints[0].y=0.0f;
		tPoints[1].x=0.0f; tPoints[1].y=1.0f;
		tPoints[2].x=1.0f; tPoints[2].y=0.0f;
		tPoints[3].x=1.0f; tPoints[3].y=1.0f;
	}
	fpoint picPoints[4];
	fpoint p1, p2;
	//��J���O�׫׶q,�Ӥ��ؤT����ƬO�ή|�׶q,�ҥH���������ഫ
	angle=angle*3.1415926f/180;
	//p1�����I�b�e���W���y��,�ҥH�n��origin(�H�Ϫ����W��0,0���y��)+�ϥ��W���y��
	p1.x=origin.x+point2Ds[0].x;
	p1.y=origin.y+point2Ds[0].y;
	//�Np2���O�N�J�n���઺�I�y��,�éI�sVectorRotate�ӱ�����I
	for (int forx=0; forx<4; forx++)
	{
		p2.x=point2Ds[forx].x;
		p2.y=point2Ds[forx].y;
		VectorRotate(p1, p2, picPoints[forx], angle);
	}
	//�N�y�ж�J�U�۪���m
	for(int ix=0;ix<3;ix++){

		pointdata[ix].x=picPoints[ix].x;
		pointdata[ix].y=picPoints[ix].y;
		pointdata[ix].z=0;
		pointdata[ix].tu=tPoints[ix].x;
		pointdata[ix].tv=tPoints[ix].y;
	}
	pointdata[3]=pointdata[2];
	pointdata[4].x=picPoints[3].x;
	pointdata[4].y=picPoints[3].y;
	pointdata[4].z=0;
	pointdata[4].tu=tPoints[3].x;
	pointdata[4].tv=tPoints[3].y;
	pointdata[5]=pointdata[1];
}

void FlatRenderDx9::SetPointData(stPicD3DVertex *pointdata, fpoint point2Ds[4],
				 int reverse/* =NOREVERSE */, float angle/* =0.0f */, fpoint origin/* = */)
{
	fpoint tPoints[4];
	switch (reverse)
	{
	case HORIZONTAL:
		//����½��,�⥿�`���K�Ϯy�Ъ�x�ϦV(1 <-> 0)
		tPoints[0].x=1.0f; tPoints[0].y=0.0f;
		tPoints[1].x=1.0f; tPoints[1].y=1.0f;
		tPoints[2].x=0.0f; tPoints[2].y=0.0f;
		tPoints[3].x=0.0f; tPoints[3].y=1.0f;
		break;
	case VERTICAL:
		//����½��,�⥿�`���K�Ϯy�Ъ�y�ϦV(1 <-> 0)
		tPoints[0].x=0.0f; tPoints[0].y=1.0f;
		tPoints[1].x=0.0f; tPoints[1].y=0.0f;
		tPoints[2].x=1.0f; tPoints[2].y=1.0f;
		tPoints[3].x=1.0f; tPoints[3].y=0.0f;
		break;
	case DIAGONAL:
		//�﨤½��,�⥿�`���K�Ϯy�Ъ�x,y�ϦV(1 <-> 0)
		tPoints[0].x=1.0f; tPoints[0].y=1.0f;
		tPoints[1].x=1.0f; tPoints[1].y=0.0f;
		tPoints[2].x=0.0f; tPoints[2].y=1.0f;
		tPoints[3].x=0.0f; tPoints[3].y=0.0f;
		break;
	default:
		tPoints[0].x=0.0f; tPoints[0].y=0.0f;
		tPoints[1].x=0.0f; tPoints[1].y=1.0f;
		tPoints[2].x=1.0f; tPoints[2].y=0.0f;
		tPoints[3].x=1.0f; tPoints[3].y=1.0f;
	}

	fpoint picPoints[4];
	fpoint p1, p2;
	//��J���O�׫׶q,�Ӥ��ؤT����ƬO�ή|�׶q,�ҥH���������ഫ
	angle=angle*3.1415926f/180;
	//p1�����I�b�e���W���y��,�ҥH�n��origin(�H�Ϫ����W��0,0���y��)+�ϥ��W���y��
	p1.x=origin.x+point2Ds[0].x;
	p1.y=origin.y+point2Ds[0].y;
	//�Np2���O�N�J�n���઺�I�y��,�éI�sVectorRotate�ӱ�����I
	for (int forx=0; forx<4; forx++)
	{
		p2.x=point2Ds[forx].x;
		p2.y=point2Ds[forx].y;
		VectorRotate(p1, p2, picPoints[forx], angle);
	}
	//�N�y�ж�J�U�۪���m
	for(int ix=0;ix<3;ix++){

		pointdata[ix].x=picPoints[ix].x;
		pointdata[ix].y=picPoints[ix].y;
		pointdata[ix].z=0;
		pointdata[ix].tu=tPoints[ix].x;
		pointdata[ix].tv=tPoints[ix].y;
	}
	pointdata[3]=pointdata[2];
	pointdata[4].x=picPoints[3].x;
	pointdata[4].y=picPoints[3].y;
	pointdata[4].z=0;
	pointdata[4].tu=tPoints[3].x;
	pointdata[4].tv=tPoints[3].y;
	pointdata[5]=pointdata[1];
}

void FlatRenderDx9::SetFillPicture( const wchar_t* id, int layer )
{
	stPicD3DVertex_Blend objData[6] = {
		{-1.0f,-1.0f,0.0f,255,255,255,255,0,1},
		{1.0f,-1.0f,0.0f,255,255,255,255,1,1},
		{1.0f,1.0f,0.0f,255,255,255,255,1,0},
		{1.0f,1.0f,0.0f,255,255,255,255,1,0},
		{-1.0f,1.0f,0.0f,255,255,255,255,0,0},
		{-1.0f,-1.0f,0.0f,255,255,255,255,0,1}
	};
	m_MapPos = m_TextureMap.find(id);
	if (m_MapPos != m_TextureMap.end())
	{
		PicInfo_Blend tmpPicInfo;
		memcpy(&tmpPicInfo, objData, sizeof(objData));
		tmpPicInfo.lpTexture = m_MapPos->second;
		m_vPicInfo_Blend[layer].push_back(tmpPicInfo);
	}
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, float angle, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BlendSet(id, layer, points, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, float angle )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BasicSet(id, layer, points, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	BlendSet(id, layer, points, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, float angle, fpoint origin )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	BasicSet(id, layer, points, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, int reverse, float angle, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BlendSet(id, layer, points, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, int reverse, float angle )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BasicSet(id, layer, points, reverse, angle, origin);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, int reverse, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	BlendSet(id, layer, points, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fRect rect, int reverse, float angle, fpoint origin )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	BasicSet(id, layer, points, reverse, angle, origin);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], float angle, unsigned char blend_colors[4] )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BlendSet(id, layer, points, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], float angle )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BasicSet(id, layer, points, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], float angle, fpoint origin, unsigned char blend_colors[4] )
{
	BlendSet(id, layer, points, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], float angle, fpoint origin )
{
	BasicSet(id, layer, points, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, unsigned char blend_colors[4] )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BlendSet(id, layer, points, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], int reverse, float angle )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	BasicSet(id, layer, points, reverse, angle, origin);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	BlendSet(id, layer, points, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetPicture( const wchar_t* id, int layer, fpoint points[4], int reverse, float angle, fpoint origin )
{
	BasicSet(id, layer, points, reverse, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBlendSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBasicSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	MulBlendSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, float angle, fpoint origin )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	MulBasicSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBlendSet(id, layer, points, position, maxPosition, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBasicSet(id, layer, points, position, maxPosition, reverse, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	MulBlendSet(id, layer, points, position, maxPosition, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fRect rect, Position position, Position maxPosition, int reverse, float angle, fpoint origin )
{
	fpoint points[4]=
	{
		{rect.left, rect.top}, {rect.left, rect.bottom}, 
		{rect.right, rect.top}, {rect.right, rect.bottom}
	};
	MulBasicSet(id, layer, points, position, maxPosition, reverse, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, unsigned char blend_colors[4] )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBlendSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBasicSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	MulBlendSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, float angle, fpoint origin )
{
	MulBasicSet(id, layer, points, position, maxPosition, NOREVERSE, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, unsigned char blend_colors[4] )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBlendSet(id, layer, points, position, maxPosition, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle )
{
	fpoint origin;
	origin.x=(points[2].x-points[0].x)/2;
	origin.y=(points[1].y-points[0].y)/2;
	MulBasicSet(id, layer, points, position, maxPosition, reverse, angle, origin);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin, unsigned char blend_colors[4] )
{
	MulBlendSet(id, layer, points, position, maxPosition, reverse, angle, origin, blend_colors);
}

void FlatRenderDx9::SetMulPicture( const wchar_t* id, int layer, fpoint points[4], Position position, Position maxPosition, int reverse, float angle, fpoint origin )
{
	MulBasicSet(id, layer, points, position, maxPosition, reverse, angle, origin);
}

void FlatRenderDx9::SetMulPointData(stPicD3DVertex *pointdata, fpoint point2Ds[4], 
				    Position position, Position maxPosition, int reverse, float angle, fpoint origin)
{
	fpoint tPoints[4];
	//���F�קK�]�w��x,y�W�L�̤j�ȥH�Ӧ����Ӧ������D,�ҥH�W�L�۰ʵ���̤j��
	if (position.x>maxPosition.x) position.x=maxPosition.x;
	if (position.y>maxPosition.y) position.y=maxPosition.y;
	//�H���W��(x,y)��(1,1)�@���з��ഫ�����`�K�Ϯy��
	tPoints[0].x=(position.x-1.0f)/maxPosition.x; tPoints[0].y=(position.y-1.0f)/maxPosition.y;
	tPoints[1].x=tPoints[0].x; tPoints[1].y=position.y/(float)maxPosition.y;
	tPoints[2].x=position.x/(float)maxPosition.x; tPoints[2].y=tPoints[0].y;
	tPoints[3].x=tPoints[2].x; tPoints[3].y=tPoints[1].y;

	switch (reverse)
	{
	case HORIZONTAL:
		//����½��,�⥪�k�I�� x �洫
		fSwap(tPoints[0].x,tPoints[2].x);
		fSwap(tPoints[1].x,tPoints[3].x);
		break;
	case VERTICAL:
		//����½��,��W�U�I�� y �洫
		fSwap(tPoints[0].y,tPoints[1].y);
		fSwap(tPoints[2].y,tPoints[3].y);
		break;
	case DIAGONAL:
		//�﨤½��=����½��+����½��
		fSwap(tPoints[0].x,tPoints[2].x);
		fSwap(tPoints[1].x,tPoints[3].x);
		fSwap(tPoints[0].y,tPoints[1].y);
		fSwap(tPoints[2].y,tPoints[3].y);
		break;
	}
	//�H�U���ೡ����SetPointData�@��
	fpoint picPoints[4];
	fpoint p1, p2;
	angle=angle*3.1415926f/180;
	p1.x=origin.x+point2Ds[0].x;
	p1.y=origin.y+point2Ds[0].y;
	for (int forx=0; forx<4; forx++)
	{
		p2.x=point2Ds[forx].x;
		p2.y=point2Ds[forx].y;
		VectorRotate(p1, p2, picPoints[forx], angle);
	}
	for(int ix=0;ix<3;ix++){

		pointdata[ix].x=picPoints[ix].x;
		pointdata[ix].y=picPoints[ix].y;
		pointdata[ix].z=0;
		pointdata[ix].tu=tPoints[ix].x;
		pointdata[ix].tv=tPoints[ix].y;
	}
	pointdata[3]=pointdata[2];
	pointdata[4].x=picPoints[3].x;
	pointdata[4].y=picPoints[3].y;
	pointdata[4].z=0;
	pointdata[4].tu=tPoints[3].x;
	pointdata[4].tv=tPoints[3].y;
	pointdata[5]=pointdata[1];
}

void FlatRenderDx9::SetMulPointData(stPicD3DVertex_Blend *pointdata, fpoint point2Ds[4], 
				    Position position, Position maxPosition, int reverse, float angle, fpoint origin)
{
	fpoint tPoints[4];
	//���F�קK�]�w��x,y�W�L�̤j�ȥH�Ӧ����Ӧ������D,�ҥH�W�L�۰ʵ���̤j��
	if (position.x>maxPosition.x) position.x=maxPosition.x;
	if (position.y>maxPosition.y) position.y=maxPosition.y;
	//�H���W��(x,y)��(1,1)�@���з��ഫ�����`�K�Ϯy��
	tPoints[0].x=(position.x-1.0f)/maxPosition.x; tPoints[0].y=(position.y-1.0f)/maxPosition.y;
	tPoints[1].x=tPoints[0].x; tPoints[1].y=(float)position.y/maxPosition.y;
	tPoints[2].x=(float)position.x/maxPosition.x; tPoints[2].y=tPoints[0].y;
	tPoints[3].x=tPoints[2].x; tPoints[3].y=tPoints[1].y;
	switch (reverse)
	{
	case HORIZONTAL:
		//����½��,�⥪�k�I�� x �洫
		fSwap(tPoints[0].x,tPoints[2].x);
		fSwap(tPoints[1].x,tPoints[3].x);
		break;
	case VERTICAL:
		//����½��,��W�U�I�� y �洫
		fSwap(tPoints[0].y,tPoints[1].y);
		fSwap(tPoints[2].y,tPoints[3].y);
		break;
	case DIAGONAL:
		//�﨤½��=����½��+����½��
		fSwap(tPoints[0].x,tPoints[2].x);
		fSwap(tPoints[1].x,tPoints[3].x);
		fSwap(tPoints[0].y,tPoints[1].y);
		fSwap(tPoints[2].y,tPoints[3].y);
		break;
	}
	//�H�U���ೡ����SetPointData�@��
	fpoint picPoints[4];
	fpoint p1, p2;
	angle=angle*MATH_PI/180;
	p1.x=origin.x+point2Ds[0].x;
	p1.y=origin.y+point2Ds[0].y;
	for (int forx=0; forx<4; forx++)
	{
		p2.x=point2Ds[forx].x;
		p2.y=point2Ds[forx].y;
		VectorRotate(p1, p2, picPoints[forx], angle);
	}
	for(int ix=0;ix<3;ix++){

		pointdata[ix].x=picPoints[ix].x;
		pointdata[ix].y=picPoints[ix].y;
		pointdata[ix].z=0;
		pointdata[ix].tu=tPoints[ix].x;
		pointdata[ix].tv=tPoints[ix].y;
	}
	pointdata[3]=pointdata[2];
	pointdata[4].x=picPoints[3].x;
	pointdata[4].y=picPoints[3].y;
	pointdata[4].z=0;
	pointdata[4].tu=tPoints[3].x;
	pointdata[4].tv=tPoints[3].y;
	pointdata[5]=pointdata[1];
}
_inline void FlatRenderDx9::fSwap(float &f1, float &f2)
{
	float ftemp;
	ftemp=f1;
	f1=f2;
	f2=ftemp;
}
//�H�U���E���O��@
void FlatRenderDx9::SetSpotLight(int layer, fpoint begPos, float direction, unsigned char begColors[3],
				 short begAlpha, unsigned char endColors[3], short endAlpha, float angle, float lightlen)
{
	if (layer >= MAX_LAYER || layer < 0)
		return;
	fpoint newpoint[3];
	TurnTrianglePoint(newpoint, begPos, direction, lightlen, angle);
	stLightPolygon tempsp[3] =
	{
		{newpoint[0].x * m_HandledWidth - 1, -newpoint[0].y * m_HandledHeight + 1, 0.0f, begColors[2], begColors[1], begColors[0], begAlpha},
		{newpoint[1].x * m_HandledWidth - 1, -newpoint[1].y * m_HandledHeight + 1, 0.0f, endColors[2], endColors[1], endColors[0], endAlpha},
		{newpoint[2].x * m_HandledWidth - 1, -newpoint[2].y * m_HandledHeight + 1, 0.0f, endColors[2], endColors[1], endColors[0], endAlpha}
	};
	stSpotLight tempsl;
	memcpy(&tempsl, tempsp, sizeof(stLightPolygon) * 3);
	m_SpotLightInfo[layer].push_back(tempsl);
}

void FlatRenderDx9::SetSpotLight(int layer, fpoint begPos, fpoint endPos,unsigned char begColors[3],
				 short begAlpha, unsigned char endColors[3], short endAlpha, float angle)
{
	if (layer >= MAX_LAYER || layer < 0)
		return;
	float lightlen, direction;
	lightlen = sqrt(pow(begPos.x-endPos.x, 2.0f) - pow(begPos.y-endPos.y, 2.0f));
	//�ΰ_�l�I�M���I���V
	//�p�G�_�l�A�M�����I�� x �t�����0�N��+-90��
	if (begPos.x - endPos.x < 0.00001f)
	{
		if (endPos.y > begPos.y)
			direction = 90.0f;
		else
			direction = -90.0f;
	}
	else
	{
		direction = atan((endPos.y - begPos.y) / (endPos.x - begPos.x)) * 360.0f / MATH_PI;
		//�b�ĤG����
		if (endPos.x - begPos.x < 0.001f && endPos.y - begPos.y > 0.001f)
			direction += 180.0f;
		//�b�ĤT����
		else if(endPos.x - begPos.x < 0.001f && endPos.y - begPos.y < 0.001f)
			direction -= 180.0f;
	}
	SetSpotLight(layer, begPos, direction, begColors, begAlpha, endColors, 
		endAlpha, angle, lightlen);
}

_inline void FlatRenderDx9::RenderSpotLight(stSpotLight* lightInfo)
{
	unsigned char beg_a, end_a;
	unsigned char nbeg_c[3];
	unsigned char nend_c[3];
	if (lightInfo->stPoint[0].color_a >= 0 && lightInfo->stPoint[1].color_a >= 0)
	{
		beg_a = (unsigned char)(lightInfo->stPoint[0].color_a );
		end_a = (unsigned char)(lightInfo->stPoint[1].color_a );
		nbeg_c[0] = lightInfo->stPoint[0].color_r;
		nbeg_c[1] = lightInfo->stPoint[0].color_g;
		nbeg_c[2] = lightInfo->stPoint[0].color_b;
		nend_c[0] = lightInfo->stPoint[1].color_r;
		nend_c[1] = lightInfo->stPoint[1].color_g;
		nend_c[2] = lightInfo->stPoint[1].color_b;
		stLightPolygon g[] = {
			{lightInfo->stPoint[0].x, lightInfo->stPoint[0].y, 0.0f, nbeg_c[2], nbeg_c[1], nbeg_c[0], beg_a},
			{lightInfo->stPoint[1].x, lightInfo->stPoint[1].y, 0.0f, nend_c[2], nend_c[1], nend_c[0], end_a},
			{lightInfo->stPoint[2].x, lightInfo->stPoint[2].y, 0.0f, nend_c[2], nend_c[1], nend_c[0], end_a},
		};	
		m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	
		m_device->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_ARGB(beg_a, beg_a, beg_a, beg_a));
		m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR );
		m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	
		m_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, g, sizeof(stLightPolygon));
	}
	else
	{
		beg_a = (unsigned char)(256 + lightInfo->stPoint[0].color_a );
		end_a = (unsigned char)(256 + lightInfo->stPoint[1].color_a );
		for (int forx = 0; forx < 3; forx++)
		{
			nbeg_c[forx] = beg_a;
			nend_c[forx] = end_a;
		}
		stLightPolygon g[] = {
			{lightInfo->stPoint[0].x, lightInfo->stPoint[0].y, 0.0f, nbeg_c[2], nbeg_c[1], nbeg_c[0], beg_a},
			{lightInfo->stPoint[1].x, lightInfo->stPoint[1].y, 0.0f, nend_c[2], nend_c[1], nend_c[0], end_a},
			{lightInfo->stPoint[2].x, lightInfo->stPoint[2].y, 0.0f, nend_c[2], nend_c[1], nend_c[0], end_a},
		};	
		m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
		m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);
		m_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, g, sizeof(stLightPolygon));
	}
}

void FlatRenderDx9::TurnTrianglePoint(fpoint tripoint[], fpoint begPos, float direction,
				      float lightlen, float angle)
{
	//�q�_�I�Vdirect��V����lightlen���ת��I
	fpoint endpoint;
	angle = angle * MATH_PI / 180.0f;
	direction = direction * MATH_PI / 180.0f;
	tripoint[0].x = begPos.x;
	tripoint[0].y = begPos.y;
	endpoint.x = begPos.x + lightlen * cos(direction);
	endpoint.y = begPos.y - lightlen * sin(direction);
	//endpoint�H���I����ߤ��O��+-�������@�b�N�O�t�~2�I
	VectorRotate(tripoint[0], endpoint, tripoint[1], -angle/2);
	VectorRotate(tripoint[0], endpoint, tripoint[2], angle/2);
}

void FlatRenderDx9::SaveNow( int w, int h, int picFormat, const wchar_t* id )
{
	LPDIRECT3DSURFACE9 surface = NULL;
	m_device->CreateOffscreenPlainSurface((unsigned int)w, (unsigned int)h, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	m_device->GetBackBuffer(0,0, D3DBACKBUFFER_TYPE_MONO, &surface);
	switch (picFormat)
	{
	case SAVE_FORMAT_BMP:
		D3DXSaveSurfaceToFile(id, D3DXIFF_BMP, surface, NULL, NULL);
		break;
	case SAVE_FORMAT_TGA:
		D3DXSaveSurfaceToFile(id, D3DXIFF_TGA, surface, NULL, NULL);
		break;
	case SAVE_FORMAT_PNG:
		D3DXSaveSurfaceToFile(id, D3DXIFF_PNG, surface, NULL, NULL);
		break;
	case SAVE_FORMAT_JPG:
		D3DXSaveSurfaceToFile(id, D3DXIFF_JPG, surface, NULL, NULL);
		break;
	case SAVE_FORMAT_DDS:
		D3DXSaveSurfaceToFile(id, D3DXIFF_DDS, surface, NULL, NULL);
		break;
	}
	surface->Release();
}
