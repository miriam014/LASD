
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

#define starting_size_qeq 10
#define REDUCE_4 4
#define REDUCE_2 2
#define INCREASE_2 2

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,
 virtual protected Vector<Data> {

private:

protected:

  using Vector<Data>::Vett;
  using Container::size;
  ulong testa=0, coda=0, N_ele=0;

public:

  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data> &);

  QueueVec(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec& );

  // Move constructor
  QueueVec(QueueVec&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueVec &operator=(const QueueVec& );

  // Move assignment
  inline QueueVec &operator=(QueueVec&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const QueueVec& other) const noexcept;

  inline bool operator != (const QueueVec& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline const Data &Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  inline Data &Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  inline void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data &) override; // Override Queue member (copy of the value)
  void Enqueue(Data &&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override;

  ulong Size() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  
  inline void Clear() override;

  void Resize(const ulong ) override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
