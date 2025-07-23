namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>::Vector(starting_size_qeq){}

  /* ************************************************************************** */

// Specific constructor
template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data> &con)
    : Vector<Data>::Vector(con), coda(con.Size()), N_ele(con.Size()) {
  if (size < starting_size_qeq)
    Resize(starting_size_qeq);
}

template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data> &&con) noexcept
    : Vector<Data>::Vector(std::move(con)), coda(con.Size()),
      N_ele(con.Size()) {
  if (size < starting_size_qeq)
    Resize(starting_size_qeq);
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data> &qeq) : Vector<Data>::Vector(qeq) {
  testa = qeq.testa;
  coda = qeq.coda;
  N_ele = qeq.N_ele;
}

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data> &&qeq) noexcept : Vector<Data>::Vector(std::move(qeq)) {
  std::swap(testa, qeq.testa);
  std::swap(coda, qeq.coda);
  std::swap(N_ele, qeq.N_ele);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
inline QueueVec<Data> &QueueVec<Data>::operator=(const QueueVec<Data> &qeq) {
  Vector<Data>::operator=(qeq);
  testa = qeq.testa;
  coda = qeq.coda;
  N_ele = qeq.N_ele;
  return *this;
}

// Move assignment
template <typename Data>
inline QueueVec<Data> &QueueVec<Data>::operator=(QueueVec<Data> &&qeq) noexcept {
  Vector<Data>::operator=(std::move(qeq));
  std::swap(testa, qeq.testa);
  std::swap(coda, qeq.coda);
  std::swap(N_ele, qeq.N_ele);
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
inline bool QueueVec<Data>::operator==(const QueueVec<Data> &qeq) const noexcept {
  if (qeq.N_ele != N_ele)
    return false;

  for (ulong i=0; i < N_ele; i++){
    if (Vett[(testa + i) % size] != qeq[(qeq.testa + i) % qeq.size])
      return false;
  }
  return true;
}


template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data> &qeq) const noexcept {
  return !(*this == qeq);
}

/* ************************************************************************** */

// Specific member functions (inherited from Queue) OVERRIDE

template <typename Data> 
inline const Data &QueueVec<Data>::Head() const {
  if (Empty())
    throw std::length_error("The queueVec is empty");

  return Vett[testa];
}

template <typename Data> 
inline Data &QueueVec<Data>::Head() {
  if (Empty())
    throw std::length_error("The queueVec is empty");
  
  return Vett[testa];
}


template <typename Data> 
inline void QueueVec<Data>::Dequeue() {
  if (Empty())
    throw std::length_error("The queueVec is empty");

  testa = (testa + 1) % size;

  if (--N_ele == (size / REDUCE_4))
    Resize(size / REDUCE_2);
}

template <typename Data> 
inline Data QueueVec<Data>::HeadNDequeue() {
  Data testatmp = Head();
  Dequeue();
  return testatmp;
}


template <typename Data> 
void QueueVec<Data>::Enqueue(const Data& val) {
  if (N_ele == size)
    Resize(size * INCREASE_2);

  Vett[coda] = val;
  coda = (coda + 1) % size;
  ++N_ele;
}

template <typename Data> 
void QueueVec<Data>::Enqueue(Data&& val) {
  if (N_ele == size)
    Resize(size * INCREASE_2);

  Vett[coda] = std::move(val);
  coda = (coda + 1) % size;
  ++N_ele;
}

/* ************************************************************************** */

// Specific member functions (inherited from Container) OVERRIDE


template <typename Data> 
inline bool QueueVec<Data>::Empty() const noexcept {
  return N_ele == 0;
}

template <typename Data>
inline ulong QueueVec<Data>::Size() const noexcept {
  return N_ele; 
}


/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer) OVERRIDE

template <typename Data> 
inline void QueueVec<Data>::Clear() {
  Resize(starting_size_qeq);
  testa = 0;
  coda = 0;
  N_ele = 0;
}

template <typename Data> 
void QueueVec<Data>::Resize(const ulong ssq) {
  if ((ssq < starting_size_qeq) || (ssq == size))
    return;

  Data *tmp = new Data[ssq]{};
  for (ulong i=testa, j=0; j < N_ele; ++j){
    tmp[j] = Vett[i];
    i = (i+1)%size;
  }

  std::swap(Vett, tmp);
  delete[] tmp;

  testa = 0;
  coda = N_ele;
  size = ssq;
}

/* ************************************************************************** */

}
