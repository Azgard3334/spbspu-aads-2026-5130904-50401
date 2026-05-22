#include <iostream>
#include <string>
#include <limits>

#include "list.hpp"

int main() {
  namespace riz = rizatdinov;

  size_t max_size = 1;

  riz::List<std::pair<std::string, riz::List<size_t>>> result;
  riz::List<riz::List<size_t>::const_iterator> range;
  riz::List<size_t> summ{0};

  try {
    auto i = result.before_begin();
    auto j = range.before_begin();
    while (!std::cin.eof()) {
      std::string name;
      std::cin >> name;
      if (std::cin.eof()) {
        break;
      }

      riz::List<size_t> lnum;

      size_t size = 0;
      size_t num = 0;
      auto k = lnum.before_begin();
      auto g = summ.before_begin();
      while (std::cin >> num) {
        auto c = g++;
        if (g == summ.end()) {
          g = summ.insert_after(c, 0);
        }

        k = lnum.insert_after(k, num);
        if ((*g) > std::numeric_limits<size_t>::max() - num) {
          throw std::overflow_error("Error: overflow");
        }

        (*g) += num;
        ++size;
     }

      if (!std::cin.eof() && std::cin.fail()) {
        std::cin.clear();
      }

      max_size = max_size < size ? size : max_size;

      std::pair<std::string, riz::List<size_t>> pair{ name, lnum };
      i = result.insert_after(i, pair);
      j = range.insert_after(j, (*i).second.cbegin());
    }
  } catch (const std::overflow_error& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }

  bool flag = true;
  for (auto i = result.cbegin(); i != result.cend(); ++i) {
    if (!flag) {
      std::cout << ' ';
    }
    flag = false;
    std::cout << (*i).first;
  }

  for (size_t i = 0; i < max_size; ++i) {
    if (!flag) { std::cout << '\n'; }

    flag = true;
    for (auto j = range.begin(); j != range.end(); ++j) {
      if ((*j) == riz::List<size_t>::const_iterator(nullptr)) {
        continue;
      }
      if (!flag) {
        std::cout << ' ';
      }
      flag = false;
      std::cout << *((*j)++);
    }
  }

  if (!flag) {
    std::cout << '\n';
  }
  flag = true;
  for (auto i = summ.begin(); i != summ.end(); ++i) {
    if (!flag) {
      std::cout << ' ';
    }
    flag = false;
    std::cout << *i;
  }
  std::cout << '\n';

  return 0;
}
