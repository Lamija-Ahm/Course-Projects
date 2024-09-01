#include "f1_teams.hpp"

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>


bool compare(const Team& a, const Team& b) {
 return a.champs() < b.champs() ;
}

bool f1_teams::ucitaj(const std::string& file)
{
  std::ifstream input(file);

  if (!input)
  {
    std::cout << "Error: nije moguce otvoriti fajl." << std::endl;
    return false;
  }

  std::string temp;
  std::getline(input, temp);

  Team t;
  while (std::getline(input, temp))
  {
    std::stringstream ssin { temp };
    ssin >> t;
    push_back(t);
  }

  input.close();
  return true;
}
