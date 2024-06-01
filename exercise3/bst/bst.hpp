
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer,
  virtual public DictionaryContainer<Data>,
  virtual public BinaryTree<Data>,
  virtual public BinaryTreeLnk<Data> {

private:

protected:

  using Container::size;
  using BinaryTreeLnk<Data>::root;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data>& ); 
  BST(MappableContainer<Data>&& ) noexcept; 

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST<Data>& operator=(const BST& );

  // Move assignment
  BST<Data>& operator=(BST&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BST& ) const noexcept;
  inline bool operator != (const BST& other ) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data& ) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data& ); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data& ); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data& ) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data& ); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data& ); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)
  const NodeLnk& Root() const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data& ) override; // Copy of the value
  bool Insert(Data&& ) noexcept override;  // Move of the value
  bool Remove(const Data & ) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data& ) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  inline void Clear() override;

protected:

  // Auxiliary functions, if necessary!

  Data DataNDelete(NodeLnk* );
  
  NodeLnk* Detach(NodeLnk *&) noexcept;

  NodeLnk* DetachMin(NodeLnk *&) noexcept;
  NodeLnk* DetachMax(NodeLnk *&) noexcept;

  NodeLnk* Skip2Left(NodeLnk *&) noexcept;
  NodeLnk* Skip2Right(NodeLnk *&) noexcept;

  // type FindPointerToMin(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk* const &FindPointerToMin(NodeLnk *const &) const noexcept;
  NodeLnk*& FindPointerToMin(NodeLnk *&) noexcept;

  // type FindPointerToMax(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk* const &FindPointerToMax(NodeLnk *const &) const noexcept;
  NodeLnk*& FindPointerToMax(NodeLnk *&) noexcept;

  // type FindPointerTo(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk*const& FindPointerTo(NodeLnk *const &, Data ) const noexcept;
  NodeLnk*& FindPointerTo(NodeLnk *&, Data ) noexcept;

  // type FindPointerToPredecessor and Successor(argument) specifiers; 
  //mutable versions
  NodeLnk* const& FindPointerToPredecessor(NodeLnk *const &, Data ) const noexcept;
  NodeLnk* const& FindPointerToSuccessor(NodeLnk *const &, Data ) const noexcept;
 // unmutable versions
  NodeLnk*& FindPointerToPredecessor(NodeLnk *&, Data ) noexcept;
  NodeLnk*& FindPointerToSuccessor(NodeLnk *&, Data ) noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
