/*
	Примечание:
		Главное, помнить: простота - залог успеха!

	Код ниже может вызвать у ревьювера неприятное жжение в некоторых частях тела.
	Настоятельно рекомендую быть готовым к этому и не впадать в крайности!
	Я пытался сделать лучше, но получилось как всегда.
*/
/*
	Найти и удалить все слова в тексте, содержащие 1 слог. Вывести все такие слова на экран.
*/
#include <iostream>
#include <cstring>
#include <Windows.h>


using namespace std;

void printStr(char*[], const int);
void getMem(char**, const int);
void sortStr(char*, char*[], char*[], int&, int&);
void delMem(char**, const int);

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	const int BUFF_SIZE = 1024;

	char buff[BUFF_SIZE];
	char* vowelStr[BUFF_SIZE];
	char* otherStr[BUFF_SIZE];
	int posOth = 0;
	int posVow = 0;

	cin.getline(buff, BUFF_SIZE);
	sortStr(buff, vowelStr, otherStr, posVow, posOth);

	printStr(otherStr, posOth);
	printStr(vowelStr, posVow);	
	
	delMem(vowelStr, posVow);
	delMem(otherStr, posOth);

	system("pause");
	return 0;
}

void sortStr(char* line, char* vow[], char* oth[], int& posVow, int& posOth) {


	const char* check = "уеёыаоэяиюУЕЁЫАОЭЯИЮeyuioaEYUIOA";
	char* nexttoken = NULL;

	char* word = strtok_s(line, " ,.-!?;\t", &nexttoken);

	while (word != NULL)
	{
		int count = 0;
		int word_size = strlen(word);

		for (int k = 0; k < word_size; k++) {
			if (strchr(check, word[k])) count++;
		}

		if (count == 1) {
			getMem(vow + posVow, word_size + 1);
			strcpy_s(vow[posVow], word_size + 1, word);
			posVow++;
		}
		else {
			getMem(oth + posOth, word_size + 1);
			strcpy_s(oth[posOth], word_size + 1, word);
			posOth++;
		}

		word = strtok_s(NULL, " ,.-!?", &nexttoken);
	}

}

void delMem(char** str, const int size) {
	for (int i = 0; i < size; i++) {
		delete[] * (str + i);
		*(str + i) = nullptr;
	}
}

void getMem(char** str, const int size) {
	*str = new (nothrow) char[size];
	if (!str) {
		cout << "Ошибка выделения памяти!\n";
		exit(1);
	}
}

void printStr(char* str[], const int size) {
	for (int i = 0; i < size; i++) {
		cout << *(str + i) << ' ';
	}
	cout << endl;
}
