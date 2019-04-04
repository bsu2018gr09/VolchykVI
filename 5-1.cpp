#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;

const int bytePerPixel = 3;

typedef unsigned __int8 BYTE;
typedef unsigned __int16 WORD;
typedef unsigned __int32 DWORD;
typedef __int32 LONG;

typedef struct {
public: 
	BYTE blue;
	BYTE green;
	BYTE red;
} TRIPLEclr;

typedef struct {
	WORD bfType;
} BMPtype;

typedef struct {
public:
	DWORD bfSize;
	DWORD bfReserved;
	DWORD bfOffBits;

} BMPFILEHeader;

typedef struct {
public:
	DWORD biSize;
	DWORD biWidth;
	DWORD biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BMPINFOHeader;

int main() {

	FILE* o = fopen("d://file.bmp", "wb");
	const int x = 800;
	const int y = 500;

	int paddingSize = (4 - (x*bytePerPixel) % 4) % 4;
	int fileSize = y * (bytePerPixel*x + paddingSize) + 54;

	BMPtype type;
	BMPFILEHeader file;
	BMPINFOHeader info;
	TRIPLEclr clr;
	TRIPLEclr tmpXclr;
	TRIPLEclr tmpYclr;

	type.bfType = 0x4D42;
	file.bfSize = fileSize;
	file.bfReserved = 0;
	file.bfOffBits = 54;
	info.biSize = 40;
	info.biWidth = x;
	info.biHeight = y;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = 0;
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 10;
	info.biYPelsPerMeter = 10;
	info.biClrUsed = 0;
	info.biClrImportant = 0;

	fwrite(&type, 1, sizeof(type), o);
	fwrite(&file, 1, sizeof(file), o);
	fwrite(&info, 1, sizeof(info), o);


	tmpXclr.red = 0;
	tmpXclr.green = 0;
	tmpXclr.blue = 0;

	unsigned char padding[3] = { 0,0,0 };

	int ii = 0;
	int jj = 0;

	for (int i = 1; i <= y; i++) {
		for (int j = 1; j <= x; j++) {
			clr.blue = j / 7;
			clr.green = j / 7;
			clr.red = j / 7;
			fwrite(&clr.blue, 1, 1, o);
			fwrite(&clr.green, 1, 1, o);
			fwrite(&clr.red, 1, 1, o);
			fwrite(padding, 1, paddingSize, o);
			clr.red = tmpXclr.red;
			clr.green = tmpXclr.green;
			clr.blue = tmpXclr.blue;
		}
	}

	return 0;
}