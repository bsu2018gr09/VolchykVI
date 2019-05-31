/*

	Это скорее не класс, а композиция классов, 
	которая реализует минимальный функционал взаимодействия
	с подобием базы данных.

	Сразу перечислю недостатки:
	1) Стек вызова функций не очищается, и поэтому
		в какой-то момент ваша память может закончиться.
		Про вызовы try/catch мы не знаем, так что вот.

	2) Нужно точное начальное редактирование файла 
		внешних данных. 
		Имя файла - memory.txt
		Путь к файлу: d://memory.txt
	
	3) Все поля элементов основного класса - числовые значения

*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

class ConstrMat {
	friend class SubControls;
	friend class SupControls;
public:
	int _cypher;
	int _stock;
	double _distance;
	int _amount;
	double _price;
public:
	ConstrMat() : 
		_cypher{ 0 }, 
		_stock{ 0 }, 
		_distance{ 0 }, 
		_amount{ 0 },
		_price{ 0 }
	{};
	~ConstrMat() {};
	ConstrMat(const ConstrMat& i) : 
		_cypher{ i._cypher }, 
		_stock{ i._stock }, 
		_distance{ i._distance }, 
		_amount{ i._amount }, 
		_price{ i._price } 
	{};
	const ConstrMat& operator = (const ConstrMat& i) {
		if (this != &i) {
			this->_cypher = i._cypher;
			this->_stock = i._stock;
			this->_distance = i._distance;
			this->_amount = i._amount;
			this->_price = i._price;
		}
		return *this;
	}
};

class SubControls {
	friend class SupControls;
public:
	int Amount;
public:
	void setCypher(ConstrMat& i, int n) {
		i._cypher = n;
	}
	void setStock(ConstrMat& i, int n) {
		i._stock = n;
	}
	void setDistance(ConstrMat& i, double n) {
		i._distance = n;
	}
	void setAmount(ConstrMat& i, int n) {
		i._amount = n;
	}
	void setPrice(ConstrMat& i, double n) {
		i._price = n;
	}

	void writeMat(const ConstrMat& i, ofstream& out) {
		out << i._cypher << ' ' << i._stock << ' ' << i._distance << ' ' << i._amount << ' ' << i._price << endl;
	}
	void readMat(ConstrMat& i, ifstream& inp) {
		inp >> i._cypher; 
		inp >> i._stock;
		inp >> i._distance;
		inp >> i._amount;
		inp >> i._price;
	}

	void writeArrMat(const ConstrMat* ptr, const int size) {
		ofstream out("d://memory.txt");
		Amount = size;
		out << Amount << endl;
		for (int i = 0; i < size; i++)
			writeMat(ptr[i], out);
		out.close();
	}
	void readArrMat(ConstrMat*& ptr) {
		ifstream inp("d://memory.txt");
		inp >> Amount;
		ptr = new ConstrMat[Amount];
		for (int i = 0; i < Amount; i++) {
			readMat(ptr[i], inp);
		}
		inp.close();
	}
	int subAmount(int digit) {
		int counter = 0;
		while ((digit /= 10) > 0) counter++;
		return counter;
	}
};

class SupControls {
	friend class SubControls;
	friend class Menu;
public:
	void printMat(ConstrMat& i, const int index) {
		const int p = 17;
		cout 
			<< left
			<< setw(2)
			<< index 
			<< right
			<< setw(p) 
			<< i._cypher 
			<< setw(p) 
			<< i._stock 
			<< setw(p) 
			<< i._distance 
			<< setw(p) 
			<< i._amount 
			<< setw(p) 
			<< i._price 
			<< endl;
	}
	void printArrMat(ConstrMat* ptr, const int size) {
		const int p = 17;
		cout
			<< right
			<< setw(19)
			<< "Шифр"
			<< setw(p)
			<< "Номер"
			<< setw(p)
			<< "Расстояние"
			<< setw(p)
			<< "Количество"
			<< setw(p)
			<< "Цена"
			<< endl;
		for (int i = 0; i < size; i++) printMat(ptr[i], i + 1);
		cout 
			<< endl;
	}
	void createMat() {
		ConstrMat* ptr, * tmp;
		SubControls subControl;
		subControl.readArrMat(ptr);
		subControl.Amount++;
		tmp = new (nothrow) ConstrMat[subControl.Amount];
		memcpy(tmp, ptr, 32*(subControl.Amount-1));
		cout << "Введите шифр материала: ";
		cin >> tmp[subControl.Amount - 1]._cypher;
		cout << "\nВведите номер склада с материалом: ";
		cin >> tmp[subControl.Amount - 1]._stock;
		cout << "\nВведите расстояние до склада: ";
		cin >> tmp[subControl.Amount - 1]._distance;
		cout << "\nВведите количество материала: ";
		cin >> tmp[subControl.Amount - 1]._amount;
		cout << "\nВведите цену материала: ";
		cin >> tmp[subControl.Amount - 1]._price;
		subControl.writeArrMat(tmp, subControl.Amount);
	}
	void deleteMat() {
		ConstrMat* ptr;
		SubControls subControl;
		subControl.readArrMat(ptr);
		int pos;
		cout << "Введите номер удаляемого элемента: ";
		cin >> pos;
		for (int i = --pos; i < subControl.Amount - 1; i++) ptr[i] = ptr[i + 1];
		!subControl.Amount ? subControl.Amount : --subControl.Amount;
		subControl.writeArrMat(ptr, subControl.Amount);
	}
	void editMat() {
		ConstrMat* ptr;
		SubControls subControl;
		subControl.readArrMat(ptr);
		if (!subControl.Amount) return;
		int pos;
		cout << "Введите номер редактируемого элемента: ";
		cin >> pos;
		while (true) {
			int choice; 
			const int p = 17;
			cout
				<< right
				<< setw(19)
				<< "Шифр"
				<< setw(p)
				<< "Номер"
				<< setw(p)
				<< "Расстояние"
				<< setw(p)
				<< "Количество"
				<< setw(p)
				<< "Цена"
				<< endl;
			printMat(ptr[pos - 1], pos);
			cout << "Выберите замену:\n";
			cout << "1) Шифр\n2) Номер\n3) Расстояние\n4) Количество\n5) Цена\n6) Сохранить\n ";
			cin >> choice;
			switch (choice) {
			case 1:
				cout << "Введите значение: ";
				cin >> ptr[pos - 1]._cypher;
				break;
			case 2:
				cout << "Введите значение: ";
				cin >> ptr[pos - 1]._stock;
				break;
			case 3:
				cout << "Введите значение: ";
				cin >> ptr[pos - 1]._distance;
				break;
			case 4:
				cout << "Введите значение: ";
				cin >> ptr[pos - 1]._amount;
				break;
			case 5:
				cout << "Введите значение: ";
				cin >> ptr[pos - 1]._price;
				break;
			case 6:
				subControl.writeArrMat(ptr, subControl.Amount);
				return;
			}
		}
	}
	void filterCypher(ConstrMat*& ptr, const int size) {
		int i{ 1 }, j{ 2 };
		while (i < size) {
			if (ptr[i - 1]._cypher <= ptr[i]._cypher) {
				i = j;
				j++;
			}
			else {
				swap(ptr[i - 1], ptr[i]);
				i--;
				if (!i) {
					i = j;
					j++;
				}
			}
		}
	}
	void filterStock(ConstrMat*& ptr, const int size) {
		int i{ 1 }, j{ 2 };
		while (i < size) {
			if (ptr[i - 1]._stock <= ptr[i]._stock) {
				i = j;
				j++;
			}
			else {
				swap(ptr[i - 1], ptr[i]);
				i--;
				if (!i) {
					i = j;
					j++;
				}
			}
		}
	}
	void filterDist(ConstrMat*& ptr, const int size) {
		int i{ 1 }, j{ 2 };
		while (i < size) {
			if (ptr[i - 1]._distance <= ptr[i]._distance) {
				i = j;
				j++;
			}
			else {
				swap(ptr[i - 1], ptr[i]);
				i--;
				if (!i) {
					i = j;
					j++;
				}
			}
		}
	}
	void filterAmount(ConstrMat*& ptr, const int size) {
		int i{ 1 }, j{ 2 };
		while (i < size) {
			if (ptr[i - 1]._amount <= ptr[i]._amount) {
				i = j;
				j++;
			}
			else {
				swap(ptr[i - 1], ptr[i]);
				i--;
				if (!i) {
					i = j;
					j++;
				}
			}
		}
	}
	void filterPrice(ConstrMat*& ptr, const int size) {
		int i{ 1 }, j{ 2 };
		while (i < size) {
			if (ptr[i - 1]._price <= ptr[i]._price) {
				i = j;
				j++;
			}
			else {
				swap(ptr[i - 1], ptr[i]);
				i--;
				if (!i) {
					i = j;
					j++;
				}
			}
		}
	}
	void showMats() {
		ConstrMat* ptr;
		SubControls subControl;
		subControl.readArrMat(ptr);
		int cypher, *tmpPtr, counter{ 0 };
		cout << "Введите шифр материала: ";
		cin >> cypher;
		for (int i{ 0 }; i < subControl.Amount;) 
			cypher == ptr[i]._cypher 
			? 
			counter++, 
			i++ 
			: 
			i++;
		tmpPtr = new (nothrow) int[counter * 3];
		for (int i{ 0 }, j{ 0 }; i < subControl.Amount;) {
			cypher == ptr[i]._cypher ?
				tmpPtr[j] = ptr[i]._amount,
				tmpPtr[j + 1] = ptr[i]._price,
				tmpPtr[j + 2] = ptr[i]._stock,
				i++,
				j++
				: 
				i++;
		}
		cout 
			<< "\nИнформация по материалу:\n" 
			<< setw(20) 
			<< "Количество на складе" 
			<< setw(20) 
			<< "Номер склада" 
			<< setw(20) 
			<< " Общая стоимость" 
			<< endl;
		for (int i{ 0 }; i < counter; i++)
			cout 
				<< right 
				<< setw(20) 
				<< tmpPtr[i] 
				<< setw(20) 
				<< tmpPtr[i + 2] 
				<< setw(20) 
				<< tmpPtr[i + 1] * tmpPtr[i] 
				<< endl;
	}
	void findStock() {
		int usrCypher, usrAmount, counter{ 0 }, *tmpPtr;
		ConstrMat* ptr;
		SubControls subControl;
		SupControls supControl;
		cout << "Введите шифр материала: ";
		cin >> usrCypher;
		cout << "Введите требуемое количество: ";
		cin >> usrAmount;
		subControl.readArrMat(ptr);
		supControl.filterDist(ptr, subControl.Amount);
		for (int i{ 0 }; i < subControl.Amount;) 
			ptr[i]._cypher == usrCypher 
			? 
			counter++, 
			i++ 
			: 
			i++;
		tmpPtr = new (nothrow) int[counter*3];
		for (int i{ 0 }, j{ 0 }; i < subControl.Amount;) {
			ptr[i]._cypher == usrCypher
				?
				tmpPtr[j] = ptr[i]._amount,
				tmpPtr[j + 1] = ptr[i]._distance,
				tmpPtr[j + 2] = ptr[i]._stock,
				i++,
				j += 3
				: 
				i++;
		}
		for (int i = 0, flag = 0; i < counter; i++) {
			if (usrAmount <= tmpPtr[i]) {
				cout << "\nНомер подходящего склада: " << tmpPtr[i + 2] << endl;
				cout << "Расстояние до склада: " << tmpPtr[i + 1] << endl;
				return;
			}
		}
	}
};

class Menu {
	friend class SupControls;
public: 
	void mainMenu(){
		int choice;
		cout << "Главное меню\n1) Вывести список доступных материалов\n2) Найти материал\n3) Найти склад с материалом\n4) Выйти\n: ";
		cin >> choice;
		switch (choice) {
		case 1:
			showMats();
			mainMenu();
			break;
		case 2: {
			SupControls supControl;
			supControl.showMats();
			mainMenu();
			break;
		}
		case 3: {
			SupControls supControl;
			supControl.findStock();
			mainMenu();
			break;
		}
		case 4:
			exit(0);
		}
				
	}
	void showMats() {
		SubControls subControl;
		SupControls supControl;
		ConstrMat* ptr;
		subControl.readArrMat(ptr);
		int choice;
		supControl.printArrMat(ptr, subControl.Amount);
		while (true) {
			cout << "1) Добавить материал\n2) Удалить материал\n3) Редактировать материал\n4) Отфильтровать список материалов\n5) Главное меню\n: ";
			cin >> choice;
			switch (choice) {
			case 1:
				supControl.createMat();
				break;
			case 2:
				supControl.deleteMat();
				break;
			case 3:
				supControl.editMat();
				break;
			case 4: 
				filter(ptr, subControl.Amount);
				break;
			case 5:
				break;
			}
			return;
		}
	}
	void filter(ConstrMat*& ptr, const int size) {
		int choice;
		SupControls supControl;
		cout << "Выберите параметр фильтрации:\n1) По шифру\n2) По номеру склада\n3) По расстоянию\n4) По количеству\n5) По цене\n: ";
		cin >> choice;
		switch (choice) {
		case 1:
			supControl.filterCypher(ptr, size);
			break;
		case 2:
			supControl.filterStock(ptr, size);
			break;
		case 3:
			supControl.filterDist(ptr, size);
			break;
		case 4:
			supControl.filterAmount(ptr, size);
			break;
		case 5:
			supControl.filterPrice(ptr, size);
			break;
		}
		supControl.printArrMat(ptr, size);
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	Menu menu;
	menu.mainMenu();
	return 0;
}