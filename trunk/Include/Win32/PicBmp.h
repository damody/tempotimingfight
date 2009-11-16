// BMP Loader - Codehead 08/11/04
// downloaded from http://gpwiki.org/index.php/LoadBMPCpp

#ifndef PicBmp_I603712f8m12424f0ac38mm7e5f_H
#define PicBmp_I603712f8m12424f0ac38mm7e5f_H

#include <iostream>
#include <fstream>
#include <memory.h>

#define IMG_OK              0x1
#define IMG_ERR_NO_FILE     0x2
#define IMG_ERR_MEM_FAIL    0x4
#define IMG_ERR_BAD_FORMAT  0x8
#define IMG_ERR_UNSUPPORTED 0x40

struct Color24
{
	unsigned char r,g,b;
};

class BMPImg
{
public:
	BMPImg();
	~BMPImg();
	int Load(const wchar_t* szFilename);
	int GetBPP();
	int GetWidth();
	int GetHeight();
	unsigned char* GetImg(void);       // Return a pointer to image data
	unsigned char* GetPalette(void);   // Return a pointer to VGA palette
	bool DownSampling(void);
	Color24 GetPoint(int x, int y);
	void SetPoint(int x, int y, Color24 c32);
private:
	unsigned int iWidth,iHeight,iEnc;
	short int iBPP,iPlanes;
	int iImgOffset,iDataSize;
	unsigned char *pImage, *pPalette, *pData;

	// Internal workers
	int GetFile(const wchar_t* szFilename);
	int ReadBmpHeader();
	int LoadBmpRaw();
	int LoadBmpRLE8();
	int LoadBmpPalette();
	void Downsampling(void);
	void FlipImg(); // Inverts image data, BMP is stored in reverse scanline order
	unsigned char *GetPixel(int x, int y);
};

#endif