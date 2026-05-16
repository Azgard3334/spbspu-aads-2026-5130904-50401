#include <iostream>
#include <string>
#include <limits>

#include "list.hpp"

struct IteratorRange {
  std::string name;
  rizatdinov::LIter<unsigned> begin;
  rizatdinov::LIter<unsigned> end;
};

int main() {
  namespace riz = rizatdinov;

  riz::List<unsigned> lnum;
  riz::List<IteratorRange> result;

  size_t size = 0;
  std::string name;
  try {
    std::cin >> name;

    auto begin = lnum.before_begin();
    for (auto i = result.before_begin(); !std::cin.eof(); ++i) {
      IteratorRange range{ name, begin, begin };

      size_t len = 0;
      unsigned num = 0;
      for (auto j = begin; std::cin >> num; ++j) {
        begin = lnum.insert_after(j, num);
        ++len;
      }

      size = len > size ? len : size;

      range.end = begin;

      result.insert_after(i, range);

      if (!std::cin.eof() && std::cin.fail()) {
        std::cin.clear();
        if (std::cin.peek() == '\n' || std::cin.peek() == ' ') {
          throw std::overflow_error("Error: overflow");
        }
        std::cin >> name;
      }
    }
  } catch (const std::bad_alloc& e) {
    std::cerr << "Error: failed to allocate memory" << std::endl;
    return 1;
  } catch (const std::overflow_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  for (auto i = result.begin(); i != result.end(); ++i) {
   ++(*i).begin;
   ++(*i).end;
  }

  if (lnum.is_empty()) {
    if (name.length()) {
      std::cout << name << '\n' << 0 << std::endl;
    } else {
      std::cout << 0 << std::endl;
    }
    return 0;
  }

  bool first = true;
  for (auto i = result.cbegin(); i != result.cend(); ++i) {
    if (!first) {
      std::cout << ' ';
    }
    first = false;
    std::cout << (*i).name;
  }
  std::cout << std::endl;

  riz::List<unsigned> summ;
  try {
    auto iterator_summ = summ.before_begin();
    for (size_t i = 0; i < size; ++i) {
      first = true;
      unsigned summa = 0;
      for (auto j = result.begin(); j != result.end(); ++j) {
        if ((*j).begin == (*j).end) {
          continue;
        }
        if (!first) {
          std::cout << ' ';
        }
        std::cout << *(*j).begin;
        first = false;
        if (summa > std::numeric_limits<unsigned>::max()  - *(*j).begin) {
          throw std::overflow_error("Error: overflow");
        }
        summa += *(*j).begin;
        ++(*j).begin;
      }
      std::cout << std::endl;

      iterator_summ = summ.insert_after(iterator_summ, summa);
    }
  } catch (const std::bad_alloc& e) {
    std::cerr << "Error: Failed to allocate memory" << std::endl;
    return 1;
  } catch (const std::overflow_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  first = true;
  for (auto i = summ.cbegin(); i != summ.cend(); ++i) {
    if (!first) {
      std::cout << ' ';
    }
    first = false;
    std::cout << *i;
  }
  std::cout << std::endl;

  return 0;
}
