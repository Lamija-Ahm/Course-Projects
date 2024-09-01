#pragma once
#include "../zadatak1/DoubleLinkedList.hpp"
#include <iostream>

class Number {
public:
  Number();
  Number(int value);
  Number(Number&& other) noexcept;
  Number &operator=(const Number &);
  Number &operator=(Number &&);
  Number(Number& other);

  Number operator+(const Number &) const;
  Number operator-(const Number &) const;
  Number &operator+=(const Number &);
  Number &operator-=(const Number &);
  Number &operator=(const int &);
  Number &operator=(int &&);
  Number operator+(const int &) const;
  Number operator-(const int &) const;
  Number &operator+=(const int &);
  Number &operator-=(const int &);
  bool operator==(const Number &o) const;
  bool operator!=(const Number &) const;
  bool operator>(const Number &) const;
  bool operator<(const Number &) const;
  bool operator>=(const Number &) const;
  bool operator<=(const Number &) const;
  bool operator==(const int &) const;
  bool operator!=(const int &) const;
  bool operator>(const int &) const;
  bool operator<(const int &) const;
  bool operator>=(const int &) const;
  bool operator<=(const int &) const;
  //   Stepenovanje
  Number operator^(short) const;
  //   Primjer pozivanja operator bool():
  //     Number num;
  //       if(num)  Poziva se operator bool()
  //        cout << "Valid" << std::endl;;
  operator bool() const;
  Number &operator++();
  Number operator++(int);
  Number &operator--();
  Number operator--(int);

  friend std::ostream &operator<<(std::ostream &o, const Number &num){
        if (num.negative_) o << '-';
        for (auto it = num.digits_.begin(); it != num.digits_.end(); ++it) {
            o << *it;
        } 
        return o;
    }

  Number add(const Number& other, bool res_sign) const;
  Number subtract(const Number& other, bool res_sign=false) const;
  void absolute();

private:
  DoubleLinkedList<int> digits_{};
  bool negative_ = false;
};
