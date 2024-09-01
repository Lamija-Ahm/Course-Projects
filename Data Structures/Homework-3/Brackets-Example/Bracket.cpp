#include <iostream>
#include <stack>
#include <string>

bool matching(const std::string& line) {
    std::stack<char> brackets;

    for (char c : line) {
        if (c == '(' || c == '[' || c == '{' || c == '<') {
            brackets.push(c);
        }
        else if (c == ')' || c == ']' || c == '}' || c == '>') {
            if (brackets.empty()) return false;
            char last_open = brackets.top();
            brackets.pop();
            if ((c == ')' && last_open != '(') ||
                (c == ']' && last_open != '[') ||
                (c == '}' && last_open != '{') ||
                (c == '>' && last_open != '<')) {
                return false;
            }
        }
    }
  
    return brackets.empty();
}

int main() {
    std::string unos;
    while (std::getline(std::cin, unos)) {
        if (matching(unos)) {
            std::cout << "Dobar" << std::endl;
        } else {
            std::cout << "Pogresan" << std::endl;
        }
    }
    return 0;
}
