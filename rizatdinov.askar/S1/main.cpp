#include <iostream>
#include "list.hpp"

// Examples:
// first 1 1 1 1
// second 2 2 2 2
// thrid { empty }
// fourth 4 4

int main() {
  namespace riz = rizatdinov;

  riz::List<std::pair<std::string, riz::List<unsigned>>> lpsu;
  for (auto i = lpsu.before_begin(); !std::cin.eof(); ++i) {
    std::string name;
    std::cin >> name;

    riz::List<unsigned> lnum;

    unsigned num = 0;
    for (auto j = lnum.before_begin(); std::cin >> num; ++j) {
      lnum.insert_after(j, num);
    }

    std::pair<std::string, riz::List<unsigned>> plus{ name, lnum };
    lpsu.insert_after(i, plus);

    if (!std::cin.eof() && std::cin.fail()) {
      std::cin.clear();
    }
  }

  for (auto i = lpsu.cbefore_begin(); i != lpsu.cend(); ++i) {
    std::cout << (*i).first << std::endl; 
  }

  return 0;
}
