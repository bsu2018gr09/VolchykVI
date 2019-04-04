/*
	В массиве А(N,M) расположить в порядке возрастания элементы столбцов, максимальный элемент которых не превосходит заданную величину р,
	а сами столбцы расположить в порядке возрастания количества перемен знаков в каждом столбце.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <fstream>
using namespace std;

int** getMemMatr(const int, const int);
void destructor(int**&, const int);
void fillWithRand(int**, const int, const int, const int, const int);
void fillWithHand(int**, const int, const int);
void fillWithFile(int**, const int, const int, ifstream&);
void getRange(int&, int&);
void printMatr(int**, const int, const int);
void getMatrSize(int&, int&);
void getP(int&);
void sortColls(int**, const int, const int, const int);
void insertSort(int*, const int);
void sortByMP(int**, const int, const int);

void firstInput() {
	int min, max, r, c, p;

	char* roadTo = new char[128];
	cout << "Введите путь к файлу: ";
	cin >> roadTo;
	cout << endl;
	ifstream input(roadTo);
	input >> r;
	input >> c;
	input >> p;
	int** X = getMemMatr(r, c);



	fillWithFile(X, r, c, input);
	printMatr(X, r, c);
	sortByMP(X, r, c);
	sortColls(X, r, c, p);
	printMatr(X, r, c);

	destructor(X, c);
	delete[] roadTo;
}

void secondInput() {
	srand(time(0));
	int min, max, r, c, p;
	r = rand() % 100;
	c = rand() % 100;
	min = rand() % 100 - 50;
	max = rand() % 100 - 50;
	p = rand() % 100 - 50;
	int** X = getMemMatr(r, c);
	fillWithRand(X, min, max, r, c);
	printMatr(X, r, c);
	sortByMP(X, r, c);
	sortColls(X, r, c, p);
	printMatr(X, r, c);

	destructor(X, c);
	cout << "Кушатб подано!\n";
}

void thirdInput() {
	int r, c, p;
	getMatrSize(r, c);
	int** X = getMemMatr(r, c);
	getP(p);
	fillWithHand(X, r, c);
	printMatr(X, r, c);
	sortByMP(X, r, c);
	sortColls(X, r, c, p);
	printMatr(X, r, c);

	destructor(X, c);
	cout << "Кушатб подано!\n";
}

int main()
{

	setlocale(LC_ALL, "rus");
	
	void(*fpoint[3])() = {firstInput, secondInput, thirdInput};



	for (int i = 0; ;) {
		cout << "0 - Хочу прочитать все данные из файла!\n";
		cout << "1 - Не хочу вводить значения, пусть они генерируются сами!\n";
		cout << "2 - Хочу ввести значения сам!\n";
		cout << "3 - Завершить сеанс!\n";
		cin >> i;
		if (i == 3) break;
		if (i >= 0 && i <= 3) fpoint[i]();
	}
	return 0;
}

void sortByMP(int** M, const int r, const int c)
{
	int* A = new int[c];
	for (int i = 0; i < c; i++)
	{
		*(A + i) = 0;
		for (int j = 0; j < r - 1; j++)
		{
			if (*(*(M + i) + j) < 0 && *(*(M + i) + j + 1) >= 0 || *(*(M + i) + j) >= 0 && *(*(M + i) + j + 1) < 0)
			{
				*(A + i) += 1;
			}
		}
	}

	for (int i = 1; i < c; i++) {
		for (int j = i; j >= 0 && *(A + j - 1) > *(A + j); j--) {
			swap(*(A + j), *(A + j - 1));
			for (int k = 0; k < r; k++) {
				swap(*(*(M + j) + k), *(*(M + j - 1) + k));
			}
		}
	}

	delete[] A;
	A = nullptr;
}

void insertSort(int* A, const int N)
{
	for (int* i = A + 1; i < A + N; i++)
	{
		for (int* j = i; j >= A && *(j - 1) > *j; j--)
		{
			swap(*j, *(j - 1));
		}
	}
}

void sortColls(int** M, const int r, const int c, const int p)
{
	int max;
	for (int i = 0; i < c; i++)
	{
		max = **(M + i);
		for (int j = 1; j < r; j++)
		{
			if (*(*(M + i) + j) > max)
			{
				max = *(*(M + i) + j);
			}
		}
		if (max <= p)
		{
			insertSort(*(M + i), r);
		}
	}
}

void getP(int& p)
{
	cout << "Введите p: ";
	cin >> p;
}

void getMatrSize(int& r, int& c)
{
	cout << "Введите количество строк и столбцов: ";
	cin >> r >> c;
}

void printMatr(int** M, const int r, const int c)
{
	cout << "Матрица:\n";
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << setw(3) << *(*(M + j) + i);
		}
		cout << endl;
	}
	cout << endl;
}

void getRange(int& min, int& max)
{
	cout << "Введите диапазон значений (a,b): ";
	cin >> min >> max;
}

void fillWithFile(int** A, const int r, const int c, ifstream& input)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			input >> *(*(A + j) + i);
		}
	}
}

void fillWithHand(int** A, const int r, const int c)
{
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r; j++)
		{
			cin >> *(*(A + i) + j);
		}
	}
}

void fillWithRand(int** A, const int min, const int max, const int r, const int c)
{
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r; j++)
		{
			*(*(A + i) + j) = rand() % (max - min) + min;
		}
	}
}

void destructor(int**& A, const int c)
{
	for (int i = 0; i < c; i++)
	{
		delete[] * (A + i);
		*(A + i) = nullptr;
	}
	delete[] A;
	A = nullptr;
}

int** getMemMatr(const int r, const int c)
{
	int** A = new (nothrow) int*[c];
	if (!A)
	{
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
	for (int i = 0; i < c; i++)
	{
		*(A + i) = new (nothrow) int[r];
		if (!*(A + i)) {
			cout << "Ошибка выделения памяти!\n";
			exit(1);
		}
	}
	return A;
}