
namespace lasd {

/* ************************************************************************** */
// Specific constructors
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data>& cont) {
  cont.Traverse(    //chiamo il metodo Traverse del container passato come parametro e itero su tutti i suoi elementi
    [this](const Data& data){
      Insert(data);
    }
  );
}

template <typename Data>
BST<Data>::BST(MappableContainer<Data>&& cont) noexcept {
  cont.Map([this](Data& data){
    Insert(std::move(data));
  });
}

/* ************************************** */
// Copy constructor
template <typename Data>
BST<Data>::BST(const BST& other) : BinaryTreeLnk<Data>::BinaryTreeLnk(other){}

// Move constructor
template <typename Data>
BST<Data>::BST(BST&& other) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(other)){}

/* ************************************** */
// Copy assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST& other) {
  if(this != &other){
    Clear();
    other.PreOrderTraverse([this](const Data & data){
        Insert(data);
    });
  }
  return *this;
}

// Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST && other) noexcept {
  if(this != &other){
    Clear();
    other.PreOrderTraverse([this](const Data & data){
        Insert(std::move(data));
    });

    other.Clear();
  }
  return *this;
}

/* *************************************** */
// Comparison operator
template <typename Data>
bool BST<Data>::operator == (const BST & other) const noexcept{
  if(Size() != other.Size())
    return false;

  bool equal = true;
  this->PreOrderTraverse([&other, &equal](const Data & data){
    if(!other.Exists(data)){
      equal = false;
      return;
    }
  });

  return equal;
}

/* ************************************************************************** */
//Specific member functions 
template <typename Data>
const Data &BST<Data>::Min() const {
  if (root != nullptr) 
    return FindPointerToMin(root)->element;
    
  throw std::length_error("Access to an empty BST.");
    
  }

  template <typename Data>
  Data BST<Data>::MinNRemove() {
    if (root != nullptr) 
      return DataNDelete(DetachMin(root));

    else throw std::length_error("Access to an empty BST.");
  }


  template <typename Data>
  void BST<Data>::RemoveMin() {
    if (root != nullptr) {
      delete DetachMin(root);
      --size;
    } else {
      throw std::length_error("Access to an empty BST.");
    }
  }

  /* ************************************** */

  template <typename Data>
  const Data &BST<Data>::Max() const {
    if (root != nullptr) 
    return FindPointerToMax(root)->element;

    throw std::length_error("Access to an empty BST.");
  }


  template <typename Data>
  Data BST<Data>::MaxNRemove() {
    if (root != nullptr) 
      return DataNDelete(DetachMax(root));
    
    throw std::length_error("Access to an empty BST.");
    
  }

  template<typename Data>
  void BST<Data>::RemoveMax() {
    if (root != nullptr) {
    delete DetachMax(root);
    --size;
    } else {
    throw std::length_error("Access to an empty BST.");
    }
  }


/* ************************************** */

template <typename Data>
const Data &BST<Data>::Predecessor(const Data &dat) const {
  typename BST<Data>::NodeLnk* tmp = FindPointerToPredecessor(root, dat);
  if (tmp != nullptr) {
    return tmp->element;
  } else {
      throw std::length_error(" Predecessor not found");
  }
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data &dat) {
  NodeLnk* tmp = FindPointerToPredecessor(root, dat);
  if (tmp != nullptr) {
    Data pre = tmp->element;
    Remove(tmp->element);
    return pre;
  } else {
    throw std::length_error(" Predecessor not found");
  }
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data &dat) {
  typename BST<Data>::NodeLnk** puntatore =& FindPointerToPredecessor(root, dat);
  if (puntatore != nullptr) {
      delete Detach(*puntatore);
      --size;
  } else {
      throw std::length_error(" Predecessor not found");
  }
}

/* ************************************** */

template <typename Data>
const Data &BST<Data>::Successor(const Data &dat) const {
  NodeLnk* const* tmp =& FindPointerToSuccessor(root, dat);
  if(tmp !=nullptr)
      return (*tmp)->element;
  
    throw std::length_error(" Successor not found");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data &dat) {
  NodeLnk** tmp =& FindPointerToSuccessor(root, dat);
  if (tmp != nullptr) 
      return DataNDelete(Detach(*tmp));

   throw std::length_error(" Successor not found");
  
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data &dat) {
    NodeLnk **tmp =& FindPointerToSuccessor(root, dat);
    if (tmp != nullptr) {
      delete Detach(*tmp);
      --size;
    }else{
      throw std::length_error(" Successor not found");
    }  
}

/* ******************************************************** */
// Specific member function (inherited from BinaryTree)
template <typename Data>
const typename BST<Data>::NodeLnk& BST<Data>::Root() const {
    if (root != nullptr)
      return *root;

    throw std::length_error(" BST is Empty.");
    
}

/* ************************************** */
// Specific member functions (inherited from DictionaryContainer)

//insert copy
template <typename Data>
bool BST<Data>::Insert(const Data &dat) {
  NodeLnk *& tmp = FindPointerTo(root, dat); 
  if(tmp == nullptr){
    tmp = new NodeLnk(dat);
    size++;
    return true;
  }
  return false;
}

//insert move
template <typename Data>
bool BST<Data>::Insert(Data &&dat) noexcept{
  NodeLnk *& tmp = FindPointerTo(root, dat); 
  if(tmp == nullptr){
    tmp = new NodeLnk(std::move(dat));
    ++size;
    return true;
  }
  return false;
}

template <typename Data>
bool BST<Data>::Remove(const Data &dat){
  NodeLnk *& tmp = FindPointerTo(root, dat);
  if(tmp != nullptr){
    delete Detach(tmp);
    --size;
    return true;
  }
  return false;
}

/* ************************************** */
// Specific member functions (inherited from TestableContainer)
template <typename Data>
inline bool BST<Data>::Exists(const Data &dat) const noexcept {
  return (FindPointerTo(root,dat) !=nullptr);
}

/* ************************************** */
// Specific member function (inherited from ClearableContainer)
template <typename Data>
inline void BST<Data>::Clear() {
  BinaryTreeLnk<Data>::Clear();
}

/* ******************************************************************************** */
// Auxiliary functions

//DataNDelete
template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node) {
  Data tmp = std::move(node->element);
  delete node;
  --size;
  return tmp;
}

//Detach
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
  if (node != nullptr) {
    if (node->HasLeftChild() && node->HasRightChild()) {
      NodeLnk* tmp = DetachMin(node->right);
      std::swap(tmp->element, node->element);
      return tmp;
    }
    else if (node->HasLeftChild()) {
      return Skip2Left(node);
    }
    else if (node->HasRightChild()) {
      return Skip2Right(node);
    }
    else {
      NodeLnk* tmp = node;
      node = nullptr;
      return tmp;
    }
  }
  else 
    return nullptr;

}

/* ************************************************************************** */


//DetachMin
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& pt) noexcept{
  return Skip2Right(FindPointerToMin(pt));
}

//DetachMax
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& pt) noexcept{
  return Skip2Left(FindPointerToMax(pt));
}


/* ************************************************************************ */

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk *&node) noexcept {
  NodeLnk* skipLeft = nullptr;
  if(node!=nullptr){
    std::swap(skipLeft, node->left);
    std::swap(skipLeft, node);
  }
  return skipLeft;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk *&node) noexcept {
  NodeLnk* skipRight = nullptr;
  if(node!=nullptr){
    std::swap(skipRight, node->right);
    std::swap(skipRight, node);
  }
  return skipRight;
}

/* ************************************************* */

//FindPointerTo
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& pt, const Data& dat) const noexcept{
  if(pt!=nullptr && pt->element<dat)
    return FindPointerTo(pt->right, dat);
  else if(pt!=nullptr && pt->element>dat)
    return FindPointerTo(pt->left, dat);
  else
    return pt;
}


template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& pt, const Data& dat) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(pt, dat));
}

/* ************************************************* */

//FindPointerToMin
template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& pt) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(pt));
}


template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& pt) const noexcept{
  if(pt==nullptr || !pt->HasLeftChild())
    return pt;
  else
  return FindPointerToMin(pt->left);
}

/* ************************************************* */

//FindPointerToMax
template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& pt) noexcept{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(pt));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& pt) const noexcept{
  if(pt==nullptr || !pt->HasRightChild())
    return pt;
  else
  return FindPointerToMax(pt->right);
}

/* ************************************************* */

//FindPointerToPredecessor
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk * const& node, const Data &dato) const noexcept {

  NodeLnk* const* candidate = nullptr;
  NodeLnk* const* current = &node;
  
  while(*current!=nullptr && (*current)->element!=dato) {
    if((*current)->element < dato) {
      candidate = current;
      current = &((*current)->right);
    }else if((*current)->element > dato)
      current = &((*current)->left);
  }

  if(*current!=nullptr && (*current)->HasLeftChild())
    return FindPointerToMax((*current)->left);
  
  return *candidate;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk*& node, const Data &dato) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, dato));
}

/* ************************************************* */

//FindPointerToSuccessor

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk * const&node, const Data &dato) const noexcept {
    
  NodeLnk* const* candidate = nullptr;
  NodeLnk* const* current = &node;
  
  while(*current!=nullptr && (*current)->element!=dato) {
    if((*current)->element < dato)
        current = &((*current)->right);
    else if((*current)->element > dato){
      candidate = current;
      current = &((*current)->left);
    }
  }

  if(*current!=nullptr && (*current)->HasRightChild())
    return FindPointerToMin((*current)->right);
  
  return *candidate; 
}


template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk*& node, const Data &dato) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, dato));
}

/* ************************************************************************** */

}