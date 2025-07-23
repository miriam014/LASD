
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */
//in caso di collisioni vengono tentate posizioni alternative finchè non si trova una posizione libera, esiste qui il concetto di conatenazione 
template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

private:

  enum Flag {empt, dirty, full};

protected:

  using DictionaryContainer<Data>::size;
  using HashTable<Data>::tableSize;
  using HashTable<Data>::HashKey;

  Data* table = nullptr;
  Flag* tableFlag = nullptr;

public:

  using DictionaryContainer<Data>::InsertAll;

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong size); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data>& other); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(const ulong size, const TraversableContainer<Data>& other); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data>&& other); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const ulong size, MappableContainer<Data>&& other); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data>& );

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data>&& ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr();

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr& );

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const HashTableOpnAdr& other) const noexcept;
  inline bool operator != (const HashTableOpnAdr& other) const noexcept { return !operator ==(other);};

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


protected:

  // Auxiliary member functions

  ulong HashKey(const Data& key, ulong& prob_index) const noexcept;
  bool Find(ulong& index, ulong& x, const Data& element) const noexcept;
  ulong FindEmpty(const Data& element, ulong& x) const noexcept;
  bool Remove(ulong& x, const Data& key) noexcept;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
