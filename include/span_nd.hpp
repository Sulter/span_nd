#ifndef SPAN_ND_HPP_INCLUDED
#define SPAN_ND_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <numeric>
#include <array>
#include <stdexcept>

#if defined(NDEBUG) && !defined(SPAN_ND_BOUNDARY_CHECK)
  #define SPAN_ND_DONT_BOUNDARY_CHECK
#endif

template <typename T, std::size_t Dims>
class span_nd {
public:
  using value_type      = T;
  using size_type       = std::size_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = value_type*;
  using const_pointer   = const value_type*;
  using iterator        = pointer;
  using const_iterator  = const_pointer;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // constructors
  // constructs an N-dimensional view of an existing buffer
  constexpr span_nd(pointer ptr, size_type len, const std::array<size_type, Dims>& arr)
  : ptr(ptr)  
  , length(len)
  , dim(arr)
  {
    //possible sanity check, maybe if !NDEBUG, like most std::span implementations?
    size_type acc = std::accumulate(arr.begin(), arr.end(), 1, std::multiplies<size_type>());
    if(acc > len)
      throw std::invalid_argument("size not big enough for required width and height");
  }
  constexpr span_nd(const span_nd& rhs) noexcept = default;

  /* TODO: ctors need to be expanded for things like construction from iterator pairs */
  constexpr span_nd& operator=(const span_nd& rhs) noexcept = default;

  // subviews
  // takes a cross section of the view indexed by the highest dimension
  constexpr span_nd<T, Dims - 1> cross_section(size_type slice)
  {
    if(slice >= dim.back())
      throw std::out_of_range("Taking slice outside range of highest dim");

    std::array<size_type, Dims - 1> newDim;
    std::copy(dim.begin(), dim.begin() + newDim.size(), newDim.begin());

    size_type newLen = std::accumulate(newDim.begin(), newDim.end(), 1, std::multiplies<size_type>());

    std::array<size_type, Dims> tmp = {};
    tmp.back() = slice;

    T* newPtr = &(*this)[tmp];

    return span_nd<T, Dims - 1>(newPtr, newLen, newDim);
  };

  // e.g. span[{x, y, z}]
  constexpr reference operator[](const std::array<size_type, Dims>& arr)
  {
    size_type index = arr[0];
    for(size_type i = 0; i < Dims - 1; i++)
    {
      index += arr[i + 1] * std::accumulate(dim.begin(), dim.begin() + i + 1, 1, std::multiplies<size_type>());
    }

    //possible sanity check, maybe if !NDEBUG, like most std::span implementations?
    if(index > length)
      throw std::out_of_range("Indexing higher than size of span");

    /* or possibly, as a policy?
    if(std::mismatch(arr.begin(), arr.end(), dim.begin(), std::less<>{}).first != arr.end())
    {
      throw std::out_of_range("Index x higher than [...]");
    }
    */

    return *(ptr + index);
  }

  constexpr const_reference operator[](const std::array<size_type, Dims>& arr) const;

  constexpr pointer data() noexcept
  {
    return ptr;
  }

  constexpr const_pointer data() const noexcept
  {
    return ptr;
  }

  constexpr reference front() noexcept
  {
    return *ptr;
  }

  constexpr const_reference front() const noexcept
  {
    return *ptr;
  }

  constexpr reference back() noexcept
  {
    return *(ptr + length);
  }

  constexpr const_reference back() const noexcept
  {
    return *(ptr + length);
  }

  // iterators
  constexpr iterator begin()  noexcept
  {
    return ptr;
  }
  constexpr const_iterator begin()  const noexcept;
  constexpr const_iterator cbegin() const noexcept;

  constexpr reverse_iterator rbegin() noexcept;
  constexpr const_reverse_iterator rbegin() const noexcept;
  constexpr const_reverse_iterator crbegin() const noexcept;

  constexpr iterator end() noexcept
  {
    return (ptr + length);
  }
  constexpr const_iterator end() const noexcept;
  constexpr const_iterator cend() const noexcept;

  constexpr reverse_iterator rend() noexcept;
  constexpr const_reverse_iterator rend() const noexcept;
  constexpr const_reverse_iterator crend() const noexcept;

  // observers
  constexpr size_type size() const noexcept
  {
    return length;
  }
  
  constexpr size_type size_bytes() const noexcept
  {
    return length + sizeof(value_type);
  }

  constexpr bool empty() const noexcept
  {
    return length == 0;
  }

  constexpr std::array<size_type, Dims> dimensions()
  {
    return dim;
  }

private:
  pointer   ptr                  = nullptr; // pointer to data
  size_type length               = 0;       // number of elements in the span
  std::array<size_type, Dims> dim{};        // dimensions stored from lowest to highest order (e.g. width, height, depth)
};

// typedefs for commonly used dimensions
template <typename T>
using span_2d = span_nd<T, 2>;

template <typename T>
using span_3d = span_nd<T, 3>;

template <typename T>
using span_4d = span_nd<T, 4>;

#endif // SPAN_ND_HPP_INCLUDED