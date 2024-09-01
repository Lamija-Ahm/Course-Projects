#include "teams.hpp"
#include<iostream>
#include<string>

std::ostream& operator<<(std::ostream& out, const Team& Team)
{
  return out << Team.name() << "," << Team.country() << ","
             << Team.year() << "," << Team.champs() << ","
             << Team.budget();
}

std::istream& operator>>(std::istream& in, Team& t)
{
  std::getline(in, t.name_, ',');
  std::getline(in, t.country_, ',');

  std::string temp;
  std::getline(in, temp, ',');
  t.year_ = std::stoi(temp);

  std::getline(in, temp, ',');
  t.champs_ = std::stoi(temp);

  std::getline(in, temp);
  t.budget_ = std::stoi(temp);

  return in;
}
