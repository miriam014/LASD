#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************** */

#include "mappable.hpp"

/* ************************** */

namespace lasd {

/* ************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderMappableContainer<Data>,
  virtual public PostOrderMappableContainer<Data>{

private:

protected:
  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************ */

  // Copy assignment
  LinearContainer& operator = (const LinearContainer& ) = delete; 

  // Move assignment
  LinearContainer& operator = (LinearContainer&& ) noexcept = delete; 

  /* ************************ */

  // Comparison operators
  bool operator == (const LinearContainer& other ) const noexcept;  
  inline bool operator != (const LinearContainer& other ) const noexcept{ return !operator == (other); }; 

  /* ************************ */

  // Specific member functions

  virtual const Data & operator [] (ulong) const = 0; //throw std::out_of_range when out of range
  virtual Data & operator [] (ulong) = 0; // throw std::out_of_range when out of range
  inline virtual const Data & Front() const; // throw std::length_error when empty
  inline virtual Data & Front(); // throw std::length_error when empty

  inline virtual const Data & Back() const; // throw std::length_error when empty
  inline virtual Data & Back(); // throw std::length_error when empty

  /* ************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  void Traverse(TraverseFun) const override; 

  /* ************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  void PreOrderTraverse(TraverseFun) const override; 

  /* ************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  void PostOrderTraverse(TraverseFun) const override; 

  /* ************************ */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;
  void Map(MapFun)  override; 

  /* ************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  void PreOrderMap(MapFun)  override; 

  /* ************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  void PostOrderMap(MapFun)  override;  

};

/* ************************** */

template <typename Data>
class SortableLinearContainer : virtual public LinearContainer<Data> {

private:

protected:
  using Container::size;
  
public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************ */

  // Copy assignment
  SortableLinearContainer& operator = (const SortableLinearContainer& ) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer& operator = (SortableLinearContainer&& ) noexcept = delete; // Move assignment of abstract types is not be possible.

  /* ************************ */

  // Comparison operators
  inline bool operator == (const SortableLinearContainer& other) const noexcept;  // Comparison of abstract types is possible.
  inline bool operator != (const SortableLinearContainer& other) const noexcept{ return !operator == (other); }; // type operator!=(argument) specifiers; // Comparison of abstract types is possible.

  /* ************************ */

  // Specific member function
  virtual void Sort() noexcept; 

protected:

  // Auxiliary member functions
  void QuickSort(ulong first, ulong last) noexcept;
  ulong Partition(ulong first, ulong last) noexcept;  

};

/* ************************** */

}

#include "linear.cpp"

#endif