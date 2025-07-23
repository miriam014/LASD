#include "linear.hpp"

namespace lasd {

/* ************************************************************************** */

//comparison operators
template<typename Data> 
bool LinearContainer<Data>::operator == (const LinearContainer<Data> &cont) const noexcept {
  if (size != cont.size) {
    return false;
  }

  for (ulong i = 0; i < size; ++i) {
    if (operator[](i) != cont[i])
        return false;
  }
  return true;
}

/* ************************************************************************** */

// Specific member functions (Linear Container)
template<typename Data>
const Data& LinearContainer<Data>::Front() const {
    if (size == 0) {
    throw std::length_error("Empty structure.");
    }
    return operator[](0);
}

template<typename Data>
Data& LinearContainer<Data>::Front() {
    if (size != 0) {
    throw std::length_error("Empty structure.");
    }
    return operator[](0);
}

template<typename Data>
const Data& LinearContainer<Data>::Back() const {
    if (size == 0) {
    throw std::length_error("Empty structure.");
    }
    return operator[](size-1);
}

template<typename Data>
Data& LinearContainer<Data>::Back() {
    if (size == 0) {
    throw std::length_error("Empty structure.");
    }
    return operator[](size-1);
}

/* ************************************************************************** */

// Specific member function (inherited from TraversableContainer)
template<typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}


/* ************************************************************************** */

// Specific member function (inherited from PreOrderTraversableContainer)
template<typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
    for (ulong i = 0; i < size; ++i){
        fun(operator[](i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderTraversableContainer)
template<typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
    ulong i = size;
    while (i > 0){
        fun(operator[](--i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from MappableContainer)
template<typename Data>
void LinearContainer<Data>::Map(MapFun fun)  {
    PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderMappableContainer)
template<typename Data>
void LinearContainer<Data>::PreOrderMap(MapFun fun)  {
    for (ulong i=0; i < size; ++i){
        fun(operator[](i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderMappableContainer)
template<typename Data>
void LinearContainer<Data>::PostOrderMap(MapFun fun)  {
    ulong i = size;
    while (i > 0){
        fun(operator[](--i));
    }
}

/* ************************************************************************** */

//Comparison operators (SortableLinearContainer)
template <typename Data>
inline bool SortableLinearContainer<Data>::operator==(const SortableLinearContainer<Data> &other) const noexcept {
  return LinearContainer<Data>::operator==(other);
}


//Specific member functions (SortableLinearContainer)
template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
    if(size > 1)
        QuickSort(0, size-1);
}
 

// Auxiliary member functions
template<typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong first, ulong last) noexcept {
    if(first < last){
        ulong med = Partition(first, last);
        QuickSort(first, med);
        QuickSort(med+1, last);
    }
}

 
template<typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong first, ulong last) noexcept {
    Data pivot = this->operator[](first);
    ulong i = first-1;
    ulong j = last+1;
    do{
        do{
            j--;
        }while(pivot < this->operator[](j));

        do{
            i++;
        }while(pivot > this->operator[](i));

        if(i < j){
           std::swap(this->operator[](i), this->operator[](j));
        }
    }while(i < j);
    return j;
}


/* ************************************************************************** */

}
