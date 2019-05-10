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
void delMatr(int**&, const int);
template <class T>
void delMem(T*);
template <class T>
T* getMem(const int);
void fillWithRand(int**, const int, const int, const int, const int);
void fillWithHand(int**, const int, const int);
void fillWithFile(int**, const int, const int, ifstream&);
void getRange(int&, int&);
void printMatr(int**, const int, const int);
void getMatrSize(int&, int&);
void getP(int&);
void sortElsInColl(int**, const int, const int, const int);
void insertSort(int*, const int);
void sortByMP(int**, const int, const int);
void firstInput();
void secondInput();
void thirdInput();


int main()
{
	setlocale(LC_ALL, "rus");

	void(*fpoint[3])() = { firstInput, secondInput, thirdInput };
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

void firstInput() {
	int r, c, p;
	const int BUFF_SIZE = 128;
	char* road = getMem<char>(BUFF_SIZE);
	cout << "Введите путь к файлу: ";
	cin >> road;
	cout << endl;
	ifstream input(road);
	delMem(road);
	input >> r;
	input >> c;
	input >> p;
	int** X = getMemMatr(r, c);
	fillWithFile(X, r, c, input);
	printMatr(X, r, c);
	sortByMP(X, r, c);
	sortElsInColl(X, r, c, p);
	printMatr(X, r, c);

	delMatr(X, c);
}

void secondInput() {
	srand(time(0));
	int min, max, r, c, p;
	r = rand() % 100;
	c = rand() % 100;
	min = (rand() % 10) - 50;
	max = rand() % 100 - 50;
	p = rand() % 100 - 50;
	int** X = getMemMatr(r, c);
	fillWithRand(X, min, max, r, c);
	printMatr(X, r, c);
	sortByMP(X, r, c);
	sortElsInColl(X, r, c, p);
	printMatr(X, r, c);

	delMatr(X, c);
}

void thirdInput() {
	int r, c, p;
	getMatrSize(r, c);
	int** X = getMemMatr(r, c);
	getP(p);
	fillWithHand(X, r, c);
	printMatr(X, r, c);
	sortByMP(X, r, c);
	sortElsInColl(X, r, c, p);
	printMatr(X, r, c);

	delMatr(X, c);
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
			swap(*(M + j), *(M + j - 1));
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

void sortElsInColl(int** M, const int r, const int c, const int p)
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

void delMatr(int**& A, const int c)
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

template <class T>
void delMem(T* ptr) {
	delete[] ptr;
	ptr = nullptr;
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
