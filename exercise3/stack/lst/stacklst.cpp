
namespace lasd {

/* ************************************************************************** */

//Specific constructor (StackLst)
template <typename Data>
StackLst<Data>::StackLst(const TraversableContainer<Data> &cont) : List<Data>::List(cont) {}

template <typename Data>
StackLst<Data>::StackLst(MappableContainer<Data> &&cont) :List<Data>::List(std::move(cont)) {}

/* ************************************************************************** */

//Copy constructor (StackLst)
template <typename Data>
inline StackLst<Data>::StackLst(const StackLst<Data> &cont) : List<Data>::List(cont) {}

// Move constructor (StackLst)
template <typename Data>
inline StackLst<Data>::StackLst(StackLst<Data> &&cont) noexcept : List<Data>::List(std::move(cont)) {}


/* ************************************************************************** */

//Copy assignment (StackLst)
template <typename Data>
StackLst<Data>& StackLst<Data>::operator = (const StackLst& stkl){
  List<Data>::operator=(stkl);
  return *this;
}

//Move assignment (StackLst)
template <typename Data>
StackLst<Data>& StackLst<Data>::operator = (StackLst&& stkl) noexcept{
  List<Data>::operator=(std::move(stkl));
  return *this;
}

/* ************************************************************************** */

// Specific member functions OVERRIDE (Stack)

template <typename Data>
const Data& StackLst<Data>::Top() const{
  if(!size)
    throw std::length_error("Empty stack");

  return List<Data>::Front();
}

template <typename Data>
Data& StackLst<Data>::Top(){
  if(!size)
    throw std::length_error("Empty stack");
  
  return List<Data>::Front();
}


template <typename Data>
void StackLst<Data>::Pop(){
  if(List<Data>::size == 0)
    throw std::length_error("Empty stack");
  
  List<Data>::RemoveFromFront();
}

template <typename Data>
Data StackLst<Data>::TopNPop(){
  if(List<Data>::size == 0)
    throw std::length_error("Empty stack");
  
  return List<Data>::FrontNRemove();
}


template <typename Data>
void StackLst<Data>::Push(const Data& val){
  List<Data>::InsertAtFront(val);
}

template <typename Data>   
void StackLst<Data>::Push(Data&& val){
  List<Data>::InsertAtFront(std::move(val));
}

/* ************************************************************************** */

}
