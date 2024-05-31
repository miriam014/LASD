
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>,
 virtual protected List<Data>{

private:

protected:

  using List<Data>::List;
  using Container::size;
  
public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const TraversableContainer<Data> & ); // A stack obtained from a TraversableContainer
  StackLst(MappableContainer<Data> && );  // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  inline StackLst(const StackLst& );

  // Move constructor
  inline StackLst(StackLst&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator = (const StackLst& );

  // Move assignment
  StackLst& operator = (StackLst&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const StackLst & other) const noexcept {return List<Data>::operator==(other); }
  inline bool operator != (const StackLst & other) const noexcept {return List<Data>::operator!=(other); }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  inline const Data & Top() const override;
  inline Data & Top() override;
  inline void Pop() override;
  inline Data TopNPop() override;
  inline void Push(const Data &) override;
  inline void Push(Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
