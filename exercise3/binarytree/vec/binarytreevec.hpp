#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"
#include "../../container/container.hpp"

/* ************************** */

namespace lasd {

/* ************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data>{

private:

protected:

  using Container::size;
  struct NodeVec : virtual public MutableBinaryTree<Data>::MutableNode { 
    
  private:

  protected:

    const ulong Index() const {return index;};
    
  public:

    Data element{};
    ulong index;
    BinaryTreeVec<Data> *tree;

    // Specific constructors
    NodeVec(const Data& ,ulong , BinaryTreeVec<Data>* );
    NodeVec(Data&& ,ulong , BinaryTreeVec<Data>* ) noexcept;

    //destructor
    virtual ~NodeVec();

    //copy assignment
    NodeVec& operator=(const NodeVec& );
    //move assignment
    NodeVec& operator=(NodeVec&& ) noexcept;

    //specific member functions
    inline virtual const Data& Element() const noexcept override { return element; }
    inline virtual Data& Element() noexcept override { return element; }

    virtual bool HasLeftChild() const noexcept override;
    virtual bool HasRightChild() const noexcept override;

    virtual NodeVec& RightChild() override;
    virtual const NodeVec& RightChild() const override;

    virtual NodeVec& LeftChild() override;
    virtual const NodeVec& LeftChild() const override;


    bool IsLeaf() const noexcept override {return !HasLeftChild() && !HasRightChild();};

  };

  Vector<NodeVec*> root;

public:

  // Default constructor
  BinaryTreeVec() : root(0) {;};

  /* ************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data>&& ) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************ */

  // Comparison operators
  inline bool operator == (const BinaryTreeVec& other) const noexcept {return BinaryTree<Data>::operator==(other);};
  inline bool operator != (const BinaryTreeVec& other) const noexcept {return BinaryTree<Data>::operator!=(other);};

  /* ************************ */

  // Specific member functions (inherited from BinaryTree)
  virtual const NodeVec& Root() const override; // (throw std::length_error when empty)

  /* ************************ */
  
  // Specific member function (inherited from MutableBinaryTree)
  virtual NodeVec& Root() override; //  (throw std::length_error when empty)

  /* ************************ */

  // Specific member function (inherited from ClearableContainer)
  virtual void Clear() override; 

  /* ************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  using typename BreadthTraversableContainer<Data>::TraverseFun;
  void BreadthTraverse(TraverseFun) const override; 

  /* ************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  using typename BreadthMappableContainer<Data>::MapFun;
  void BreadthMap(MapFun) override;  

protected:

  // Auxiliary functions, if necessary!

};

/* ************************** */

}

#include "binarytreevec.cpp"

#endif