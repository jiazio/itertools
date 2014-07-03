#ifndef _ZIP_HPP_
#define _ZIP_HPP_

#include <iterator>
#include <tuple>
#include <utility>

namespace {
  template <class Tuple, class F, size_t... I>
  auto apply_impl(Tuple & its, F && f, std::index_sequence<I...>) -> decltype(auto)
  {
    return std::make_tuple(f(std::get<I>(its))...);
  }

  template <class Tuple, class F, size_t... I>
  auto apply_impl(Tuple & lhs, Tuple & rhs, F && f, std::index_sequence<I...>) -> decltype(auto)
  {
    return std::make_tuple(f(std::get<I>(lhs), std::get<I>(rhs))...);
  }

  template <class Tuple, class F, class Indices = std::make_index_sequence<std::tuple_size<Tuple>::value>>
  auto apply(Tuple & its, F && f) -> decltype(auto)
  {
    return apply_impl(its, std::forward<F>(f), Indices());
  }

  template <class Tuple, class F, class Indices = std::make_index_sequence<std::tuple_size<Tuple>::value>>
  auto apply(Tuple & lhs, Tuple & rhs, F && f) -> decltype(auto)
  {
    return apply_impl(lhs, rhs, std::forward<F>(f), Indices());
  }

  bool any_impl() { return false; }

  template <class First, class... Rest>
  bool any_impl(First first, Rest... rest)
  {
    return first || any_impl(rest...);
  }

  template <class Tuple, size_t... I>
  bool any(Tuple & t, std::index_sequence<I...>)
  {
    return any_impl(std::get<I>(t)...);
  }

  template <class Tuple, class Indices = std::make_index_sequence<std::tuple_size<Tuple>::value>>
  bool any_equal(const Tuple & lhs, const Tuple & rhs)
  {
    auto t = apply_impl(lhs, rhs, [](auto x, auto y){ return x == y; }, Indices());
    return any(t, Indices());
  }
};

template <class... Containers>
class ZipIterator;

template <class... Containers>
class Zipper
{
  public:
    Zipper(const Containers&...  containers)
      : containers_(std::make_tuple(containers...)) {}

    ZipIterator<Containers...> begin() const
    {
      return ZipIterator<Containers...>(apply(containers_, [](auto& c){ return std::begin(c);}));
    }
    ZipIterator<Containers...> end() const
    {
      return ZipIterator<Containers...>(apply(containers_, [](auto& c){ return std::end(c); }));
    }
  private:
    const std::tuple<Containers...> containers_;
};

template <class... Containers>
class ZipIterator
  : public std::iterator<std::input_iterator_tag, std::tuple<Containers...>>
{
  friend class Zipper<Containers...>;

  public:
    bool operator==(const ZipIterator & it) const
    {
      return any_equal(it.its_, its_);
    }

    bool operator!=(const ZipIterator & it) const
    {
      return !operator==(it);
    }

    ZipIterator operator++()
    {
      apply(its_, [](auto& it) { return it++; });
      return *this;
    }

    ZipIterator operator++(int)
    {
      auto result = *this;
      apply(its_, [](auto& it) { return it++; });
      return result;
    }

    auto operator*() const -> decltype(auto)
    {
      return apply(its_, [](auto it) { return *it; });
    }

  private:
    ZipIterator(std::tuple<typename Containers::const_iterator...> && its)
      : its_(its) {}
    std::tuple<typename Containers::const_iterator...> its_;
};

template <class... Containers>
inline auto zip(const Containers&... containers) -> decltype(auto)
{
  return Zipper<Containers...>(containers...);
}

#endif
