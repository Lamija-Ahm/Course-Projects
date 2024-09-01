#include "Polinom.cpp"
#include<stdexcept>
#include <iostream>

int main() {
	Polinom p1, p2;
	std::cout << "Unesi polinom 1: ";
	double unos;
	while (std::cin >> unos)
		p1.addCoefficient(unos); 
	std::cin.clear();
	std::cin.ignore();
	std::cout << "Unesi polinom 2: ";
	while (std::cin >> unos)
		p2.addCoefficient(unos);
	std::cout << "P1(x) = " << p1 << std::endl;
  std::cout << "P1'(x) = " << p1.izvod() << std::endl;
	std::cout << "P2(x) = " << p2 << std::endl;
	std::cout << "P2'(x) = " << p2.izvod() << std::endl;
	std::cout << "P1(x) + P2(x) = " << (p1+p2) << std::endl;
	std::cout << "P1(x) - P2(x) = " << (p1-p2) << std::endl;
	std::cout << "P1(x) * P2(x) = " << (p1*p2) << std::endl << std::endl;

  std::cout << "\n Vrijednosti polinoma P1(x) u rasponu [-10, 10]:" << std::endl;
	for (auto i = -10; i <= 10; ++i) {
		std::cout << "P(" << i << ") = " << p1(i) << '\n' ;
	}
  auto p=p1.izvod();
  std::cout << "\n Vrijednosti polinoma P1'(x) u rasponu [-10, 10]:" << std::endl;
	for (auto i = -10; i <= 10; ++i) {
		std::cout << "P(" << i << ") = " << p(i) << '\n' ;
	}
	
	
	return 0;
}
