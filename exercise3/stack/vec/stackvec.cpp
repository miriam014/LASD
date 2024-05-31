namespace lasd {

/* ************************************************************************** */

//Costructor
template <typename Data> 
StackVec<Data>::StackVec(): Vector<Data>::Vector(starting_size_vec){}

/* ************************************************************************** */

// Specific constructor   

template <typename Data> 
StackVec<Data>::StackVec(const TraversableContainer<Data>& cont) : Vector<Data>::Vector(cont) {
  n_elem = cont.Size();
  if (size == starting_size_vec)
      Resize((ulong)size*INCREASE_2);
}

template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data>&& cont) : Vector<Data>::Vector(std::move(cont)) {
  n_elem = cont.Size();
  if (size == starting_size_vec)
      Resize((ulong)size*INCREASE_2);
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec& stkv): Vector<Data>::Vector(stkv), n_elem(stkv.n_elem) {}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec&& stkv) noexcept : Vector<Data>(std::move(stkv)){
  std::swap(stkv.n_elem, n_elem);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stkv) {
  Vector<Data>::operator=(stkv);
  n_elem = stkv.n_elem;
  return *this;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stkv) noexcept {
  Vector<Data>::operator=(std::move(stkv));
  std::swap(n_elem, stkv.n_elem);
  return *this;
}


/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool StackVec<Data>::operator == (const StackVec& stkv) const noexcept {
  if(n_elem != stkv.n_elem) //se le dimensioni sono diverse ritorna false
    return false;

  for(ulong i = 0; i < n_elem; i++){  //scorre i due stack e confronta i dati
    if(Vett[i] != stkv.Vett[i]) //se anche un solo dato è diverso ritorna false
      return false;
  }
  return true;
}


template <typename Data>
bool StackVec<Data>::operator != (const StackVec& stkv) const noexcept {
  return !(*this == stkv);
}

/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template <typename Data>
const Data& StackVec<Data>::Top() const{
  if(n_elem == 0)
    throw std::length_error("Empty stack");

  return Vett[n_elem - 1];
}

template <typename Data>
Data& StackVec<Data>::Top() {
  if(n_elem == 0)
    throw std::length_error("Empty stack");

  return Vett[n_elem - 1];
}


template <typename Data>
void StackVec<Data>::Pop(){
  if(n_elem == 0)
    throw std::length_error("Empty stack");

  if(--n_elem < size / REDUCE_4)
    Resize(size / REDUCE_2);
}

template <typename Data>
Data StackVec<Data>::TopNPop(){
  Data TopElm{Top()};
  Pop();
  return TopElm;
}

template <typename Data>
void StackVec<Data>::Push(const Data& val){
  if(n_elem == size)
    Resize(size * INCREASE_2);
  
  Vett[n_elem] = val;
  n_elem++;
}

template <typename Data>
void StackVec<Data>::Push(Data&& val){
  if(n_elem == size)
    Resize(size * INCREASE_2);
  
  Vett[n_elem] = std::move(val);
  n_elem++;
}


/* ************************************************************************** */

//Specific member functions (inherited from ClearableContainer)
template <typename Data>
void StackVec<Data>::Clear(){
  Resize(starting_size_vec);
  n_elem = 0;
}


template <typename Data>
void StackVec<Data>::Resize(const ulong siz){
  if (siz >= n_elem)
    Vector<Data>::Resize(siz);
}

/* ************************************************************************** */

}
