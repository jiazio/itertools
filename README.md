itertools
=========

暇つぶしがてらにPythonの組み込み関数やItertoolsの中から幾つかをC++のイテレータとして実装したものです。

enumerate
---------
```
std::vector<std::string> v{"foo", "bar", "baz", "qux"};

for (auto x : enumerate(x))
  std::cout << "(" << std::get<0>(x) << ", " << std::get<1>(x) << "), ";
      // => (foo, 0), (bar, 1), (baz, 2), (qux, 3), 
```
```
std::vector<std::string> v{"foo", "bar", "baz", "qux"};

for (auto x : emumerate(x, 100))
  std::cout << "(" << std::get<0>(x) << ", " << std::get<1>(x) << "), ";
      // => (foo, 100), (bar, 101), (baz, 102), (qux, 103), 

```

zip
---

```
std::list<std::string> u{"hoge", "fuga", "piyo"};
std::vector<std::string> v{"foo", "bar", "baz", "qux"};
std::vector<int> w{0, 1, 2};

for (auto x ' zip(u, v, w))
  std::cout << "(" << std::get<0>(x) << ", " << std::get<1>(x) << ", " << std::get<2>(x) << "), ";
      // => (hoge, foo, 0), (fuga, bar, 1), (piyo, baz, 2),
```
  
  
