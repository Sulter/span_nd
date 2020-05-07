# span_nd

[![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/FnMmEF)
[![Standard](https://img.shields.io/badge/c%2B%2B-14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)

Multi dimensional [std::span](https://en.cppreference.com/w/cpp/container/span).  
The aim is to provide a `std::span` like interface and performance, but with multi-dimensional access and manipulation.

## Usage

[Try it out online!](https://godbolt.org/z/FnMmEF)  
  
Any type contiguous memory (C-array, std::vector, std::array) are easily converted to a span_nd:

```cpp
int array[100];
span_nd<int, 2> twoD(array, 100, {10, 10});

//works like all other containers
std::iota(twoD.begin(), twoD.end(), 0);

//easy access with [] operator
twoD[{8, 8}] = -1;

//you can get cross_section of dimensions:
//fill second row with 2
std::fill(twoD.cross_section(1).begin(), twoD.cross_section(1).end(), 2);
```
