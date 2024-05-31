#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public ResizableContainer,
  virtual public LinearContainer<Data> {

private:

protected:

  using Container::size;
  Data* Vett = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong N); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data>& ); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data>&& ) noexcept; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector&);

  // Move constructor
  Vector(Vector&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector() {delete[] Vett;};

  /* ************************************************************************ */

  // Copy assignment
  inline Vector& operator = (const Vector&);

  // Move assignment
  inline Vector& operator = (Vector&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const Vector &) const noexcept;
  inline bool operator != (const Vector &other) const noexcept { return !operator == (other);};

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  void Resize(const ulong) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](const ulong) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data & operator[](const ulong) override; 

  const Data & Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data & Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data & Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data & Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>,
  virtual public SortableLinearContainer<Data>{

private:

protected:

  using Container::size;

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  inline SortableVector(ulong other):Vector<Data>(other){}; // A vector with a given initial dimension
  inline SortableVector(const TraversableContainer<Data> &other): Vector<Data>::Vector(other){}; // A vector obtained from a TraversableContainer
  inline SortableVector(MappableContainer<Data> &&other): Vector<Data>::Vector(std::move(other)){}; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  inline explicit SortableVector(const SortableVector<Data> &other): Vector<Data>::Vector(other){};

  // Move constructor
  inline explicit SortableVector(SortableVector<Data> &&other) noexcept: Vector<Data>::Vector(std::move(other)){};

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline SortableVector<Data> & operator=(const SortableVector& );

  // Move assignment
  inline SortableVector<Data> & operator=(SortableVector&& ) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
