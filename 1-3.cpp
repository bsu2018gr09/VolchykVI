/*
	Элементы массива А(N), значения которых – простые числа, расположить в порядке возрастания, не нарушая порядка следования других элементов.
*/

#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;


int* constructor(int);
int getSize();
void destructor(int*);
int getSize();
void fillWithRand(int*, int, const int, const int);
void getRange(int&, int&);
void sortPrimes(int*, const int);
bool isPrime(int);
void printAr(int*, const int);

int main() {

	setlocale(LC_ALL, "rus");
	srand(time(0));

	int N = getSize(), min, max;
	int* X = constructor(N);
	getRange(min, max);
	fillWithRand(X, N, min, max);
	sortPrimes(X, N);
	printAr(X, N);

	destructor(X);
	system("pause");
	return 0;
}

void printAr(int* A, const int N)
{
	for (int i = 0; i < N; i++) {
		cout << setw(4) << *(A + i);
	}
	cout << endl;
}

bool isPrime(int n) {

	if (abs(n) == 2) {
		return true;
	}
	else if (abs(n) <= 1 || abs(n) == 0) {
		return false;
	}
	int end = sqrt(abs(n));
	for (int i = 2; i <= end; i++) {
		if (n%i == 0) {
			return false;
		}
	}
	return true;
}

void sortPrimes(int* A, const int N)
{
	int amount = N - 1;
	for (int i = 0; i < N; i++) {
		int flag = 0;
		int* primeNow = nullptr;
		int* primeBefore = nullptr;
		for (int* j = A; j < A + amount; j++)
		{
			if (primeNow && isPrime(*j) && (*j < *primeNow))
			{
				flag = 1;
				swap(*primeNow, *j);
				primeBefore = primeNow;
				primeNow = j;
			}
			else if (isPrime(*j))
			{
				primeBefore = primeNow;
				primeNow = j;
			}
		}
		amount = primeBefore - A;
		if (!flag) break;
	}
}

void getRange(int& min, int& max)
{
	cout << "Введите диапазон значений (a,b): ";
	cin >> min >> max;
}


void fillWithRand(int* A, int N, const int min, const int max)
{
	while (N-- > 0)
		*(A++) = rand() % (max - min) + min;
}

int getSize()
{
	int N;
	cout << "Введите размер массива: ";
	cin >> N;
	return N;
}

void destructor(int* A) {
	delete[] A;
	A = nullptr;
}

int* constructor(int N) {
	int* A = new (nothrow) int[N];
	if (!A) {
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
	return A;
}
