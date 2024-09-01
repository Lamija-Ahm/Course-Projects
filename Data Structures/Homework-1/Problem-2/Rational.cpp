#include "Rational.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include<stdexcept>
#include<cmath>

Rational::Rational(int numerator, int denominator) {
	if (denominator == 0)
		throw std::invalid_argument{"Nazivnik ne moze biti nula"};
	numerator_ = numerator;
	denominator_ = denominator;
}

Rational::Rational(const char* rational) {
	*this = Rational(std::string(rational));
}

Rational::Rational(const std::string& str) {
	int x = str.find('/');
	if (x == std::string::npos)
		throw std::invalid_argument("Nedostaje /");
  
  std::string str1 = str.substr(0, x);
  std::string str2 = str.substr(x+1, str.length()-1);

  for(char c : str1){
  if(!std::isdigit(c))
    throw std::invalid_argument("POgresan unos, samo brojevi!");
  } 

  
  for(char c : str2){
  if(!std::isdigit(c))
 throw std::invalid_argument("POgresan unos, samo brojevi!");
  }

  if (std::stoi(str2) == 0)
        throw std::invalid_argument("Nazivnik ne smije biti 0");

   numerator_ = std::stoi(str1);
   denominator_ = std::stoi(str2);

}

int gcd(int numerator, int denominator) {
	if (numerator < 0) numerator *= -1;
	if (denominator < 0) denominator *= -1;
	const int num = numerator;
	const int denom = denominator;
	int shift;
	for (shift = 0; ((numerator | denominator) & 1) == 0; ++shift) {
		numerator >>= 1;
		denominator >>= 1;
	}
	while ((numerator & 1) == 0) {
		numerator >>= 1;
	}
	while (denominator != 0) {
		while ((denominator & 1) == 0) {
			denominator >>= 1;
		}
		if (numerator > denominator) {
			std::swap(numerator, denominator);
		}
		denominator -= numerator;
	}
	return numerator << shift;
}


Rational Rational::operator+(const Rational& rational) const {
    if (numerator() == 0) return rational;
    if (rational.numerator() == 0) return *this;

    int num = numerator() * rational.denominator() + rational.numerator() * denominator();
    int den = denominator() * rational.denominator();

    int nzd = gcd(num, den);
    num /= nzd;
    den /= nzd;

    return Rational(num, den);
}

  Rational Rational::operator+(int numerator) const {
	return (*this + Rational(numerator, 1));
  }


Rational Rational::operator-(const Rational& rational) const {
    if (numerator() == 0)
        return rational;
    if (rational.numerator() == 0)
        return *this;

    int num = numerator() * rational.denominator() - rational.numerator() * denominator();
    int den = denominator() * rational.denominator();

    int nzd = gcd(num, den);
    num /= nzd;
    den /= nzd;

    return Rational(num, den);
}

  Rational Rational::operator-(int numerator) const {
	return *this - Rational(numerator, 1);
}




Rational Rational::operator*(const Rational& rational) const {

    int num = numerator() * rational.numerator();
    int den = denominator() * rational.denominator();

    int nzd = gcd(num, den);
    num /= nzd;
    den /= nzd;

    return Rational(num, den);
}

Rational Rational::operator*(int numerator) const {
    int num = this->numerator() * numerator;
    
    int nzd = gcd(num, denominator());
    num /= nzd;
    int den = denominator() / nzd;

    return Rational(num, den);
}

Rational Rational::operator/(const Rational& rational) const {
    int num = numerator() * rational.denominator();
    int den = denominator() * rational.numerator();

    int nzd = gcd(num, den);
    num /= nzd;
    den /= nzd;

    return Rational(num, den);
}

Rational Rational::operator/(int numerator) const {
    int den = denominator() * numerator;

    int nzd = gcd(this->numerator(), den);
    int num = this->numerator() / nzd;
    den /= nzd;

    return Rational(num, den);
}

Rational Rational::operator^(int exponent) const {
	return Rational( pow(numerator(), exponent), pow(denominator(), exponent));
}

Rational& Rational::operator++() {
    *this = *this + 1;
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp(*this);
    *this = *this + 1;
    return temp;
}

Rational& Rational::operator--() {
    *this = *this - 1;
    return *this;
}

Rational Rational::operator--(int) {
    Rational temp(*this);
    *this = *this - 1;
    return temp;
}

bool Rational::operator==(const Rational& rational) const {
    int proizvod1 = numerator() * rational.denominator();
    int proizvod2 = rational.numerator() * denominator();
      return proizvod1 == proizvod2;
}

bool Rational::operator==(const char* rational) const {
	Rational rat(rational);
	return *this == rat;
}

bool Rational::operator!=(const Rational& rational) const {
    return !(*this == rational);
}

bool Rational::operator!=(const char* rational) const {
	Rational rat(rational);
	return *this != rat;
}

std::ostream& operator<<(std::ostream& os, const Rational& rational) {
    int num = rational.numerator();
    int den = rational.denominator();
    int nzd = gcd(num, den);
    num /= nzd;
    den /= nzd;

    if (num == 0) {
        os << 0;
    } else {
        os << num;
        if (den != 1)
            os << '/' << den;
    }
