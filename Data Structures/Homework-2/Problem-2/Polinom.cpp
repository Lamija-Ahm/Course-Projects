#include "Polinom.hpp"
#include<cmath>


Polinom Polinom::operator+(const Polinom& other) const{
  auto max = std::max(this->size(), other.size());
  Polinom res;
  res.resize(max, 0.0);
  for(auto i=0; i<this->size(); ++i){
    res[i] += (*this)[i];
  }
  for(auto i=0; i<other.size(); ++i){
    res[i] += other[i];
  }
return res;
}

Polinom Polinom::operator-(const Polinom& other) const{
  auto max = std::max(this->size(), other.size());
  Polinom res;
  res.resize(max, 0.0);
  for(auto i=0; i<this->size(); ++i){
    res[i] += (*this)[i];
  }
  for(auto i=0; i<other.size(); ++i){
    res[i] -= other[i];
  }
return res;
}

Polinom Polinom::operator*(const Polinom& other) const {
  
 auto size = this->size() + other.size();

  Polinom res;
  res.resize(size,0.0);

for (size_t i = 0; i < this->size(); ++i) {
  for (size_t j = 0; j < other.size(); ++j) {
    res[i+j] += (*this)[i] * other[j];
 }
 }

 return res;
 }

std::ostream& operator<<(std::ostream& os, const Polinom& pol) {
    for (auto i = 0; i < pol.size(); ++i) {
        if (i == 0) { 
          if(pol[i] != 0)
            os << pol[i];
        } else{
        if(pol[i]<0){ 
         os << " " << pol[i] << "*x^" << i;
        }
          if(pol[i]>0) 
        {
            os << " + " << pol[i] << "*x^" << i;
        }
    }}
    return os;
}

std::istream& operator>>(std::istream& is, Polinom& pol) {

    pol.clear();
    double input;
    while (is >> input) {
        pol.push_back(input);
    }
    return is;
}

double Polinom::operator()(double input) const{
  double res=0;

for (size_t i = 0; i < this->size(); ++i) {
  res+=(*this)[i]*pow(input, i);
}
 return res;
}


 Polinom Polinom::izvod() const {
        Polinom res;
        if (this->size() <= 1) {
            return res;
        }

        for (size_t i = 1; i < this->size(); ++i) {
            res.push_back((*this)[i] * i);
        }

        return res;
    }
