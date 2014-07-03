#ifndef _ENUMERATE_HPP_
#define _ENUMERATE_HPP_

#include <iterator>
#include <tuple>

template <class Container>
class enumerateIterator;

template <class Container>
class Enumerator
{
  public:
    Enumerator(Container & container, int start = 0)
      : container_(container), start_(start) {}

    enumerateIterator<Container> begin() const
    {
      return enumerateIterator<Container>(container_.cbegin(), start_);
    }

    enumerateIterator<Container> end() const
    {
      return enumerateIterator<Container>(container_.cend(), start_ + container_.size());
    }

  private:
    Container container_;
    int start_;
};

template <class Container>
class enumerateIterator
  : public std::iterator< std::input_iterator_tag, std::tuple<typename Container::value_type, int>>
{
  friend class Enumerator<Container>;

public:
  using value_type = std::tuple<typename Container::value_type, int>;

  bool operator==(const enumerateIterator & it) const
  {
    return it.it_ == it_;
  }

  bool operator!=(const enumerateIterator & it) const
  {
    return !operator==(it);
  }

  value_type operator*() const
  {
    return std::make_tuple(*it_, counter_);
  }

  enumerateIterator operator++()
  {
    counter_++;
    it_++;
    return *this; 
  }

  enumerateIterator operator++(int) 
  {
    auto result = *this;
    counter_++;
    it_++;
    return result;
  }

private:
  enumerateIterator(typename Container::const_iterator && it, int n)
    : it_(it), counter_(n) {}
  int counter_;
  typename Container::const_iterator it_;
};

template <class Container>
Enumerator<Container> enumerate(Container & container, int start = 0)
{
  return Enumerator<Container>(container, start);
}

#endif
