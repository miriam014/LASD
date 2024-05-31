
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

#define starting_size_vec 10
#define REDUCE_4 4
#define REDUCE_2 2
#define INCREASE_2 2

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>,
  virtual protected Vector<Data>{

private:

protected:

  using Container::size;
  using Vector<Data>::Vett;
  ulong n_elem = 0;

public:

  // Constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const TraversableContainer<Data> & cont);
  StackVec(MappableContainer<Data> && cont);

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec& );

  // Move constructor
  StackVec(StackVec&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&); 

  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const StackVec& ) const noexcept;
  inline bool operator != (const StackVec& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override;
  Data& Top() override;
  void Pop() override;
  Data TopNPop() override;
  void Push(const Data &) override;
  void Push(Data &&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override { return n_elem == 0; }

  inline ulong Size() const noexcept override { return n_elem; }

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

  void Resize(const ulong s) override;

protected:

  // Auxiliary functions

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
