#include <boost/test/unit_test.hpp>

#include <vector>
#include <list>
#include <array>

#include "../include/zip.hpp"

BOOST_AUTO_TEST_SUITE(zip_tset);
BOOST_AUTO_TEST_CASE(zip_test1)
{
  std::vector<int> v0{1, 2, 3, 4};
  std::vector<int> v1{1, 2, 3, 4};
  std::vector<int> v2{1, 2, 3, 4};

  auto z = zip(v0, v1, v2);

  auto it0 = v0.begin();
  auto it1 = v1.begin();
  auto it2 = v2.begin();

  for (auto it = z.begin(); it != z.end(); ++it)
  {
    BOOST_CHECK_EQUAL(std::get<0>(*it), *it0++);
    BOOST_CHECK_EQUAL(std::get<1>(*it), *it1++);
    BOOST_CHECK_EQUAL(std::get<2>(*it), *it2++);
  }
}

BOOST_AUTO_TEST_CASE(zip_test2)
{
  std::vector<int> v0{1, 2, 3, 4};
  std::list<std::string> v1{"foo", "bar", "baz", "qux"};
  std::array<double, 5> v2{1.0, 2.0, 3.0, 4.0, 5.0};

  auto z = zip(v0, v1, v2);

  auto it0 = v0.begin();
  auto it1 = v1.begin();
  auto it2 = v2.begin();

  for (auto it = z.begin(); it != z.end(); ++it)
  {
    BOOST_CHECK_EQUAL(std::get<0>(*it), *it0++);
    BOOST_CHECK_EQUAL(std::get<1>(*it), *it1++);
    BOOST_CHECK_EQUAL(std::get<2>(*it), *it2++);
  }
}
BOOST_AUTO_TEST_SUITE_END()
