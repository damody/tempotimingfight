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

#ifndef EditBitMap_H
#define EditBitMap_H

#include <vector>

struct c32
{
	unsigned char B,G,R,A;
	bool operator==(c32 &rhs)
	{
		return (B == rhs.B && G == rhs.G && R == rhs.R && A == rhs.A);
	}
	bool operator!=(c32 &rhs)
	{
		return (B != rhs.B || G != rhs.G || R != rhs.R || A != rhs.A);
	}
	bool operator==(int rhs)
	{
		return (B == (unsigned char)rhs && G == (unsigned char)rhs && R == (unsigned char)rhs && A == (unsigned char)rhs);
	}
	bool operator!=(int rhs)
	{
		return (B != (unsigned char)rhs || G != (unsigned char)rhs || R != (unsigned char)rhs || A != (unsigned char)rhs);
	}
};

class EditBitMap
{
public:
	EditBitMap();
	~EditBitMap();
	void NewMap(int w, int h);
	c32* GetPixel(int x, int y);
	void SetPixel(int x, int y, c32 color);
	c32** GetMartrix(int x, int y, int radius);
	void ReleaseMartrix();
	bool checkIndex(int w, int h,int x, int y)
	{ return (x>=0 && y>=0 && x<w && y<h); };
	int iWidth,iHeight;
	long lImageSize;
	c32 *pImage;
private:
	struct c32Matrix
	{
		c32** lp;
		int size;
	};
	std::vector<c32Matrix> m_MatrixMange;
	std::vector<c32Matrix>::iterator m_MatrixMangePos;
};

#endif //EditBitMap_H