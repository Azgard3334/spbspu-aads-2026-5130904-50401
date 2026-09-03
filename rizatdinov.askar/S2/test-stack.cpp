#define BOOST_TEST_MODULE StackTest
#include <boost/test/included/unit_test.hpp>

#include "stack.hpp"
#include <list.hpp>

BOOST_AUTO_TEST_SUITE(stack_tests)

BOOST_AUTO_TEST_CASE(push) {
  rizatdinov::Stack<int, rizatdinov::List<int>> stk;

  stk.push(10);
  BOOST_CHECK_EQUAL(stk.top(), 10);
  stk.push(20);
  BOOST_CHECK_EQUAL(stk.top(), 20);
  stk.push(30);
  BOOST_CHECK_EQUAL(stk.top(), 30);

  int val = 10;
  stk.push(val);
  BOOST_CHECK_EQUAL(stk.top(), 10);
  val = 20;
  stk.push(val);
  BOOST_CHECK_EQUAL(stk.top(), 20);
  val = 30;
  stk.push(val);
  BOOST_CHECK_EQUAL(stk.top(), 30);
}

BOOST_AUTO_TEST_CASE(pop) {
  rizatdinov::List<int> lst{ 30, 20, 10 };
  rizatdinov::Stack<int, rizatdinov::List<int>> stk(lst);

  BOOST_CHECK_EQUAL(stk.top(), 30);
  stk.pop();
  BOOST_CHECK_EQUAL(stk.top(), 20);
  stk.pop();
  BOOST_CHECK_EQUAL(stk.top(), 10);
  stk.pop();

  BOOST_CHECK_THROW(stk.pop(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(drop) {
  rizatdinov::List<int> lst{ 30, 20, 10 };
  rizatdinov::Stack<int, rizatdinov::List<int>> stk(lst);

  int val = stk.drop();
  BOOST_CHECK_EQUAL(val, 30);
  val = stk.drop();
  BOOST_CHECK_EQUAL(val, 20);
  val = stk.drop();
  BOOST_CHECK_EQUAL(val, 10);

  BOOST_CHECK_THROW(stk.drop(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(empty) {
  rizatdinov::List<int> lst{ 30, 20, 10 };
  rizatdinov::Stack<int, rizatdinov::List<int>> stk1(lst);
  rizatdinov::Stack<int, rizatdinov::List<int>> stk2;

  BOOST_CHECK_EQUAL(stk1.empty(), false);
  BOOST_CHECK_EQUAL(stk2.empty(), true);
}

BOOST_AUTO_TEST_SUITE_END()
