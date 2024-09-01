#pragma once

#include "teams.hpp"

#include <vector>

class f1_teams : public std::vector<Team>
  {
    public:



    bool ucitaj(const std::string& file);
bool compare(const f1_teams& a, const f1_teams& b);

  };

void filter_duplicates(std::vector<Team>& teams) {
    auto it = teams.begin();
    while (it != teams.end()) {
        auto it_other = it + 1;
        while (it_other != teams.end()) {
            if (it->name() == it_other->name() && it->country() == it_other->country()) {
                it->year(std::min(it->year(), it_other->year()));
                it->champs(it->champs() + it_other->champs());
                it->budget(it->budget() + it_other->budget());
                it_other = teams.erase(it_other);
            } else {
                ++it_other;
            }
        }
        ++it;
    }
}
