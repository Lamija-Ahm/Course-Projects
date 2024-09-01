#pragma once

#include<iostream>
#include<string>

class Team
{
  public:


    friend std::istream& operator>>(std::istream&, const Team&);

   friend std::istream& operator>>(std::istream& in, Team& t);
    
    const std::string& name() const { return name_; }
    const std::string& country() const { return country_; }
    int year() const { return year_; }
    int champs() const { return champs_; }
    int budget() const { return budget_; }

    void name(const std::string& name){ name_ = name; }
    void country(const std::string& country){ country_ = country; }
    void year(int year){ year_ = year;}
    void champs(int champs){champs_ = champs;}
    void budget (int budget){budget_ = budget;}

  private:
    std::string name_;
    std::string country_;
    int year_{};
    int champs_{};
    int budget_{};

};

std::ostream& operator<<(std::ostream&, const Team&);

