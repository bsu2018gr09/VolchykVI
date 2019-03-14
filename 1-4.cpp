/*
	void give_memory(int**&, int, int)//первый способ. ѕодумайте, почему об€зательно надо тут &
	int** give_memory(int, int)//второй способ. ѕодумайте, можно ли и безопасно ли тут нап≥сать int**& give_memory
	void init_array(int **,int,int)
	void print_array(int **,int,int)
	void free_array(int **,int)
*/

#include <iostream>
#include <ctime>


using namespace std;

void give_memory(int**&, int, int);
int** give_memory(int, int);
void init_array(int**, int, int);
void print_array(int**, int, int);
void free_array(int**, int);

int main() {

	int **M;
	system("pause");
	return 0;
}

void free_array(int** M, int c) {
	for (int i = 0; i < c; i++) {
		delete[] * (M + i);
		*(M + i) = nullptr;
	}
	delete[] M;
	M = nullptr;
}

void print_array(int**M, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << *(*(M + j) + i) << ' ';
		}
		cout << endl;
	}
}

void init_array(int** M, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			*(*(M + j) + i) = rand() % 10;
		}
	}
}

int** give_memory(int r, int c) {
	int** M = new (nothrow) int *[r];
	for (int i = 0; i < c; i++) {
		*(M + i) = new (nothrow) int[c];
	}
	return M;
}

void give_memory(int**&M, int r, int c) {
	M = new int *[c];
	if (!M) {
		cout << "Allocation error\n";
		exit(1);
	}
	for (int i = 0; i < r; i++) {
		*(M + i) = new int[r];
	}
}