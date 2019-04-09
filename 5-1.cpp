/*

	24 BIT ONLY

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;

typedef unsigned __int8 BYTE;
typedef unsigned __int16 WORD;
typedef unsigned __int32 DWORD;
typedef __int32 LONG;

//#########################
//Описание структуры BMP-24

struct BMPtype {
	WORD bfType;
};

struct BMPFILEHeader {
public:
	DWORD bfSize;
	DWORD bfReserved;
	DWORD bfOffBits;

};

struct BMPINFOHeader {
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
};

//#############################
//Описание цветового заполнения

struct TRIPLEclr {
public:
	BYTE blue;
	BYTE green;
	BYTE red;
};

struct GradCoords {
public:
	int x1;
	int y1;
	int x2;
	int y2;
};

struct canvasSize {
public:
	int height;
	int width;
	int padding;
};


template <class T1, class T2, class T3>
void writeBMP24(T1&, T2&, T3&, ofstream&);
template <class T>
T* getMem(const int);
template <class T>
void delMem(T*);
void getBMP24Header(BMPtype&, BMPFILEHeader&, BMPINFOHeader&, canvasSize&);
void writeCanvas(GradCoords&, TRIPLEclr&, TRIPLEclr&, ofstream&, canvasSize&);
void getRode(char*&);
void clrPicker(TRIPLEclr&);
void clrSet(TRIPLEclr&);
void horizontal();
void vertical();
void free();


int main() {

	setlocale(LC_ALL, "rus");

	void(*fpoint[])() = { horizontal, vertical, free };

	for (int i = 0; ;) {
		cout << "0 - Горизонтальный линейный градиент\n";
		cout << "1 - Вертикальный линейный градиент\n";
		cout << "2 - Произвольный линейный градиент\n";
		cout << "3 - Закрыть окно\n";
		cin >> i;
		if (i == 3) break;
		if (i >= 0 && i <= 3) { fpoint[i](); i = 0; };
	}

	return 0;
}

void writeCanvas(GradCoords& crd, TRIPLEclr& originClr, TRIPLEclr& finishClr, ofstream& o, canvasSize& size) {
	BYTE padding[3] = { 0,0,0 };

	int A = (crd.x2 - crd.x1);
	int B = (crd.y2 - crd.y1);

	int C1 = A * crd.x1 + B * crd.y1;
	int C2 = A * crd.x2 + B * crd.y2;

	for (int i = 0; i < size.height; i++) {
		for (int j = 0; j < size.width; j++) {
			int C = A * j + B * i;
			if (C <= C1) {
				writeBMP24(originClr.blue, originClr.green, originClr.red, o);
				//fwrite(padding, 1, size.padding, o);
				o.write((char*)padding, size.padding);
			}
			else if (C >= C2) {
				writeBMP24(finishClr.blue, finishClr.green, finishClr.red, o);
				//fwrite(padding, 1, size.padding, o);
				o.write((char*)padding, size.padding);
			}
			else {
				BYTE blue = (originClr.blue*(C2 - C) + finishClr.blue*(C - C1)) / (C2 - C1);
				BYTE green = (originClr.green*(C2 - C) + finishClr.green*(C - C1)) / (C2 - C1);
				BYTE red = (originClr.red*(C2 - C) + finishClr.red*(C - C1)) / (C2 - C1);
				writeBMP24(blue, green, red, o);
				//fwrite(padding, 1, size.padding, o);
				o.write((char*)padding, size.padding);
			}
		}
	}
}


template <class T1, class T2, class T3>
void writeBMP24(T1& type, T2& file, T3& info, ofstream& o) {
	//fwrite(&type, 1, sizeof(type), o);
	//fwrite(&file, 1, sizeof(file), o);
	//fwrite(&info, 1, sizeof(info), o);
	o.write((char*)&type, sizeof(type));
	o.write((char*)&file, sizeof(file));
	o.write((char*)&info, sizeof(info));
}

void getBMP24Header(BMPtype& type, BMPFILEHeader& file, BMPINFOHeader& info, canvasSize& size)
{
	size.padding = (4 - (size.width * 3) % 4) % 4;
	int fileSize = size.height * (3 * size.width + size.padding) + 54;
	type.bfType = 0x4D42;
	file.bfSize = fileSize;
	file.bfReserved = 0;
	file.bfOffBits = 54;
	info.biSize = 40;
	info.biWidth = size.width;
	info.biHeight = size.height;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = 0;
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 10;
	info.biYPelsPerMeter = 10;
	info.biClrUsed = 0;
	info.biClrImportant = 0;
}

template <class T>
T* getMem(const int size) {
	T* ptr = new (nothrow) T[size];
	if (!ptr) {
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
	return ptr;
}

template <class T>
void delMem(T* ptr) {
	delete[] ptr;
	ptr = nullptr;
}

void getRode(char*& ptr) {
	cout << "Введите расположение файла вывода: ";
	cin >> ptr;
}

void clrPicker(TRIPLEclr& clr) {
	cout << "Введите цвет (RGB): ";
	int red, green, blue;
	cin >> red >> green >> blue;
	clr.red = (BYTE)red;
	clr.green = (BYTE)green;
	clr.blue = (BYTE)blue;
}

void clrSet(TRIPLEclr& clr) {
	int flag;
	cout << "Выберите цвет:\n(1)Красный\n(2)Оранжевый\n(3)Жёлтый\n(4)Зелёный\n(5)Голубой\n(6)Синий\n(7)Фиолетовый\n(8)Чёрный\n(9)Белый\n";
	cin >> flag;
	switch (flag) {
	case 1:
		clr.red = 255;
		clr.green = 0;
		clr.blue = 0;
		break;
	case 2:
		clr.red = 255;
		clr.green = 128;
		clr.blue = 0;
		break;
	case 3:
		clr.red = 255;
		clr.green = 255;
		clr.blue = 0;
		break;
	case 4:
		clr.red = 0;
		clr.green = 255;
		clr.blue = 0;
		break;
	case 5:
		clr.red = 0;
		clr.green = 255;
		clr.blue = 255;
		break;
	case 6:
		clr.red = 0;
		clr.green = 0;
		clr.blue = 0;
		break;
	case 7:
		clr.red = 127;
		clr.green = 0;
		clr.blue = 255;
		break;
	case 8:
		clr.red = clr.green = clr.blue = 0;
		break;
	case 9:
		clr.red = clr.green = clr.blue = 255;
		break;
	}
}

void horizontal() {
	BMPtype type;
	BMPFILEHeader file;
	BMPINFOHeader info;

	TRIPLEclr originClr;
	TRIPLEclr finishClr;
	GradCoords crd;
	canvasSize size;

	int flag;
	const int BUFF_SIZE = 128;
	char* rode = getMem<char>(BUFF_SIZE);
	getRode(rode);

	ofstream o(rode, ios::binary);
	//FILE* o = fopen(rode, "wb");
	delMem(rode);

	crd.y1 = crd.y2 = 0;

	cout << "\nВведите размеры изображения (в пикселях ширина|высота): ";
	cin >> size.width >> size.height;

	getBMP24Header(type, file, info, size);
	writeBMP24(type, file, info, o);

	cout << "\nВведите отступ начала градиента от левого края: ";
	cin >> crd.x1;

	cout << "\nВведите отступ конца градиента от левого края: ";
	cin >> crd.x2;

	cout << "Выберите тип ввода цвета: \n(1)RGB\n(2)По названию\n";
	cin >> flag;

	switch (flag) {
	case 1:
		clrPicker(originClr);
		clrPicker(finishClr);
		break;
	case 2:
		clrSet(originClr);
		clrSet(finishClr);
		break;
	}

	writeCanvas(crd, originClr, finishClr, o, size);
	//fclose(o);
	o.close();
}

void vertical() {
	BMPtype type;
	BMPFILEHeader file;
	BMPINFOHeader info;

	TRIPLEclr originClr;
	TRIPLEclr finishClr;
	GradCoords crd;
	canvasSize size;

	int flag;
	const int BUFF_SIZE = 128;
	char* rode = getMem<char>(BUFF_SIZE);
	getRode(rode);

	ofstream o(rode, ios::binary);
	//FILE* o = fopen(rode, "wb");
	delMem(rode);

	crd.x1 = crd.x2 = 0;

	cout << "\nВведите размеры изображения (в пикселях ширина|высота): ";
	cin >> size.width >> size.height;

	getBMP24Header(type, file, info, size);
	writeBMP24(type, file, info, o);

	cout << "\nВведите отступ начала градиента от верхнего края: ";
	cin >> crd.y1;

	cout << "\nВведите отступ конца градиента от верхнего края: ";
	cin >> crd.y2;

	cout << "Выберите тип ввода цвета: \n(1)RGB\n(2)По названию\n";
	cin >> flag;

	switch (flag) {
	case 1:
		clrPicker(originClr);
		clrPicker(finishClr);
		break;
	case 2:
		clrSet(originClr);
		clrSet(finishClr);
		break;
	}

	writeCanvas(crd, originClr, finishClr, o, size);
	//fclose(o);
	o.close();
}

void free() {
	BMPtype type;
	BMPFILEHeader file;
	BMPINFOHeader info;

	TRIPLEclr originClr;
	TRIPLEclr finishClr;
	GradCoords crd;
	canvasSize size;

	int flag;
	const int BUFF_SIZE = 128;
	char* rode = getMem<char>(BUFF_SIZE);
	getRode(rode);

	ofstream o(rode, ios::binary);
	//FILE* o = fopen(rode, "wb");
	delMem(rode);

	cout << "\nВведите размеры изображения (в пикселях ширина|высота): ";
	cin >> size.width >> size.height;

	getBMP24Header(type, file, info, size);
	writeBMP24(type, file, info, o);

	cout << "\nВведите координаты начала градиента: ";
	cin >> crd.x1 >> crd.y1;

	cout << "\nВведите координаты конца градиента: ";
	cin >> crd.x2 >> crd.y2;

	cout << "Выберите тип ввода цвета: \n(1)RGB\n(2)По названию\n";
	cin >> flag;

	switch (flag) {
	case 1:
		clrPicker(originClr);
		clrPicker(finishClr);
		break;
	case 2:
		clrSet(originClr);
		clrSet(finishClr);
		break;
	}
	writeCanvas(crd, originClr, finishClr, o, size);
	//fclose(o);
	o.close();
}
