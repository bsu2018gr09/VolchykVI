/*
	Расположить в порядке возрастания элементы массива А(N), начиная с k-го элемента.
*/
#include <iostream>
#include <ctime>



int getSize();
void printArray(int*, const int);
void fillingWithRandNumbers(int*, int, const int, const int);
void insertSort(int*, const int, const int);
void getRange(int&, int&);
void getNum(int&);

int main() {

	setlocale(LC_ALL, "rus");
	int N = getSize();
	int* arr = new (std::nothrow) int[N], a, b, k;
	if (!arr) {
		std::cout << "Ошибка выделения памяти\n";
		exit(1);
	}
	getRange(a, b);
	getNum(k);
	fillingWithRandNumbers(arr, N, a, b);
	printArray(arr, N);
	insertSort(arr, N, k);
	printArray(arr, N);

	delete[] arr;
	arr = nullptr;

	system("pause");
	return 0;
}

void getNum(int& k) {
	std::cout << "Введите номер элемента:";
	std::cin >> k;
}

void getRange(int& a, int& b) {
	std::cout << "Введите диапазаон значений (a,b): ";
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

void printArray(int* A, const int N) {
	for (int* i{ A }; i < A + N; i++) {
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
}

void insertSort(int* A, const int N, const int k) {
	for (int* i = A + 1 + k; i < A + +N; i++) {
		for (int* j = i; j >= A + k && *(j - 1) > *j; j--) {
			int tmp = *j;
			*j = *(j - 1);
			*(j - 1) = tmp;
		}
	}
}
