/*
	В тексте найти предложение, содержащее наибольшее количество слов, начинающихся на заданную букву.
	Отсортировать все слова найденного предложения в алфавитном порядке.
*/
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

const int TMP_SIZE = 100;
const int BUFF_SIZE = 1024;
const char* LOCATION_INP = "D:/Repositos/input.txt";
const char* LOCATION_OUT = "D:/Repositos/output.txt";

void checkInp(ifstream&);
void checkOut(ofstream&);
void getChar(char&);
void getMem(char*&, const int);
void getPtr(char**&, const int);
void delMem(char*&);
void delPtr(char**&);
void sortString(char**, const int);
void writeIntoArray(char*&, char**, int&, int&);
void logic(int&, int&, char**&, char**&, char*&, ifstream&, ofstream&, char);
void cntEquals(int&, const int, char**&, char);
void copyArr(char**&, char**&, const int);
void prntArr(char**&, const int, ofstream&);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	char ch;
	char* buff;
	char** tmpStr;
	char** cmpStr;
	ifstream input;
	ofstream output;
	int maxPos = 0;
	int maxWords = 0;

	input.open(LOCATION_INP);
	output.open(LOCATION_OUT);

	getMem(buff, BUFF_SIZE);
	getPtr(tmpStr, TMP_SIZE);
	getPtr(cmpStr, TMP_SIZE);
	getChar(ch);
	checkInp(input);
	checkOut(output);
	logic(maxWords, maxPos, cmpStr, tmpStr, buff, input, output, ch);
	sortString(cmpStr, maxPos);
	prntArr(cmpStr, maxPos, output);


	delPtr(tmpStr);
	delPtr(cmpStr);
	delMem(buff);

	input.close();
	output.close();

	system("pause");
	return 0;
}

void logic(int& maxWords, int& maxPos, char**& cmpStr, char**& tmpStr, char*& buff, ifstream& input, ofstream& output, char ch)
{
	while (42)
	{
		int pos = 0;
		int count = 0;

		input.getline(buff, BUFF_SIZE, '.');
		writeIntoArray(buff, tmpStr, pos, count);

		cntEquals(count, pos, tmpStr, ch);

		if (count > maxWords)
		{
			for (int i = 0; i < maxPos; i++) delMem(*(cmpStr + i));
			maxWords = count;
			maxPos = pos;
			copyArr(cmpStr, tmpStr, maxPos);
		}

		prntArr(tmpStr, pos, output);

		for (int i = 0; i < pos; i++) delMem(*(tmpStr + i));
		if (input.eof()) break;
		output << endl;
	}
}

void prntArr(char**& str, const int size, ofstream& out) {
	for (int i = 0; i < size; i++) {
		out << *(str + i) << ' ';
	}
	out << endl;
}

void copyArr(char**& dest, char**& orig, const int size)
{
	for (int i = 0; i < size; i++)
	{
		getMem(*(dest + i), strlen(orig[i]) + 1);
		strcpy_s(*(dest + i), (strlen(orig[i]) + 1), *(orig + i));
	}
}

void cntEquals(int& count, const int size, char**& str, char ch) {
	for (int i = 0; i < size; i++) if (toupper(**(str + i)) == toupper(ch)) count++;
}

void checkOut(ofstream& out)
{
	if (!out)
	{
		cout << "Невозможно создать файл вывода!\n";
		exit(1);
	}
}

void checkInp(ifstream& inp)
{
	if (!inp) {
		cout << "Невозможно открыть файл ввода!\n";
		exit(1);
	}
};

void writeIntoArray(char*& orig, char** dest, int& pos, int& count)
{
	char* nexttoken = NULL;
	char* word = strtok_s(orig, " ,.-()\t;", &nexttoken);
	while (word != NULL)
	{
		int wordSize = strlen(word);
		getMem(*(dest + pos), wordSize + 1);
		strcpy_s(*(dest + pos), wordSize + 1, word);
		pos++;
		word = strtok_s(NULL, " ,.-()\t;", &nexttoken);
	}
}

void sortString(char** str, const int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1, k; j < size; j++)
		{
			k = 0;
			if (str[i] != str[j])
			{
				while (str[i][k] == str[j][k]) k++;
				if (toupper(str[i][k]) > toupper(str[j][k])) swap(str[i], str[j]);
			}
		}
	}
}

void delMem(char*& str)
{
	delete[] str;
	str = nullptr;
}

void getMem(char*& str, const int size)
{
	str = new (nothrow) char[size];
	if (!str)
	{
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
}

void getChar(char& ch)
{
	cout << "Введите букву: ";
	cin >> ch;
}

void getPtr(char**& str, const int size)
{
	str = new (nothrow) char*[size];
	if (!str) {
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
}

void delPtr(char**& str) {
	delete[] str;
	str = nullptr;
}