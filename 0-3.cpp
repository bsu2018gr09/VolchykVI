/*
	Массив чисел размера N проинициализировать случайными числами из промежутка от -N до N.
	Написать функцию циклического сдвига элементов массива вправо на k элементов.
*/
#include <iostream>
#include <ctime>



int defArraySize();
void printArray(int*, const int);
void fillingWithRandNumbers(int*, int, const int, const int);
void movingArray(int*, const int, const int);
void getRange(int&, int&);
void getMove(int&);


int main() {

	setlocale(LC_ALL, "rus");
	int N = defArraySize(), a, b, k;
	int* arr = new (std::nothrow) int[N];
	if (!arr) {
		std::cout << "Memory allocation error";
		exit(1);
	}
	getRange(a, b);
	getMove(k);
	fillingWithRandNumbers(arr, N, a, b);
	printArray(arr, N);
	movingArray(arr, N, k);
	printArray(arr, N);

	delete[] arr;
	arr = nullptr;

	system("pause");
	return 0;
}

void getMove(int& k) {
	std::cout << "Введите дальность сдвига массива: ";
	std::cin >> k;
}

void getRange(int& a, int& b) {
	std::cout << "Введите диапазон значений (a,b): ";
	std::cin >> a >> b;
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

void printArray(int* A, const int N) {
	std::cout << "Массив: ";
	for (int* i = A; i < A + N; i++) {
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
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