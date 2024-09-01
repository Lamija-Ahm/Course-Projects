#pragma once
#include <ostream>
#include<iostream>
#include<algorithm>
#include<numeric>
#include<sstream>
#include<string>
#include<cmath>

/*! \class Rational
 *
 *  Klasa Rational simulira rad sa racionalnim brojevima.
 *  Stanje ove klase cine dva cijela broja: brojnik i nazivnik.
 *  Sve operacije moraju bit optimialne, sto znaci da ako je moguce i brojnik i
 * nazivnik treba skratiti na najmanju mogucu vrijednost, na primjer: 10/12 je
 * neophodno prikazati kao 5/6 nakon kracenja sa 2.
 * Ne dozvoliti da nazivnik bude 0!
 */

class Rational {
  public:
  // Numerator 0, denominator 1
  Rational(): numerator_(0), denominator_(0) {};
  // denominator should not be 0!
  Rational(int numerator, int denominator);
  // Split const char* by / delimiter
  Rational(const char* rational);
  Rational(const std::string&);
  // copy constructor
  Rational(const Rational& rational):
    numerator_(rational.numerator_), 
    denominator_(rational.denominator_) {};
  // Move constructor
  Rational(Rational&& rational):
    numerator_(rational.numerator_),
    denominator_(rational.denominator_){
    rational.numerator_ = 0;
    rational.denominator_ = 1;
    };
  // Copy op=
  Rational& operator=(const Rational& rational) {
		numerator_ = rational.numerator_;
		denominator_ = rational.denominator_;
		return *this;
	}
  // Move op=
  Rational& operator=(Rational&& rational) {
		numerator_ = rational.numerator_;
		denominator_ = rational.denominator_;
		rational.numerator_ = 0;
		rational.denominator_ = 1;
		return *this;
	}
  // Return optimal rational number
  // 2/3 + 4/3, operator should return 3/1.
  // std::cout should print it as 3, not 3/1!
  Rational operator+(const Rational& rational) const;
  Rational operator+(int numerator) const;
  Rational operator-(const Rational& rational) const;
  Rational operator-(int numerator) const;
  Rational operator*(const Rational& rational) const;
  Rational operator*(int numerator) const;
  Rational operator/(const Rational& rational) const;
  Rational operator/(int numerator) const;
  Rational operator^(int) const;
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  bool operator==(const Rational& rational) const;
  bool operator==(const char* rational) const;
  bool operator!=(const Rational& rational) const;
  bool operator!=(const char* rational) const;
  // Get numerator
  const int numerator() const{
    return numerator_;
  }
  // Get denominator
  const int denominator() const{
    return denominator_;
  }

  ~Rational() {}

  private:
  int numerator_;   // brojnik
  int denominator_; // nazivnik
};

// Example:
// 5/1 should be printed as 5!
// 10/5 should be printed as 2
// 12/8 should be printed as 3/2
std::ostream& operator<<(std::ostream& os, const Rational& rational);

// divisior gcd will return the greatest number that we should use to divide
// numerator and denominator(Normalization)
int gcd(const int numerator, const int denominator);
