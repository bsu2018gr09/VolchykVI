/*
	Элементы массива А(N), значения которых – простые числа, расположить в порядке возрастания, не нарушая порядка следования других элементов.
*/

#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;


typedef struct Primes {
	int* num;
	int* pos;
	int size;
};

void getMem(int*&, const int&);
int getSize();
void destructor(int*);
void fillWithRand(int*, int, const int, const int);
void getRange(int&, int&);
bool isPrime(int);
void printAr(int*, int);

int countPrimes(int*, const int&);
void getPrimes(Primes&, int*, const int&);
void sortPrimes(Primes&);
void insPrimes(Primes&, int*);

int main() {

	setlocale(LC_ALL, "rus");
	srand(time(0));
	Primes P;
	int N = getSize(), min, max;
	int* X = nullptr;
	getMem(X, N);
	getRange(min, max);
	fillWithRand(X, N, min, max);
	printAr(X, N);

	P.size = countPrimes(X, N);
	getMem(P.num, P.size);
	getMem(P.pos, P.size);

	getPrimes(P, X, N);
	sortPrimes(P);
	insPrimes(P, X);
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

int countPrimes(int* A, const int& N) {
	int size{ 0 };
	for (int i = 0; i < N; i++) { if (isPrime(*(A + i))) size++; }
	return size;
}

void getPrimes(Primes& P, int* A, const int& N) {
	for (int i = 0, j = 0; i < N; i++) {
		if (isPrime(A[i])) {
			P.num[j] = *(A + i);
			P.pos[j] = i;
			j++;
		}
	}
}

void sortPrimes(Primes& P) {
	for (int i = 0; i < P.size; i++) {
		for (int j = i; j > 0 && P.num[j] < P.num[j - 1]; j--) {
			swap(P.num[j], P.num[j - 1]);
		}
	}
}

void insPrimes(Primes& P, int* A) {
	for (int i = 0; i < P.size; i++) {
		A[P.pos[i]] = P.num[i];
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

void getMem(int*& ptr, const int& size) {
	ptr = new (nothrow) int[size];
	if (!ptr) {
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
}
