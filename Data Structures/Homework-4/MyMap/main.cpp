#include "map.hpp"
#include <string>

int main()
{
  Map<int,std::string> m1;
  m1.insert(5,"pet");
  m1.insert(1,"jedan");
  m1.insert(9,"devet");
  m1.insert(3,"tri");
//  m1.print();
  //Map<int,std::string> m2{m1};
  Map<int,std::string> m2;
  m2 = m1;
  std::cout << m2.empty() << std::endl;
  std::cout << m2.at(2) << std::endl;
  std::cout << m2.at(5) << std::endl;
  std::cout<< m2[5] << std::endl;
  if(m2.find(9))
  std::cout << *m2.find(3) << std::endl;
  m1.erase(1);
  //m1.print();
  m2.clear();
//  m2.print();
  return 0;
}
