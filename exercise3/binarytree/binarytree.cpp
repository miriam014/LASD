#include "binarytree.hpp"
#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
//    BINARYTREE
// Comparison operators
template <typename Data>
bool BinaryTree<Data>::operator == (const BinaryTree &other) const noexcept {
    if(size != other.size) {  //se i due alberi hanno dimensioni diverse sicuramente non sono uguali
        return false;
    }
    BTPreOrderIterator i(*this);
    BTPreOrderIterator j(other);
    while(!(i.Terminated()) && !(j.Terminated())){
        if((*i)!=(*j)) {
            return false;
        }
        ++i;
        ++j;
    }
    return true;
}


/* ****************************************************************** */
// Specific member function (inherited from PreOrderTraversableContainer)
template <typename Data>
inline void BinaryTree<Data>::PreOrderTraverse (TraverseFun fun) const {
    if(!this->Empty()) {
        PreOrderTraverseRico(fun, Root());
    }
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverseRico(TraverseFun fun, const Node& node) const {

    fun(node.Element());
    if(node.HasLeftChild()) {
        PreOrderTraverseRico(fun, node.LeftChild());
    }
    if(node.HasRightChild()) {
        PreOrderTraverseRico(fun, node.RightChild());
    }
}

/* ****************************************************************** */
// Specific member function (inherited from PostOrderTraversableContainer)
template <typename Data>
void BinaryTree<Data>::PostOrderTraverse (TraverseFun fun) const {
    if(!this->Empty()) {
        PostOrderTraverseRico(fun, Root());
    }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverseRico(TraverseFun fun, const Node& node) const {

    if(node.HasLeftChild()) {
        PostOrderTraverseRico(fun, node.LeftChild());
    }
    if(node.HasRightChild()) {
        PostOrderTraverseRico(fun, node.RightChild());
    }
    fun(node.Element());
}

/* ******************************************************************* */
// Specific member function (inherited from InOrderTraversableContainer)
template <typename Data>  
inline void BinaryTree<Data>::InOrderTraverse (TraverseFun fun) const {
    if(!this->Empty()) {
        InOrderTraverseRico(fun, Root());
    }
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverseRico(TraverseFun fun, const Node& node) const {
    if(node.HasLeftChild()) {
        InOrderTraverseRico(fun, node.LeftChild());
    }
    fun(node.Element());
    if(node.HasRightChild()) {
        InOrderTraverseRico(fun, node.RightChild());
    }
}


/* ******************************************************************* */
// Specific member function (inherited from BreadthTraversableContainer)
template <typename Data>
inline void BinaryTree<Data>::BreadthTraverse (TraverseFun fun) const {
    for(BTBreadthIterator i(*this); !(i.Terminated()); ++i) 
        fun(*i);
}

/* ************************************************************************** */
/* ************************************************************************ */
//      MUTABLE BINARY TREE
// Specific member function (inherited from MappableContainer)
template <typename Data>
void MutableBinaryTree<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}


/* ************************************************************************ */
// Specific member function (inherited from PreOrderMappableContainer)
template <typename Data>
inline void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) {
    if(!Empty()) {
        PreOrderMapRico(fun, Root());
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMapRico(MapFun fun, MutableNode& node) {
    fun(node.Element());
    if(node.HasLeftChild()) {
        PreOrderMapRico(fun, node.LeftChild());
    }
    if(node.HasRightChild()) {
        PreOrderMapRico(fun, node.RightChild());
    }
}

/* ************************************************************************ */
// Specific member function (inherited from PostOrderMappableContainer)
template <typename Data>
inline void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) {
    if(!Empty()) 
        PostOrderMapRico(fun, Root());
}


template <typename Data>
void MutableBinaryTree<Data>::PostOrderMapRico(MapFun fun, MutableNode& node) {
    if(node.HasLeftChild()) {
        PostOrderMapRico(fun, node.LeftChild());
    }
    if(node.HasRightChild()) {
        PostOrderMapRico(fun, node.RightChild());
    }
    fun(node.Element());
}

/* ************************************************************************ */
// Specific member function (inherited from InOrderMappableContainer)
template <typename Data>
inline void MutableBinaryTree<Data>::InOrderMap(MapFun fun) {
    if(!Empty()) {
        InOrderMapRico(fun, Root());
    }
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMapRico(MapFun fun, MutableNode& node) {
    if(node.HasLeftChild()) {
        InOrderMapRico(fun, node.LeftChild());
    }
    fun(node.Element());
    if(node.HasRightChild()) {
        InOrderMapRico(fun, node.RightChild());
    }
}

/* ************************************************************************ */
// Specific member function (inherited from BreadthMappableContainer)
template <typename Data>
inline void MutableBinaryTree<Data>::BreadthMap(MapFun fun) {
    for(BTBreadthMutableIterator i(*this); !(i.Terminated()); ++i) 
        fun(*i);
}


/* ******************************************************************************************** */
/* ******************************************************************************************** */

//      BT PreOrderIterator

// Specific constructors    
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& other) {
    if(!other.Empty()) {
       current = root = &other.Root();
    }
}

/* **************************************************************** */

// Copy constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator &other) {
    root = other.root;
    current = other.current;
}

//Move constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& other) noexcept  {
    std::swap(root, other.root);
    std::swap(current, other.current); 
}

/* *************************************************************** */

// Copy assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& other) {
    root = other.root;
    stack = other.stack;
    current = other.current;
    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& other) noexcept {
    std::swap(root, other.root);
    std::swap(stack, other.stack); 
    std::swap(current, other.current);
    return *this;
}

/* ************************************************************ */

// Comparison operators
template <typename Data>
bool BTPreOrderIterator<Data>::operator == (const BTPreOrderIterator &other) const noexcept {
    return (current==other.current && root==other.root);
}

/* ************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
const Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated()) 
        throw std::out_of_range("Iterator is terminated.");

    return current->Element();
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* *********************************************************** */

// Specific member functions (inherited from ForwardIterator)
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>:: operator++() {
    if(Terminated()) //se l'iteratore non è terminato
        throw std::out_of_range("Out of range iterator");
    
    if(current->HasLeftChild()){
        if(current->HasRightChild()) {
            stack.Push(&current->RightChild());
        }
        current=&(current->LeftChild());
    }else if(current->HasRightChild()) 
        current=&(current->RightChild());
     else if (!stack.Empty())    //se non ha nè figlio destro nè figlio sinistro 
        current=stack.TopNPop();
     else 
        current=nullptr;
    
    return *this;
}

/* ************************************************************ */

// Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
    stack.Clear();
    this->current = root;
}

/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
//      BT  PreOrderMutableIterator
// Copy assignment
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& right) {
    this->root=right.root;
    this->stack=right.stack;
    this->current=right.current;
    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& right) noexcept {
    this->root = std::move(right.root);
    this->stack = std::move(right.stack);
    this->current = std::move(right.current); 
    return *this;
}

/* ************************************************************ */
// Comparison operators
template <typename Data>
inline bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator &other) const noexcept {
    return BTPreOrderIterator<Data>::operator==(other);
}

/* ************************************************************* */
// Specific member functions (inherited from MutableIterator)
template <typename Data>
Data& BTPreOrderMutableIterator<Data>::operator*()  {
    if((this->current) != nullptr) 
        return const_cast<Data&>(this->current->Element());
    
    throw std::out_of_range("Error: Out of range iterator"); 
    
}

/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
//      BT PostOrderIterator
// Specific constructors
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& other){
    if(other.Empty()) {
        root = nullptr;
    } else {
        root = &other.Root();
    }
    current = FirstLeftLeaf(root);
}

/* ********************************************************* */

// Copy constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& other) {
    stack = other.stack;
    root = other.root;
    current=other.current;
}

//Move constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& other) noexcept {
    std::swap(stack, other.stack);
    std::swap(root, other.root); 
    std::swap(current, other.current);
}


/* ********************************************************* */

// Copy assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& other) {
    stack=other.stack;
    root=other.root;
    current=other.current;
    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& other) noexcept {
    std::swap(stack, other.stack); 
    std::swap(root, other.root);
    std::swap(current, other.current);
    return *this;
}

/* ********************************************************* */

// Comparison operators
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator &other) const noexcept {
    return ((current == other.current) && (root == other.root));
}

/* ********************************************************* */

// Specific member functions (inherited from Iterator)

template <typename Data>
const Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated()) 
        throw std::out_of_range("Iterator is terminated.");

    return current->Element();
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ********************************************************* */

// Specific member functions (inherited from ForwardIterator)
template <typename Data>
const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::FirstLeftLeaf(const typename BinaryTree<Data>::Node* node){
    if(node!=nullptr){
        while(node->HasLeftChild()){
            stack.Push(node);
            node = &node->LeftChild();
        }
        if(node->HasRightChild()){
            stack.Push(node);
            node = &node->RightChild();
            node = FirstLeftLeaf(node);
        }
    }
    return node;
}


template <typename Data>
BTPostOrderIterator<Data>&  BTPostOrderIterator<Data>::operator++(){
    if(!Terminated()){
        if(!(stack.Empty())){
            if (stack.Top()->HasRightChild() && !(&(stack.Top()->RightChild()) == current)) {
                current = &(stack.Top()->RightChild());
                current = FirstLeftLeaf(current);
            } else {
                current = stack.TopNPop();
            }
        } else {
            current = nullptr;
        }
    }
    else {
        throw std::out_of_range("Iterator is terminated.");
    }
    return *this;
}

/* ********************************************************* */

// Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
    stack.Clear();
    current = root;
    current = FirstLeftLeaf(root);
}


/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
//      BT PostOrderMutableIterator
// Copy assignment
template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& right) {
    this->root=right.root;
    this->stack=right.stack;
    this->current=right.current;
    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& right) noexcept {
    std::swap(this->root, right.root);
    std::swap(this->stack, right.stack);    
    std::swap(this->current, right.current);
    return *this;
}

/* ********************************************************* */
// Comparison operators
template <typename Data>
inline bool BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator &other) const noexcept {
    return BTPostOrderIterator<Data>::operator==(other);
}

/* ********************************************************* */
// Specific member functions (inherited from MutableIterator)
template <typename Data>
Data& BTPostOrderMutableIterator<Data>::operator*()  {
    if((this->current) != nullptr) 
        return const_cast<Data&>((this->current)->Element());
    
    throw std::out_of_range("Error: Out of range iterator"); 
    
}

/* ********************************************************************************************************** */
/* ************************************************************************** */
//      BT InOrderIterator
// Specific constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &other) {
    if(!other.Empty()){
        root = current = &other.Root();
        current = MostLeftNode(root);
    }
}

/* ********************************************************* */
// Copy constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator & other) {
    stack = other.stack;
    root = other.root;
    current = other.current;
}

//Move constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& other) noexcept {
    std::swap(stack, other.stack);
    std::swap(current, other.current);
    std::swap(root, other.root); 
}

/* ********************************************************* */

// Copy assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& other) {
    stack = other.stack;
    root = other.root;
    current = other.current;
    return *this;
}

// Move assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& other) noexcept {
    std::swap(stack, other.stack);
    std::swap(root, other.root);
    std::swap(current, other.current);
    return *this;
}

/* ********************************************************* */
// Comparison operators
template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator &other) const noexcept {
    return ((current == other.current) && (root == other.root));
}

/* ********************************************************* */
// Specific member functions (inherited from Iterator)
template <typename Data>
const Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated()) 
        throw std::out_of_range("Iterator is terminated.");
    
    return current->Element();
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

/* ********************************************************* */

// Specific member functions (inherited from ForwardIterator)

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++(){
    if(Terminated()) 
    throw std::out_of_range("Iterator is terminated.");

    if((stack.Empty()) && !(current->HasRightChild())) {
        current=nullptr;
    } else { 
        if(current->HasRightChild()){
            current = MostLeftNode(&current->RightChild());
        } else {
            current = stack.TopNPop();
        }
    }
    
    return *this;
}

template <typename Data>
const typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::MostLeftNode(const typename BinaryTree<Data>::Node* node) {
    if(node != nullptr) {
        while(node->HasLeftChild()) {
            stack.Push(node);
            node = &node->LeftChild();
        }
    }
    return node;
}

/* ********************************************************* */
// Specific member functions (inherited from ResettableIterator)

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
    stack.Clear(); 
    current = MostLeftNode(root);
}

/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
//      BT InOrderMutableIterator
// Copy assignment
template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator& right) {
    this->root=right.root;
    this->stack=right.stack;
    this->current=right.current;
    return *this;
}

// move assignment
template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator&& right) noexcept {
    std::swap(this->root, right.root);
    std::swap(this->stack, right.stack);
    std::swap(this->current, right.current);
    return *this;
}

/* *********************************************************** */
// Comparison operators
template <typename Data>
bool BTInOrderMutableIterator<Data>::operator==(const BTInOrderMutableIterator &other) const noexcept {
    return BTInOrderIterator<Data>::operator==(other);
}

/* ************************************************************ */
// Specific member functions (inherited from MutableIterator)
template <typename Data>
Data& BTInOrderMutableIterator<Data>::operator*()  {
    if((this->current) != nullptr) 
        return const_cast<Data&>((this->current)->Element());
    
    throw std::out_of_range("Error: Out of range iterator"); 
    
}

/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
//      BT BreadthIterator
// Specific constructors
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& other) {
    if(!other.Empty())
            current = root = &other.Root();
}

/* ********************************************************* */
// Copy constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator &other) {
    queue = other.queue;
    current = other.current;
    root = other.root;
}

//Move constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& other) noexcept {
    std::swap(queue, other.queue);
    std::swap(root, other.root);
    std::swap(current, other.current); 
}

/* ********************************************************* */
// Copy assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& other) {
    root = other.root;
    current = other.current;
    queue = other.queue;
    return *this;
}

// Move assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& other) noexcept {
    std::swap(root, other.root);
    std::swap(current, other.current);
    std::swap(queue, other.queue);
    return *this;
}

/* ********************************************************* */
// Comparison operators
template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator &other) const noexcept {
    return (current == other.current && root == other.root);
}

/* ********************************************************* */
// Specific member functions (inherited from Iterator)
template <typename Data>
const Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated()) 
        throw std::out_of_range("Iterator is terminated.");

    return current->Element();
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ********************************************************* */
// Specific member functions (inherited from ForwardIterator)
template <typename Data>
 BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if(!Terminated()) { //se non è terminato
        if (current->HasLeftChild()) 
            queue.Enqueue(&(current->LeftChild())); 
        if (current->HasRightChild()) 
            queue.Enqueue(&(current->RightChild()));
        if (!queue.Empty()) 
            current = queue.HeadNDequeue();
        else current = nullptr;
    } else {
        throw std::out_of_range("Iterator is terminated.");
    }
    return *this;
}

/* ********************************************************* */
// Specific member functions (inherited from ResettableIterator)

template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
    queue.Clear();
    current = root;
}
/* ********************************************************************************************************** */
/* ********************************************************************************************************** */
//      BT BreadthMutableIterator
// Copy assignment
template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator& other) {
    this->root = other.root;
    this->queue = other.queue;
    this->current = other.current;
    return *this;
}

// Move assignment
template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator&& other) noexcept {
    std::swap(this->root, other.root);
    std::swap(this->queue, other.queue);
    std::swap(this->current, other.current);
    return *this;
}

/****************************************** */
// Comparison operators
template <typename Data>
inline bool BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator &other) const noexcept {
    return BTBreadthIterator<Data>::operator==(other);
}

/* ***************************************** */
// Specific member functions (inherited from MutableIterator)
template <typename Data>
Data& BTBreadthMutableIterator<Data>::operator*()  {
    if((this->current) != nullptr) 
        return const_cast<Data&>((this->current)->Element());
    
    throw std::out_of_range("Error: Out of range iterator"); 
}

/* ********************************************************************************************************** */

}