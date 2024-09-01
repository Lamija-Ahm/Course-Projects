#pragma once
#include "../zadatak1/MojVektor.hpp"

class Polinom : MojVektor<double> {
  public:

    void addCoefficient(const double& coeff) {
        this->push_back(coeff);}
    Polinom operator+(const Polinom& other) const;
    Polinom operator-(const Polinom& other) const;
    Polinom operator*(const Polinom& other) const;
    double operator()(double input) const;
    Polinom izvod() const;
    friend std::ostream& operator<<(std::ostream& os, const Polinom& p);
    friend std::istream& operator>>(std::istream& is, Polinom& p);

  private:
   // MojVektor<double> coef;
};
