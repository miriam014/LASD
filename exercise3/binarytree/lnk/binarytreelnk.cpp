
namespace lasd {

/* ************************************************************************** */
//Constructors
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& newElement){
  element = newElement;
  left = nullptr;
  right = nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& newElement) noexcept{
  std::swap(element, newElement);
  left = nullptr;
  right = nullptr;
}


//Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk & other) {
    element = other.element;
    if(other.HasLeftChild())
        left = new NodeLnk(*other.left);
    if(other.HasRightChild())
        right = new NodeLnk(*other.right);
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk && other) noexcept{
    std::swap(element, other.element);
    std::swap(left, other.left);
    std::swap(right, other.right);
}


//Destructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
    delete left;
    delete right;
}

/* ******************************************************* */

//Specific member functions from binarytree
template <typename Data>
const struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if(!HasLeftChild())
        throw std::out_of_range("Access to an empty child.");

    return *left;
}

template <typename Data>
const struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    if(!HasRightChild())
        throw std::out_of_range("Access to an empty child.");

    return *right;
}

//Specific member functions from mutablebinarytree

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() {
    if(!HasLeftChild())
        throw std::out_of_range("Access to an empty child.");

    return *left;
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() {
    if(!HasRightChild())
        throw std::out_of_range("Access to an empty child.");

    return *right;
}


/* ************************************************************************** */
/* ************************************************************************** */

//Specific constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& cont){
    size = cont.Size();
    QueueVec<NodeLnk **> queue; // coda di puntatori a nodelnk
    queue.Enqueue(&root);

    cont.Traverse([&queue](const Data & data){  //per ogni elemento del cont mi creo un nodo e lo metto in coda
        NodeLnk *&node = *queue.HeadNDequeue();
        node = new NodeLnk(data); 
        queue.Enqueue(&node->left);
        queue.Enqueue(&node->right);
    });
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> &&cont) {
    size = cont.Size();
    QueueVec<NodeLnk **> queue;
    queue.Enqueue(&root);

    cont.Map([&queue](const Data & data){ 
        NodeLnk *&node = *queue.HeadNDequeue();
        node = new NodeLnk(std::move(data)); 
        queue.Enqueue(&node->left);
        queue.Enqueue(&node->right);
    });
}

/* **************************************** */
//Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk &other) {
    Clear();
    size = other.Size();
    if(other.root!=nullptr) {
        root = new NodeLnk(*other.root);
        size = other.Size();
    }     
}

//Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk &&other) noexcept {
    std::swap(root, other.root);
    std::swap(size, other.size);
}

/* **************************************** */
// Destructor
template <typename Data>
inline BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    delete root;
}

// Copy assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> &other) {
    if(other.size!=0){
        BinaryTreeLnk<Data>* tmp = new BinaryTreeLnk<Data>(other);
	    std::swap(*tmp, *this);
	    delete tmp;
    }else{
        Clear();
    }
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> &&other) noexcept {
    std::swap(root,other.root);
    std::swap(size,other.size);
    return *this;
}

/* **************************************** */

// Comparison operators
template <typename Data>
inline bool BinaryTreeLnk<Data>::operator == (const BinaryTreeLnk<Data> &other) const noexcept {
    return BinaryTree<Data>::operator==(other);
}

/* ***************************************** */

// Specific member functions (inherited from BinaryTree)
template <typename Data>
inline const struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if(this->Empty())
        throw std::length_error("Access to an empty tree.");

    return *root;
}

// Specific member functions (inherited from MutableBinaryTree)
template <typename Data>
inline BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() {
    if(this->Empty())
        throw std::length_error("Access to an empty tree.");
    return *root;
}


// Specific member functions (inherited from ClerableContainer)
template <typename Data>
void BinaryTreeLnk<Data>::Clear() {
    delete root;
    root = nullptr;
    size = 0;
}


/* ************************************************************************** */

}
