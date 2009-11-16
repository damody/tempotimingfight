
#ifndef _DATATYPE_
#define _DATATYPE_

#include <d3d9.h>
#include <d3dx9tex.h>
#include <functional>
enum Reverse {NOREVERSE, HORIZONTAL, VERTICAL, DIAGONAL};
enum PicLayer {L1_BACKGROUND, L2_SHADOW, L3_ROLE_SKILL, L4_BLEND_ROLE, L5_LIGHT_SKILL, L6_INTERFACE};
struct fColor //專門存顏色的結構可輸出 unsigned char[4]
{
	union {
		float Color[4];
		struct {
			float A,R,G,B;
		};
	};
	union {
		unsigned char cColor[4];
		struct {
			unsigned char cA,cR,cG,cB;
		};
	};
	fColor()
	{
	}
	fColor(const unsigned char iColor[4])
	{
		for (int i = 0;i < 4;i++)
		{
			cColor[i] = iColor[i];
			Color[i] = (float)iColor[i];
		}
	}
	void UpdateFloat()
	{
		for (int i = 0;i < 4;i++)
		{
			Color[i] = (float)cColor[i];
		}
	}
	void UpdateUCher()
	{
		for (int i = 0;i < 4;i++)
		{
			cColor[i] = (unsigned char)Color[i];
		}
	}
	unsigned char* UChar()
	{
		return cColor;
	}
	unsigned char* GetUChar()
	{
		for (int i = 0;i < 4;i++)
		{
			cColor[i] = (unsigned char)Color[i];
		}
		return cColor;
	}
	fColor operator+(const fColor& rhs)
	{
		fColor tmp;
		for (int i=0;i < 4;i++)
		{
			tmp.Color[i] = Color[i] + rhs.Color[i];
		}
		return tmp;
	};
	fColor& operator+=(const fColor& rhs)
	{
		for (int i=0;i < 4;i++)
		{
			Color[i] += rhs.Color[i];
		}
		return *this;
	};
	fColor operator-(const fColor& rhs)
	{
		fColor tmp;
		for (int i=0;i < 4;i++)
		{
			tmp.Color[i] = Color[i] - rhs.Color[i];
		}
		return tmp;
	};
	fColor& operator-=(const fColor& rhs)
	{
		for (int i=0;i < 4;i++)
		{
			Color[i] -= rhs.Color[i];
		}
		return *this;
	};
	fColor operator*(const float num)
	{
		fColor tmp;
		for (int i=0;i < 4;i++)
		{
			tmp.Color[i] = Color[i] * num;
		}
		return tmp;
	};
	fColor& operator*=(const float num)
	{
		for (int i=0;i < 4;i++)
		{
			Color[i] *= num;
		}
		return *this;
	};
	fColor operator/(const float num)
	{
		fColor tmp;
		for (int i=0;i < 4;i++)
		{
			tmp.Color[i] = Color[i] / num;
		}
		return tmp;
	};
	fColor& operator/=(const float num)
	{
		for (int i=0;i < 4;i++)
		{
			Color[i] /= num;
		}
		return *this;
	};
	fColor& operator=(const fColor& rhs)
	{
		for (int i=0;i < 4;i++)
		{
			Color[i] = rhs.Color[i];
		}
		return *this;
	};
};

struct fRect
{
	float left, right, top, bottom;
	fRect operator+(const fRect& rect)
	{
		fRect tmp;
		tmp.left = left + rect.left;
		tmp.right = right + rect.right;
		tmp.top = top + rect.top;
		tmp.bottom = bottom + rect.bottom;
		return tmp;
	};
	fRect& operator+=(const fRect& rect)
	{
		left += rect.left;
		right += rect.right;
		top += rect.top;
		bottom += rect.bottom;
		return *this;
	};
	fRect operator-(const fRect& rect)
	{
		fRect tmp;
		tmp.left = left - rect.left;
		tmp.right = right - rect.right;
		tmp.top = top - rect.top;
		tmp.bottom = bottom - rect.bottom;
		return tmp;
	};
	fRect& operator-=(const fRect& rect)
	{
		left -= rect.left;
		right -= rect.right;
		top -= rect.top;
		bottom -= rect.bottom;
		return *this;
	};
	fRect operator*(const float num)
	{
		fRect tmp;
		tmp.left = left * num;
		tmp.right = right * num;
		tmp.top = top * num;
		tmp.bottom = bottom * num;
		return tmp;
	};
	fRect& operator*=(const float num)
	{
		left *= num;
		right *= num;
		top *= num;
		bottom *= num;
		return *this;
	};
	fRect operator/(const float num)
	{
		fRect tmp;
		tmp.left = left / num;
		tmp.right = right / num;
		tmp.top = top / num;
		tmp.bottom = bottom / num;
		return tmp;
	};
	fRect& operator/=(const float num)
	{
		left /= num;
		right /= num;
		top /= num;
		bottom /= num;
		return *this;
	};
	fRect& operator=(const fRect& rect)
	{
		left = rect.left;
		right = rect.right;
		top = rect.top;
		bottom = rect.bottom;
		return *this;
	};
	bool operator==(const fRect& rect)
	{
		if (left == rect.left && right == rect.right && top == rect.top && bottom == rect.bottom)
			return true;
		return false;
	};
};
struct fpoint
{
	float x,y;
};
//分格圖的行列結構
struct Position
{
	int x,y;
};

struct stPicD3DVertex
{
	float x, y, z;
	float tu, tv;
};
//正常版圖片資訊
struct PicInfo 
{
	int layer;
	stPicD3DVertex stPoint[6];
	LPDIRECT3DTEXTURE9* lpTexture;
};
//混色版頂點結構
struct stPicD3DVertex_Blend
{
	float x, y, z;
	unsigned char color_b, color_g, color_r, color_a;
	float tu, tv;
};	
//混色版圖片資訊
struct PicInfo_Blend 
{
	int layer;
	stPicD3DVertex_Blend stPoint[6];
	LPDIRECT3DTEXTURE9* lpTexture;
};
//光點結構
struct stLightPolygon
{
	float x, y, z;
	unsigned char color_b, color_g, color_r;
	short color_a;
};
struct stSpotLight
{
	stLightPolygon stPoint[3];
};
struct wcharcmp
	: public std::binary_function<wchar_t*, wchar_t*, bool>
{	// functor for operator<
	bool operator()(const wchar_t* _Left, const wchar_t* _Right) const
	{	// apply operator< to operands
		return wcscmp(_Left, _Right) < 0;
	}
};
struct Feature
{};
template <class _PeopleType>
struct CSIE
{
	Feature ComputerTechology;
};
template <class _Department>
	struct NTUST
	{
		Feature strong,intelligent,strive,Powerful;
	};
//NTUST<CSIE<Student> > Name;
#endif //_DATATYPE_