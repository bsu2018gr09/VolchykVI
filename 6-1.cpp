/*

	Класс арифметических дробей

	(Пока что без автоматическая сокращения на общий множитель)

*/

#include <iostream>

using namespace std;

class Fraction {
private:
	int _numer;
	int _denom;
public:
	Fraction() { 
		_numer = 0;
		_denom = 1;
		//cout << "constructor works!\n"; 
	}
	
	~Fraction() { 
		//cout << "destructor works!\n"; 
	}
	
	Fraction(int _numer, int _denom = 1) {
		this->_numer = _numer;
		this->_denom = _denom;
	}
	
	Fraction(Fraction& fr) {
		//cout << "copy constructor works!\n";
		this->_numer = fr._numer;
		this->_denom = fr._denom;
	}

	const Fraction& operator=(const Fraction& fr) {
		if (this != &fr) {
			this->_numer = fr._numer;
			this->_denom = fr._denom;
		}
		return *this;
	}

	Fraction& operator ++ () {
		this->_numer += this->_denom;
		return *this;
	}

	Fraction operator ++ (int) {
		Fraction temp = *this;
		++*this;
		return temp;
	}

	Fraction& operator -- () {
		this->_numer -= this->_denom;
		return *this;
	}

	Fraction operator -- (int) {
		Fraction temp = *this;
		--*this;
		return temp;
	}

	Fraction operator + (const Fraction& fr) {
		Fraction temp;
		if (this->_denom != fr._denom) {
			temp._numer = this->_numer*fr._denom + fr._numer*this->_denom;
			temp._denom = this->_denom;
		}
		else {
			temp._numer = this->_numer + fr._numer;
			temp._denom = this->_denom;
		}
		return temp;
	}

	Fraction operator + (const int n) {
		Fraction temp;
		temp._numer = this->_numer + n * this->_denom;
		temp._denom = this->_denom;
		return temp;
	}

	Fraction operator - (const Fraction& fr) {
		Fraction temp;
		if (this->_denom != fr._denom) { 
			temp._numer = this->_numer*fr._denom - fr._numer*this->_denom;
			temp._denom = this->_denom;
		}
		else {
			temp._numer = this->_numer - fr._numer;
			temp._denom = this->_denom;
		}
		return temp;
	}

	Fraction operator - (const int n) {
		Fraction temp;
		temp._numer = this->_numer - n * this->_denom;
		temp._denom = this->_denom;
		return temp;
	}

	Fraction operator * (const Fraction& fr) {
		Fraction temp(this->_numer * fr._numer, this->_denom * fr._denom);
		return temp;
	}

	Fraction operator * (const int n) {
		Fraction temp(this->_numer * n, this->_denom);
		return temp;
	}

	Fraction operator / (const Fraction& fr) {
		Fraction temp(this->_numer * fr._denom, this->_denom * fr._numer);
		return temp;
	}

	Fraction operator / (const int n) {
		Fraction temp(this->_numer, this->_denom * n);
		return temp;
	}

	Fraction& operator - () {
		this->_numer = -this->_numer;
		return *this;
	}

	Fraction& operator + () {
		return *this;
	}

	Fraction& operator += (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			this->_numer = this->_numer*fr._denom + fr._numer*this->_denom;
		}
		else
			this->_numer += fr._numer;
		return *this;
	}

	Fraction& operator -= (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			this->_numer = this->_numer*fr._denom - fr._numer*this->_denom;
		}
		else
			this->_numer -= fr._numer;
		return *this;
	}

	Fraction& operator *= (const Fraction& fr) {
		this->_numer *= fr._numer;
		this->_denom *= fr._denom;
		return *this;
	}

	Fraction& operator /= (const Fraction& fr) {
		this->_numer *= fr._denom;
		this->_denom *= fr._numer;
		return *this;
	}

	bool operator > (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			return (this->_numer*fr._denom > fr._numer*this->_denom);
		}
		return (this->_numer > fr._numer);
	}

	bool operator < (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			return (this->_numer*fr._denom < fr._numer*this->_denom);
		}
		return (this->_numer < fr._numer);
	}

	bool operator == (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			return (this->_numer*fr._denom == fr._numer*this->_denom);
		}
		return (this->_numer == fr._numer);
	}

	bool operator >= (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			return (this->_numer*fr._denom >= fr._numer*this->_denom);
		}
		return (this->_numer >= fr._numer);
	}

	bool operator <= (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			return (this->_numer*fr._denom <= fr._numer*this->_denom);
		}
		return (this->_numer <= fr._numer);
	}

	friend ostream& operator << (ostream & stream, const Fraction& fr)
	{
		stream << fr._numer << '/' << fr._denom;
		return stream;
	}

	friend istream& operator >> (istream& stream, Fraction& fr) {
		stream >> fr._numer;
		stream >> fr._denom;
		return stream;
	}
};

int main() {

	Fraction num1, num2(2,5), num3(1,5);
	Fraction *ptr1, *ptr2;
	Fraction arr[5];
	ptr2 = new (nothrow) Fraction[10];

	cout << "Objects\n\n";
	cout << num2 + num3 << endl;
	cout << num2 - num3 << endl;
	cout << num2 * num3 << endl;
	cout << num2 / num3 << endl;
	cout << (num2 += num3) << endl;
	cout << (num2 -= num3) << endl;
	cout << (num2 *= num3) << endl;
	cout << (num2 /= num3) << endl;
	cout << (num2 > num3) << endl;
	cout << (num2 < num3) << endl;
	cout << (num2 == num3) << endl;
	cout << (num2 >= num3) << endl;
	cout << (num2 <= num3) << endl;
	cout << num3 + 10 << endl;
	cout << num3 - 10 << endl;
	cout << num3 * 10 << endl; 
	cout << num3 / 10 << endl;
	cout << -num3 << endl;

	ptr1 = &-num3;

	cout << "\nPointer\n\n";
	cout << *ptr1 << endl;
	cout << *ptr1 + 10 << endl;
	cout << *ptr1 - 10 << endl;
	cout << *ptr1 * 10 << endl;
	cout << *ptr1 / 10 << endl;
	cout << *ptr1 + *ptr1 << endl;
	cout << *ptr1 + num3 << endl;
	cout << ++*ptr1 << endl;

	arr[0] = Fraction(10, 14);


	cout << "\nArray's element\n\n";
	cout << arr[0] << endl;
	cout << arr[0] * 10 << endl;
	cout << arr[0] + arr[0] << endl;

	arr[0] = *ptr1;
	cout << arr[0] << endl;

	arr[0] = num3;
	cout << arr[0] << endl;

	ptr2[5] = arr[0];

	cout << arr[0] + *ptr1 + num3 +ptr2[5] << endl;


	system("pause");
	return 0;
}