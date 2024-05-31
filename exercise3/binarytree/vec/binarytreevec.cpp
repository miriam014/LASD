namespace lasd {

/* ************************** */
//NodeVec

//Copy constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &elem, ulong i, BinaryTreeVec<Data>* bt){
    element = elem;
    index = i;
    tree = bt;
}

//Move constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data && elem, ulong i, BinaryTreeVec<Data>* bt) noexcept{
    std::swap(element, elem);
    index = i;
    tree = bt;
}

//Destructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::~NodeVec(){
    if(!tree->root.Empty()){
        tree->root[Index()] = nullptr;
    }  
}


//Copy assignment
template <typename Data>
BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec & other){
    element = other.element;
    index = other.index;
    tree = other.tree;
    return *this;
}

//Move assignment
template <typename Data>
BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(NodeVec && other) noexcept{
    std::swap(element, other.element);
    std::swap(index, other.index);
    std::swap(tree, other.tree);
    return *this;
}

//HasLeftChild
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
    return ((index*2 + 1) < (tree->root).Size() && tree->root[index *2 + 1] != nullptr);
}

//HasRightChild
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    return ((index *2 + 2) < (tree->root).Size() && tree->root[index *2 + 2] != nullptr);
}

//RightChild
template <typename Data>
BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::RightChild() {
    if(HasRightChild())
        return *(tree->root.operator[](index *2 + 2));
    else
        throw std::out_of_range("RightChild doe not exist");
}

template <typename Data>
const BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(HasRightChild())
        return (*tree->root.operator[](index *2 + 2));
    else
        throw std::out_of_range("RightChild doe not exist");
}


//LeftChild
template <typename Data>
BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if(HasLeftChild())
        return *(tree->root.operator[](index *2 + 1));
    else
        throw std::out_of_range("LeftChild doe not exist");
}

template <typename Data>
const BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(HasLeftChild()) 
        return *tree->root.operator[](index *2 + 1);
    else
        throw std::out_of_range("LeftChild doe not exist");
}


/* ************************** */
// BinaryTreeVec

//Specific constructors
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& cont) : root(cont.Size()){
    ulong i = 0;
    cont.Traverse([this, &i](const Data& data){
        this->root[i] = new NodeVec(data, i, this);
        i++;
    }); 
    this->size = cont.Size();
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& cont) noexcept : root(cont.Size()){
	ulong i = 0;
    cont.Map([this, &i](Data& data){
        this->root[i] = new NodeVec(data, i, this);
        i++;
    }); 
    this->size = cont.Size();
}

/* ************** */
// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec& other) : root(other.root.Size()) {
    size = other.Size();
    for(ulong i = 0; i < size; i++){
        this->root[i] = new NodeVec(other.root[i]->Element(), i, this);
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& other) noexcept {
    std::swap(size, other.size);
    std::swap(root, other.root);

    for(ulong i = 0; i < this->Size(); i++)
        this->root[i]->tree = this;
    for(ulong i = 0; i < other.Size(); i++)
        other.root[i]->tree = &other;  
}

/* ************** */
// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
  Clear();
}

/* ************** */

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& other) {
    Clear();
    root.Resize(other.Size());
    this->size = other.Size();
    for(ulong i = 0; i < this->Size(); i++)
        this->root[i] = new NodeVec(other.root[i]->Element(), i, this);
    
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& other) noexcept{
    std::swap(size, other.size);
    std::swap(root, other.root);
    for(ulong i = 0; i < this->Size(); i++)
        this->root[i]->tree = this;
    for(ulong i = 0; i < other.Size(); i++)
        other.root[i]->tree = &other;

  return *this;
}


/* ************** */
//Specific member function (inherited from BinaryTree)
template <typename Data>
const BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
    if(!this->Empty()) 
        return *root[0];
    
    throw std::length_error(" Empty tree");
}

// Specific member function (inherited from MutableBinaryTree)
template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if(!this->Empty())
        return *root[0]; 
        
    throw std::length_error(" Empty tree");
}


// Specific member function (inherited from ClearableContainer)
template <typename Data>
inline void BinaryTreeVec<Data>::Clear(){
    if (this->Size() > 0) {
        for (ulong i = 0; i < this->Size(); i++) {
            if(root[i] != nullptr){
                delete root[i];
                root[i] = nullptr;
            }
        }

        root.Clear();
        this->size = 0;
    }
}


// Specific member function (inherited from BreadthTraversableContainer)
template<typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const {
    for (ulong i = 0; i < this->Size(); i++) {
        if (root[i] != nullptr) {
            fun(root[i]->Element());
        }
    }
}

// Specific member function (inherited from BreadthMappableContainer)
template<typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun fun) {
    for (ulong i = 0; i < this->Size(); i++) {
        if (root[i] != nullptr) {
            fun(root[i]->Element());
        }
    }
}

/* ************************** */

}