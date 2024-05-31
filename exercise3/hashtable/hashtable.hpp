
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  ulong operator()(const Data& element) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>, 
  virtual public ResizableContainer {

private:

protected:

  using DictionaryContainer<Data>::size;

  ulong a;
  ulong b;
  ulong nPrimo = 1229; 
  ulong tableSize = 16;

  //Generatore di numeri casuali per inizializzare i coefficienti a e b
  std::default_random_engine genera = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<ulong> genA = std::uniform_int_distribution<ulong>(1, nPrimo - 1);  
  std::uniform_int_distribution<ulong> genB = std::uniform_int_distribution<ulong>(0, nPrimo - 1);

  //Default constructor
  HashTable();

  //Copy constructor
  HashTable(const HashTable&);

  //Move constructor
  HashTable(HashTable&&) noexcept;


public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator = (const HashTable&); // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator = (HashTable&&) noexcept; // Move assignment of abstract types should not be possible.
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const HashTable& other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator != (const HashTable& other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  ulong HashKey(ulong ) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
