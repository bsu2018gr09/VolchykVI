/*
	Положительные элементы массива А(N) переставить в конец массива, сохраняя порядок следования.
	Отрицательные элементы расположить в порядке убывания. Дополнительный массив не использовать.
*/

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int* constructor(int);
int getSize();
void destructor(int*);
void fillWithRand(int*, int, const int, const int);
void getRange(int&, int&);
void sortPos(int*, int);
void movingArray(int*, const int, const int);
void insertSort(int*, const int);
void printAr(int *, int);


int main() {

	setlocale(LC_ALL, "rus");
	srand(time(0));

	int N = getSize(), min, max;
	int* X = constructor(N);
	getRange(min, max);
	fillWithRand(X, N, min, max);
	printAr((int*)X, N);
	sortPos(X, N);
	insertSort(X, N);
	printAr((int*)X, N);
	destructor(X);

	system("pause");
	return 0;
}

void insertSort(int* A, const int N) {
	for (int* i = A + 1; i < A + +N; i++) {
		for (int* j = i; (j > A) && (*j > *(j - 1)) && (*j < 0); j--) {
			swap(*(j - 1), *j);
		}
	}
}

void printAr(int* A, int N) {
	while (N-- > 0) {
		cout << *A++ << ' ';
	}
	cout << endl;
}

void sortPos(int* A, int N) {
	int k{ 0 }, i{ 0 };
	for (; i < N; i++) {
		if (*(A + i) >= 0)
			swap(*(A + i), *(A + k++));
	}
	movingArray(A, N, (i - k));// совсем никакой оптимизации (((
}

void getRange(int& min, int& max) {
	cout << "Введите  диапазон значений (a,b): ";
	cin >> min >> max;
}

void fillWithRand(int* A, int N, const int min, const int max) {
	while (N-- > 0)
		*(A++) = rand() % (max - min) + min;
}

int getSize() {
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

void movingArray(int* A, const int N, const int k) {
	for (int j = k; j > 0; j--) {
		int tmp = *(A + N - 1);
		for (int* i = A + N - 1; i > A; i--) {
			*i = *(i - 1);
		}
		*A = tmp;
	}
}
