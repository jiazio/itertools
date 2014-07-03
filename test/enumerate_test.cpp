#include <boost/test/unit_test.hpp>

#include <vector>
#include <list>

#include "../include/enumerate.hpp"

BOOST_AUTO_TEST_SUITE(enumerate_test)

BOOST_AUTO_TEST_CASE(enumerate_test1)
{
  std::vector<int> seq{0, 1, 2, 3, 4, 5};
  std::vector<float> v{1, 2, 3, 4, 5, 6}; 
  
  auto it0 = v.begin();
  auto it1 = seq.begin();
  
  for (auto x : enumerate(v))
  {
    BOOST_CHECK_EQUAL(std::get<0>(x), *it0++);
    BOOST_CHECK_EQUAL(std::get<1>(x), *it1++);
  }
}

BOOST_AUTO_TEST_CASE(enumerate_test2)
{
  std::vector<int> seq{0, 1, 2, 3};
  std::list<std::string> v{"foo", "bar", "baz", "qux"};
  
  auto it0 = v.begin();
  auto it1 = seq.begin();
  
  for (auto x : enumerate(v))
  {
    BOOST_CHECK_EQUAL(std::get<0>(x), *it0++);
    BOOST_CHECK_EQUAL(std::get<1>(x), *it1++);
  }
}

BOOST_AUTO_TEST_SUITE_END();

