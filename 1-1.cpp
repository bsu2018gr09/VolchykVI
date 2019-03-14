/*
	Даны точки плоскости своими координатами в виде двух одномерных массивов(случайные числа).
	Точки плоскости рассортировать по возрастанию расстояния до прямой ax + by + c = 0.
*/

#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;

template <class T>
T* constructor(int);
int getSize();
template <class T>
void destructor(T*);
int getSize();
void fillWithRand(int*, int, int);
int getRange();
void findDistance(double*, int*, int*, int, double, double, double);
void getCoffs(double&, double&, double&);
void sortPoints(int*, int*, double*, int);
void outputPoints(int*, int*, double*, int);

int main() {

	setlocale(LC_ALL, "rus");
	srand(time(0));
	int N = getSize();
	int* X = constructor<int>(N);
	int* Y = constructor<int>(N);
	double* S = constructor<double>(N);
	int range = getRange();
	fillWithRand(X, N, range);
	fillWithRand(Y, N, range);
	double a, b, c;
	getCoffs(a, b, c);
	findDistance(S, X, Y, N, a, b, c);
	outputPoints(X, Y, S, N);
	sortPoints(X, Y, S, N);
	outputPoints(X, Y, S, N);
	destructor(X);
	destructor(Y);
	destructor(S);

	system("pause");
	return 0;
}

void outputPoints(int* X, int* Y, double* S, int N) {
	cout << "  X  Y " << "Метрика\n==============\n";
	for (int i = 0; i < N; i++) {
		cout << setw(3) << *(X + i) << setw(3) << *(Y + i) << ' ' << *(S + i) << endl;
	}
	cout << endl;
}

void sortPoints(int *X, int *Y, double *S, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if (*(S + j) > *(S + j + 1)) {
				swap(*(S + j), *(S + j + 1));
				swap(*(X + j), *(X + j + 1));
				swap(*(Y + j), *(Y + j + 1));
			}
		}
	}
}

void getCoffs(double& a, double& b, double& c) {
	cout << "Введите коэффиценты в порядке их следования: ";
	cin >> a >> b >> c;
}

void findDistance(double* S, int* X, int* Y, int N, double a, double b, double c) {
	while (N-- > 0) {
		*(S++) = (abs(*(X++)*a + *(Y++)*b + c) / sqrt((a*a) + (b*b)));
	}
}

int getRange() {
	int range;
	cout << "Введите диапазон значений: ";
	cin >> range;
	return range;
}

void fillWithRand(int* A, int N, int range) {
	while (N-- > 0)
		*(A++) = rand() % range;
}

int getSize() {
	int N;
	cout << "Введите размер массива: ";
	cin >> N;
	return N;
}

template <class T>
void destructor(T* A) {
	delete[] A;
	A = nullptr;
}

template <class T>
T* constructor(int N) {
	T* A = new T[N];
	if (!A) {
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
	return A;
}
