
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd { 
  
/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data>{

private:

protected:

  using Container::size;


  struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode {

  friend class BinaryTreeLnk<Data>;

  private:

  protected:

  public:

  Data element {};
  NodeLnk* left = nullptr;
  NodeLnk* right = nullptr;

   //Costructors
    NodeLnk(const Data& );
    NodeLnk(Data&& ) noexcept;

    // Copy constructor
    NodeLnk(const NodeLnk & other);
    // Move constructor
    NodeLnk(NodeLnk && other) noexcept;

    //Distructor
    virtual ~NodeLnk();

    // Specific member functions

    Data& Element() noexcept override {return element;}; 
    const Data& Element() const noexcept override {return element;}; 

    bool HasLeftChild() const noexcept override {return left != nullptr;};
    bool HasRightChild() const noexcept override {return right != nullptr;}; 

    //binarytree
    const NodeLnk& LeftChild() const override; 
    const NodeLnk& RightChild() const override; 

    //mutable
    NodeLnk& LeftChild() override; 
    NodeLnk& RightChild() override; 
    
    bool IsLeaf() const noexcept override {return (!HasLeftChild() && !HasRightChild());};

  };

  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data>& ); 
  BinaryTreeLnk(MappableContainer<Data>&& ); 

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BinaryTreeLnk&) const noexcept;
  inline bool operator != (const BinaryTreeLnk& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  const NodeLnk& Root() const override; //(throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  NodeLnk& Root() override; // (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; 

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif