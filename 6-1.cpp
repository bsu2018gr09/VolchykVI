/*

	Класс арифметических дробей

*/

#include <iostream>

using namespace std;

class Fraction {
private:
	int _numer;
	int _denom;
public:
	Fraction() : _numer{ 0 }, _denom{ 1 } {
		//cout << "constructor works!\n"; 
	}

	~Fraction() {
		//cout << "destructor works!\n"; 
	}

	Fraction(int numer, int denom = 1) : _numer{ numer / gcd(numer, denom) }, _denom{ denom / gcd(numer, denom) } {
		if (!denom) { _denom = 1; cout << "denominator replaced with '1', because it was zero\n"; }
	}

	Fraction(const Fraction& fr) : _numer{ fr._numer / gcd(fr._numer, fr._denom) }, _denom{ fr._denom / gcd(fr._numer, fr._denom) } {
		//cout << "copy constructor works!\n";
	}

	int gcd(int a, int b) {
		a = abs(a);
		b = abs(b);
		while (a != b) {
			if (a > b) { swap(a, b); }
			b = b - a;
		}
		return a;
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
		if (this->_denom != fr._denom) {
			int _gcd = gcd(this->_numer*fr._denom + fr._numer*this->_denom, this->_denom);
			return Fraction((this->_numer*fr._denom + fr._numer*this->_denom) / _gcd, this->_denom / _gcd);
		}
		else {
			int _gcd = gcd(this->_numer + fr._numer, this->_denom);
			return Fraction((this->_numer + fr._numer) / _gcd, this->_denom / _gcd);
		}
	}

	Fraction operator + (const int n) {
		int _gcd = gcd(this->_numer + n * this->_denom, this->_denom);
		return Fraction((this->_numer + n * this->_denom) / _gcd, this->_denom / _gcd);
	}

	Fraction operator - (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			int _gcd = gcd(this->_numer*fr._denom - fr._numer*this->_denom, this->_denom);
			return Fraction((this->_numer*fr._denom - fr._numer*this->_denom) / _gcd, this->_denom / _gcd);
		}
		else {
			int _gcd = gcd(this->_numer - fr._numer, this->_denom);
			return Fraction((this->_numer - fr._numer) / _gcd, this->_denom / _gcd);
		}
	}

	Fraction operator - (const int n) {
		int _gcd = gcd(this->_numer - n * this->_denom, this->_denom);
		return Fraction((this->_numer - n * this->_denom) / _gcd, this->_denom / _gcd);
	}

	Fraction operator * (const Fraction& fr) {
		int _gcd = gcd(this->_numer * fr._numer, this->_denom * fr._denom);
		return Fraction(this->_numer * fr._numer / _gcd, this->_denom * fr._denom / _gcd);
	}

	Fraction operator * (const int n) {
		int _gcd = gcd(this->_numer*n, this->_denom);
		return Fraction(this->_numer * n / _gcd, this->_denom / _gcd);
	}

	Fraction operator / (const Fraction& fr) {
		return Fraction(this->_numer * fr._denom, this->_denom * fr._numer);
	}

	Fraction operator / (const int n) {
		int _gcd = gcd(this->_numer, this->_denom * n);
		return Fraction(this->_numer / _gcd, this->_denom * n / _gcd);
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
		this->_numer /= gcd(this->_numer, this->_denom);
		this->_denom /= gcd(this->_numer, this->_denom);
		return *this;
	}

	Fraction& operator -= (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			this->_numer = this->_numer*fr._denom - fr._numer*this->_denom;
		}
		else
			this->_numer -= fr._numer;
		this->_numer /= gcd(this->_numer, this->_denom);
		this->_denom /= gcd(this->_numer, this->_denom);
		return *this;
	}

	Fraction& operator *= (const Fraction& fr) {
		int _gcd = gcd(this->_numer * fr._numer, this->_denom * fr._denom);
		this->_numer *= fr._numer / _gcd;
		this->_denom *= fr._denom / _gcd;
		return *this;
	}

	Fraction& operator /= (const Fraction& fr) {
		int _gcd = gcd(this->_numer * fr._denom, this->_numer * fr._denom);
		this->_numer *= fr._denom / _gcd;
		this->_denom *= fr._numer / _gcd;
		return *this;
	}

	bool operator > (const Fraction& fr) {
		if (this->_denom != fr._denom) {
			return (this->_numer*fr._denom > fr._numer*this->_denom);
		}
		return (this->_numer > fr._numer);
	}

	bool operator < (const Fraction& fr) {
		return !(*this > fr);
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

	friend istream& operator >> (istream& stream, Fraction& fr) { /*    Думаю добавить поддержку ввода сплошной строки    */
		stream >> fr._numer;
		stream >> fr._denom;
		return stream;
	}
};

int main() {

	Fraction num1, num2(2, 4), num3(6, 4);
	Fraction *ptr1, *ptr2;
	Fraction arr[5];
	ptr2 = new (nothrow) Fraction[10];

	cout << "Object\n\n";
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

	cout << arr[0] + *ptr1 + num3 + ptr2[5] << endl;


	system("pause");
	return 0;
}
