/*
	В массиве размера N, заполненного случ.числами от 0 до 10, определить максимальную длину последовательности равных элементов.
*/
#include <iostream>
#include <ctime>
#include <algorithm>

int defArraySize();
void printArray(int*, const int);
void fillingWithRandNumbers(int*, int);
void maxSeries(int* A, const int N);
void getRange(int&, int&);
void getMem(int*&, const int);
void delMem(int*);

int main() {
	setlocale(LC_ALL, "rus");

	int N = defArraySize();
	int* arr;

	getMem(arr, N);
	fillingWithRandNumbers(arr, N);
	printArray(arr, N);
	maxSeries(arr, N);
	delMem(arr);

	system("pause");
	return 0;
}

void delMem(int* ptr) {
	delete[] ptr;
	ptr = nullptr;
}

void getMem(int*& ptr, const int N) {
	ptr = new (std::nothrow) int[N];
	if (!ptr) {
		std::cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
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

void fillingWithRandNumbers(int* A, int N) {
	srand(time(0));
	while (N-- > 0)
		*(A + N) = rand() % 10;
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