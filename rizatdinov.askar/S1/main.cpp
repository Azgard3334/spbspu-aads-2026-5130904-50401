#include <iostream>
#include <string>
#include <limits>

#include "list.hpp"

int main() {
  namespace riz = rizatdinov;

  size_t max_size = 1;

  riz::List<std::pair<std::string, riz::List<long unsigned>>> result;
  riz::List<riz::List<long unsigned>::const_iterator> range;
  riz::List<long unsigned> summ{0};

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
      long unsigned num = 0;
      auto k = lnum.before_begin();
      auto g = summ.before_begin();
      while (std::cin >> num) {
        k = lnum.insert_after(k, num);
        if (!summ.is_empty() && (*g) > std::numeric_limits<long unsigned>::max() - num) {
          throw std::overflow_error("Error: overflow");
        }

        ++size;

        auto c = g++;
        if (g == summ.end()) {
          g = summ.insert_after(c, num);
        } else {
          (*g) += num;
        }
     }

      if (!std::cin.eof() && std::cin.fail()) {
        std::cin.clear();
        if (std::cin.peek() == '\n' || std::cin.peek() == ' ') {
          throw std::overflow_error("Error: overflow");
        }
      }

      max_size = max_size < size ? size : max_size;

      std::pair<std::string, riz::List<long unsigned>> pair{ name, lnum };
      i = result.insert_after(i, pair);
      j = range.insert_after(j, (*i).second.cbegin());
    }
  } catch (const std::bad_alloc& e) {
    std::cerr << "Error: failed to allocate memory" << std::endl;
    return 1;
  } catch (const std::overflow_error& e) {
    std::cerr << e.what() << std::endl;
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
    if (!flag) { std::cout << std::endl; }

    flag = true;
    for (auto j = range.begin(); j != range.end(); ++j) {
      if ((*j) == riz::List<long unsigned>::const_iterator(nullptr)) {
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
    std::cout << std::endl;
  }

  flag = true;
  for (auto i = summ.begin(); i != summ.end(); ++i) {
    if (!flag) {
      std::cout << ' ';
    }
    flag = false;
    std::cout << *i;
  }
  std::cout << std::endl;

  return 0;
}
