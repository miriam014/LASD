
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>,
 virtual protected List<Data>{

private:

protected:

  using List<Data>::size;

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const TraversableContainer<Data> &);

  QueueLst(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst &);

  // Move constructor
  QueueLst(QueueLst &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueLst &operator=(const QueueLst& );

  // Move assignment
  inline QueueLst &operator=(QueueLst&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const QueueLst& ) const noexcept;

  bool operator != (const QueueLst& ) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline Data &Head() override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  inline const Data &Head() const override; // Override Queue member (mutable version; must throw std::length_error when empty)
  
  inline void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  
  inline void Enqueue(const Data &) override; // Override Queue member (copy of the value)
  inline void Enqueue(Data &&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
