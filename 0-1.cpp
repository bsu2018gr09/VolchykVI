/*
	В массиве размера N, заполненного случ.числами от 0 до 10, подсчитать количество элементов, встречающихся более одного раза.
*/
#include <iostream>
#include <ctime>
#include <iomanip>

int getSize();
void printArray(int*, const int);
void countEqualValues(int*, const int);
void insertSort(int*, const int);
void fillingWithRandNumbers(int*, int, const int, const int);
void getRange(int&, int&);

int main() {

	setlocale(LC_ALL, "rus");
	int N = getSize(), a, b;
	int* arr = new int[N];
	if (!arr) {
		std::cout << "Ошибка выделения памяти\n";
		exit(1);
	}
	getRange(a, b);
	fillingWithRandNumbers(arr, N, a, b);
	printArray(arr, N);
	insertSort(arr, N);
	countEqualValues(arr, N);
	delete[] arr;
	arr = nullptr;

	system("pause");
	return 0;
}

void getRange(int& a, int& b) {
	std::cout << "Введите диапазон значений (a,b): ";
	std::cin >> a >> b;
}

int getSize() {
	int N;
	while (42) {
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

void insertSort(int* A, const int N) {
	for (int* i = A + 1; i < A + +N; i++) {
		for (int* j = i; j >= A && *(j - 1) > *j; j--) {
			int tmp = *j;
			*j = *(j - 1);
			*(j - 1) = tmp;
		}
	}
}

void countEqualValues(int* A, const int N) {
	int cnt = 0;
	for (int* i = A; i < A + N;)
	{
		int j = 0;
		while (++i < A + N && *i == *(i - 1))
			j++;
		if (j != 0)
			cnt += j + 1;
	}
	std::cout << "Количество одинаковых элементов: " << cnt << std::endl;
}

void printArray(int* A, const int N) {
	std::cout << "Массив: ";
	for (int* i = A; i < A + N; i++) {
		std::cout << std::setw(3) << *i;
	}
	std::cout << std::endl;
}