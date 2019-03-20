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

const int BUFF_SIZE = 512;

using namespace std;

void getLine(char*, const int);
void printStr(char*[], const int);
void getMem(char**, const int, const int);
void sortStr(char*, char**, char**);

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	char buff[BUFF_SIZE];
	char* vowelStr[BUFF_SIZE];
	char* otherStr[BUFF_SIZE];

	getLine(buff, BUFF_SIZE);
	sortStr(buff, vowelStr, otherStr);

	system("pause");
	return 0;
}

void sortStr(char* line, char** vow, char** oth) {

	int pos_to_push_vow = 0;
	int pos_to_push_oth = 0;

	const char* check = "уеёыаоэяиюУЕЁЫАОЭЯИЮeyuioaEYUIOA";
	char* nexttoken = NULL;

	char* word = strtok_s(line, " ,.-!?", &nexttoken);

	while (word != NULL)
	{
		int count = 0;
		int word_size = strlen(word);

		for (int k = 0; k < word_size; k++) {
			if (strchr(check, word[k])) count++;
		}
		if (count == 1) {
			getMem(vow, word_size + 1, pos_to_push_vow);
			strcpy_s(vow[pos_to_push_vow], word_size + 1, word);
			pos_to_push_vow++;
		}
		else {
			getMem(oth, word_size + 1, pos_to_push_oth);
			strcpy_s(oth[pos_to_push_oth], word_size + 1, word);
			pos_to_push_oth++;
		}

		word = strtok_s(NULL, " ,.-!?", &nexttoken);
	}

	printStr(oth, pos_to_push_oth);
	printStr(vow, pos_to_push_vow);
}

void getMem(char** str, const int size, const int pos) {
	*(str + pos) = new char[size];
}

void printStr(char* str[], const int size) {
	for (int i = 0; i < size; i++) {
		cout << *(str + i) << ' ';
	}
	cout << endl;
}

void getLine(char* str, const int size) {
	cin.getline(str, BUFF_SIZE);
}