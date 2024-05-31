
namespace lasd {

/* ************************************************************************** */

// Specific constructor

template <typename Data>
QueueLst<Data>::QueueLst(const TraversableContainer<Data> &qeq): List<Data>::List(qeq) {}


template <typename Data>
QueueLst<Data>::QueueLst(MappableContainer<Data> &&qeq) noexcept : List<Data>::List(std::move(qeq)) {}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data> &qeq) : List<Data>::List(qeq) {}

// Move constructor
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data> &&qeq) noexcept : List<Data>::List(std::move(qeq)) {}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
inline QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &qeq) {
  List<Data>::operator=(qeq);
  return *this;
}

// Move assignment
template <typename Data>
inline QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&qeq) noexcept {
  List<Data>::operator=(std::move(qeq));
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
inline bool QueueLst<Data>::operator==(const QueueLst<Data> &qeq) const noexcept {
  return List<Data>::operator==(qeq);
}

template <typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data> &qeq) const noexcept {
  return !(*this == qeq);
}

/* ************************************************************************** */

// Overrided Methods

template <typename Data> 
inline Data &QueueLst<Data>::Head() {
  if (!size)
    throw std::length_error("The queue is empty");

  return List<Data>::Front();
}

template <typename Data> 
inline const Data &QueueLst<Data>::Head() const {
  if (!size)
    throw std::length_error("The queue is empty");

  return List<Data>::Front();
}

template <typename Data> 
inline void QueueLst<Data>::Dequeue() {
  if (!size)
    throw std::length_error("The queue is empty");

  return List<Data>::RemoveFromFront();
}

template <typename Data> 
inline Data QueueLst<Data>::HeadNDequeue() {
  if (!size)
    throw std::length_error("The queue is empty");

  return List<Data>::FrontNRemove();
}

template <typename Data> 
inline void QueueLst<Data>::Enqueue(const Data &dat) {
  return List<Data>::InsertAtBack(dat);
}

template <typename Data> 
inline void QueueLst<Data>::Enqueue(Data &&dat) {
  return List<Data>::InsertAtBack(std::move(dat));
}

/* ************************************************************************** */

}
