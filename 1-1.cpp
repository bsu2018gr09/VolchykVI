/*
	Даны точки плоскости своими координатами в виде двух одномерных массивов(случайные числа).
	Точки плоскости рассортировать по возрастанию расстояния до прямой ax + by + c = 0.
*/

#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;

typedef struct point {
	int X;
	int Y;
	double S;
};

template <class T>
T* constructor(int);
int getSize();
template <class T>
void destructor(T*);
int getSize();
void fillWithRand(point*, int, int);
int getRange();
void findDistance(point*, int, double, double, double);
void getCoffs(double&, double&, double&);
void sortPoints(point*, int);
void outputPoints(point*, int);



int main() {

	setlocale(LC_ALL, "rus");
	srand(time(0));
	int N = getSize();
	point* V = constructor<point>(N);
	int range = getRange();
	fillWithRand(V, N, range);
	double a, b, c;
	getCoffs(a, b, c);
	findDistance(V, N, a, b, c);
	outputPoints(V, N);
	sortPoints(V, N);
	outputPoints(V, N);
	destructor<point>(V);

	system("pause");
	return 0;
}

void outputPoints(point* V, int N) {
	cout << "  X  Y " << "Метрика\n==============\n";
	for (int i = 0; i < N; i++) {
		cout << setw(3) << (V + i)->X << setw(3) << (V + i)->Y << ' ' << (V + i)->S << endl;
	}
	cout << endl;
}

void sortPoints(point* V, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if ((V + j)->S > (V + j + 1)->S) { swap(*(V + j), *(V + j + 1)); }
		}
	}
}

void getCoffs(double& a, double& b, double& c) {
	cout << "Введите коэффиценты в порядке их следования: ";
	cin >> a >> b >> c;
}

void findDistance(point* V, int N, double a, double b, double c) {
	double l = sqrt((a*a) + (b*b));
	for (int i = 0; i < N; i++) {
		(V + i)->S = abs((V + i)->X*a + (V + i)->Y*b + c) / l;
	}
}

int getRange() {
	int range;
	cout << "Введите диапазон значений: ";
	cin >> range;
	return range;
}

void fillWithRand(point* V, int N, int range) {
	for (int i = 0; i < N; i++) {
		(V + i)->X = rand() % range;
		(V + i)->Y = rand() % range;
	}
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
