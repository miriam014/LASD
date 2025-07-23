#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer,
  virtual public LinearContainer<Data>,
  virtual public DictionaryContainer<Data> {

private:

protected:

  using Container::size;

  struct Node {

    Data dato{};
    Node* next = nullptr;
    
    /* ********************************************************************** */

    Node() = default; // Default constructor

    // Specific constructors
    Node(const Data& );

    Node(Data&& ) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node& );

    // Move constructor
    Node(Node&& ) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    inline bool operator == (const Node& other);
    inline bool operator != (const Node& other) { return !(operator == (other)); }

    /* ********************************************************************** */

    // Specific member functions

    //...

  };

  Node* testa = nullptr;
  Node* coda = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data>& );  // A list obtained from a TraversableContainer
  List(MappableContainer<Data>&& ); // A list obtained from a MappableContainer


  /* ************************************************************************ */

  // Copy constructor
  List(const List& );

  // Move constructor
  List(List&& );

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  inline List& operator = (const List& );

  // Move assignment
  inline List& operator = (List&& );

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const List& other) const noexcept;
  inline bool operator != (const List& other) const noexcept { return !(*this == other); };

  /* ************************************************************************ */

  // Specific member functions
  void InsertAtFront(const Data& ); // Copy of the value
  void InsertAtFront(Data&& ); // Move of the value

  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data& ); // Copy of the value
  void InsertAtBack(Data&& ); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; 

  using TraversableContainer<Data>::Exists;
  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data& dato) override; // Copy of the value 
  bool Insert(Data&& dato) noexcept override;  // Move of the value
  bool Remove(const Data& dato) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
  inline const Data & operator[](ulong ) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  inline Data& operator[](ulong ) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  inline const Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  inline const Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override;
  
  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;
  inline void Map(MapFun)  override; 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun)  override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun)  override;

protected:

  // Auxiliary member functions (for PreOrderTraversableContainer & PostOrderTraversabeContainer)
  
  void PreOrderTraverse(TraverseFun, Node* ) const;
  void PostOrderTraverse(TraverseFun, Node* ) const;
  void PreOrderMap(MapFun, Node* ) ;
  void PostOrderMap(MapFun, Node* ) ;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
