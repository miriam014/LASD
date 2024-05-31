
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data>{

private:

protected:

  using DictionaryContainer<Data>::size;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::tableSize;
  lasd::List<Data>* table = nullptr;

public:
  
  using DictionaryContainer<Data>::InsertAll;

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const ulong new_size); // A hash table of a given size
  HashTableClsAdr(const TraversableContainer<Data>& other); // A hash table obtained from a TraversableContainer
  HashTableClsAdr(const ulong new_size, const TraversableContainer<Data>& other); // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(MappableContainer<Data>&& other); // A hash table obtained from a MappableContainer
  HashTableClsAdr(const ulong new_size, MappableContainer<Data>&& other); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data>& );

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data>&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  inline ~HashTableClsAdr() {
    delete[] table;
  };

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr& );

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr&& ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr& other) const noexcept;
  bool operator!=(const HashTableClsAdr& other) const noexcept { return !(operator==(other));};
  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data& ) override; // (Copy of the value)
  bool Insert(Data&& ) noexcept override; // (Move of the value)
  bool Remove(const Data& ) override; 
  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data& ) const noexcept override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)
  void Resize(const ulong ) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  void Clear() override;

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
