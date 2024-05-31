
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
//#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
//#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>,
  virtual public PostOrderTraversableContainer<Data>,
  virtual public InOrderTraversableContainer<Data>,
  virtual public BreadthTraversableContainer<Data>  {

private:

protected:

  using Container::size; 

public:

  struct Node {

  protected:

  public:

  friend class BinaryTree<Data>;

  /* ********************************************************************** */

  // Destructor
  virtual ~Node() = default;

  /* ********************************************************************** */

  // Copy assignment
  Node& operator=(const Node& ) = delete;

  // Move assignment
  Node& operator=(Node&& ) noexcept = delete;

  /* ********************************************************************** */

  // Specific member functions

  virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

  virtual bool IsLeaf() const noexcept = 0; // (concrete function should not throw exceptions)
  virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
  virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

  virtual const Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
  virtual const Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };


  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree& operator=(const BinaryTree&) = delete;

  // Move assignment
  BinaryTree& operator=(BinaryTree&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BinaryTree&) const noexcept;
  inline bool operator != (const BinaryTree& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions
  
  virtual const Node& Root() const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  virtual inline void Traverse (TraverseFun fun) const override {return PreOrderTraverse(fun);}; 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  inline void PreOrderTraverse (TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  inline void PostOrderTraverse (TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)
  inline void InOrderTraverse (TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  inline void BreadthTraverse (TraverseFun) const override;

protected:

  // Auxiliary functions, if necessary!
  void PreOrderTraverseRico(TraverseFun, const Node& ) const;
  void PostOrderTraverseRico(TraverseFun, const Node& ) const;
  void InOrderTraverseRico(TraverseFun, const Node& ) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,
  virtual public BinaryTree<Data>,
  virtual public PreOrderMappableContainer<Data>,
  virtual public PostOrderMappableContainer<Data>,
  virtual public InOrderMappableContainer<Data>,
  virtual public BreadthMappableContainer<Data> {
  

private:

protected:

public:

struct MutableNode :  public virtual BinaryTree<Data>:: Node {

  friend class MutableBinaryTree<Data>;

  /* ********************************************************************** */

  // Destructor
  virtual ~MutableNode() = default;

  /* ********************************************************************** */

  // Copy assignment
  MutableNode& operator=(const MutableNode&) = delete;

  // Move assignment
  MutableNode& operator=(MutableNode&&) noexcept = delete;

  /* ********************************************************************** */

  // Specific member functions
  using BinaryTree<Data>::Node::Element;
  virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

  using BinaryTree<Data>::Node::LeftChild;
  virtual MutableNode& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  using BinaryTree<Data>::Node::RightChild;
  virtual MutableNode& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  //Copy assignment
  MutableBinaryTree& operator = (const MutableBinaryTree&) = delete;

  // Move assignment
  MutableBinaryTree& operator = (MutableBinaryTree&&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  using BinaryTree<Data>::Root;
  virtual MutableNode& Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;
  inline void Map(MapFun) override; 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  virtual void PreOrderMap(MapFun) override; 

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  virtual void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)
  virtual void InOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  virtual void BreadthMap(MapFun) override;

protected:

  // Auxiliary functions, if necessary!
  void PreOrderMapRico(MapFun, MutableNode& );
  void PostOrderMapRico(MapFun, MutableNode& );
  void InOrderMapRico(MapFun, MutableNode& );
  
};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  const typename BinaryTree<Data>::Node* current = nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator& );

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator&);

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTPreOrderIterator& ) const noexcept;
  inline bool operator != (const BTPreOrderIterator& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override;

  bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTPreOrderIterator<Data>& operator++() override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTPreOrderIterator<Data> {

private:

protected:

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data>& other): BTPreOrderIterator<Data>(other) {;};

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator& other): BTPreOrderIterator<Data>(other) {;};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator&& other) noexcept: BTPreOrderIterator<Data>(std::move(other)) {;};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator = (const BTPreOrderMutableIterator& );

  // Move assignment
  BTPreOrderMutableIterator& operator = (BTPreOrderMutableIterator&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTPreOrderMutableIterator& other) const noexcept;
  bool operator != (const BTPreOrderMutableIterator& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  const typename BinaryTree<Data>::Node* current = nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stack;

  const typename BinaryTree<Data>::Node *FirstLeftLeaf(const typename BinaryTree<Data>::Node *);


public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&); 

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator& );

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator = (const BTPostOrderIterator& );

  // Move assignment
  BTPostOrderIterator& operator = (BTPostOrderIterator&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTPostOrderIterator& other) const noexcept;
  inline bool operator != (const BTPostOrderIterator& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)


  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTPostOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override; // (should not throw exceptions)


};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTPostOrderIterator<Data> {

private:

protected:

  using BTPostOrderIterator<Data>::current;

public:

  // Specific constructors
  BTPostOrderMutableIterator(const MutableBinaryTree<Data>& other) : BTPostOrderIterator<Data>(other) {;}; 
  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator& other): BTPostOrderIterator<Data>(other) {;};

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator&& other) noexcept : BTPostOrderIterator<Data>(std::move(other)) {;};

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator& operator = (const BTPostOrderMutableIterator& );

  // Move assignment
  BTPostOrderMutableIterator& operator = (BTPostOrderMutableIterator&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTPostOrderMutableIterator& other) const noexcept;
  inline bool operator != (const BTPostOrderMutableIterator& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:
  
    const typename BinaryTree<Data>::Node* root = nullptr;
    const typename BinaryTree<Data>::Node* current = nullptr;
    StackVec<const typename BinaryTree<Data>::Node*> stack; 

    const typename BinaryTree<Data>::Node* MostLeftNode(const typename BinaryTree<Data>::Node* );

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&);  // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator& );

  // Move constructor
  BTInOrderIterator(BTInOrderIterator&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator = (const BTInOrderIterator& );

  // Move assignment
  BTInOrderIterator& operator = (BTInOrderIterator&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTInOrderIterator& other) const noexcept;
  inline bool operator != (const BTInOrderIterator& other) const noexcept {return !operator==(other);};

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTInOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override; // (should not throw exceptions)



};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTInOrderIterator<Data>{

private:

protected:

public:

  // Specific constructors
  BTInOrderMutableIterator(const MutableBinaryTree<Data>& other) : BTInOrderIterator<Data>(other) {};

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator& other): BTInOrderIterator<Data>(other) {};

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator&& other) noexcept: BTInOrderIterator<Data>(std::move(other)) {};

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator& operator = (const BTInOrderMutableIterator& );

  // Move assignment
  BTInOrderMutableIterator& operator = (BTInOrderMutableIterator&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTInOrderMutableIterator& other) const noexcept;
  inline bool operator != (const BTInOrderMutableIterator& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
  virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  const typename BinaryTree<Data>::Node* current = nullptr;
  QueueVec<const typename BinaryTree<Data>::Node*> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&);  // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator& );

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator& operator = (const BTBreadthIterator& );

  // Move assignment
  BTBreadthIterator& operator = (BTBreadthIterator&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTBreadthIterator& other) const noexcept;
  inline bool operator != (const BTBreadthIterator& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTBreadthIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
  virtual public BTBreadthIterator<Data> {

private:

protected:

public:

  // Specific constructors
  BTBreadthMutableIterator(const MutableBinaryTree<Data>& other): BTBreadthIterator<Data>(other) {};

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator& other) : BTBreadthIterator<Data>(other) {};

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator&& other) noexcept : BTBreadthIterator<Data>(std::move(other)) {};

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator& operator = (const BTBreadthMutableIterator& );

  // Move assignment
  BTBreadthMutableIterator& operator = (BTBreadthMutableIterator&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTBreadthMutableIterator& other) const noexcept;
  inline bool operator != (const BTBreadthMutableIterator& other) const noexcept {return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
