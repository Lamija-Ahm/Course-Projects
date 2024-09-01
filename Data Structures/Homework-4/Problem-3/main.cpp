#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

std::string toLower(const std::string& str) {
    std::string lowerStr;
    for (char c : str) {
        lowerStr += std::tolower(c);
    }
    return lowerStr;
}

int main() {
    std::ifstream file("story.txt");
    if (!file.is_open()) {
        std::cerr << "Ne moze se otvoriti" << std::endl;
        return 1;
    }

    std::map<std::string, std::vector<int>> wordPos;
    std::string line, word;
    int pos = 0;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        while (stream >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return std::ispunct(c); }), word.end());
            word = toLower(word);
            wordPos[word].push_back(pos);
            pos += word.length() + 1;
        }
    }

    file.close();

    for (const auto& entry : wordPos) {
        std::cout << "Rijec je '" << entry.first << "' i nalazi se na sljedecim pozicijama:" << std::endl;
        for (int pos : entry.second) {
            std::cout << pos << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}
