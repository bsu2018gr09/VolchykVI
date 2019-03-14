/*
	В массиве размера N, заполненного случ.числами от 0 до 10, определить максимальную длину последовательности равных элементов.
*/
#include <iostream>
#include <ctime>
#include <algorithm>



int defArraySize();
void printArray(int*, const int);
void fillingWithRandNumbers(int*, int, const int, const int);
void maxSeries(int* A, const int N);
void getRange(int&, int&);

int main() {

	setlocale(LC_ALL, "rus");
	int N = defArraySize(), a, b;
	int* arr = new (std::nothrow) int[N];
	if (!arr) {
		std::cout << "Ошибка выделения памяти\n";
		exit(1);
	}
	getRange(a, b);
	fillingWithRandNumbers(arr, N, a, b);
	printArray(arr, N);
	maxSeries(arr, N);

	delete[] arr;
	arr = nullptr;

	system("pause");
	return 0;
}

void getRange(int& a, int& b) {
	std::cout << "Введите диапазон значений (a,b): ";
	std::cin >> a >> b;
}

void printArray(int* A, const int N) {
	std::cout << "Массив: ";
	for (int* i = A; i < A + N; i++) {
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
}

int defArraySize() {
	int N;
	while (true) {
		std::cout << "Введите размер массива: ";
		std::cin >> N;
		if (N > 0)
			break;
		else
			std::cout << "Введите положительное значение!\n";
	}
	return N;
}

void fillingWithRandNumbers(int* A, int N, const int a, const int b) {
	srand(time(0));
	while (N-- > 0)
		*(A + N) = rand() % (b - a) + a;
}

void maxSeries(int* A, const int N) {
	int maxL = 0, real = 1;
	for (int* i = A; i < A + N - 1; i++) {
		if (*i == *(i + 1)) {
			real++;
		}
		else {
			maxL = std::max(maxL, real);
			real = 1;
		}
	}
	std::cout << "Максимальная длина ряда одинаковых элементов: " << maxL << std::endl;
}