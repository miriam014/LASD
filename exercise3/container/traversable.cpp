
namespace lasd {

/* ************************************************************************** */

// Specific member function (inherited from TraversableContainer)

template <typename Data, typename Accumulator>
using FoldFun = typename TraversableContainer<Data>:: FoldFun<Accumulator>;


template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const {
  Traverse(
        [&acc, fun](const Data &dato) { 
            acc = fun(dato, acc); 
        }
    );
  return acc;
};

/* ************************** */

// Override TraversableContainer member
template<typename Data>
bool TraversableContainer<Data>::Exists(const Data& x) const noexcept {
    bool result = false;
    Traverse(
        [x, &result](const Data& dato){
            result |= (dato == x);
        }
    );
    return result;
}

/* ************************** */

// Specific member function (inherited from PreOrderTraversableContainer)
template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    PreOrderTraverse(
        [fun, &acc](const Data& x) {
            acc = fun(x, acc);
        }
    );
    return acc;
}

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

/* ************************** */

// PostOrder Traversable Container
template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    PostOrderTraverse(
        [fun, &acc](const Data& x) {
            acc = fun(x, acc);
        }
    );
    return acc;
}

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PostOrderTraverse(fun);
}

/* ************************** */

// InOrder Traversable Container
template <typename Data>
template <typename Accumulator>
Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    InOrderTraverse(
        [fun, &acc](const Data& x) { 
            acc = fun(x, acc);
        }
    );
    return acc;
}

template <typename Data>
void InOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    InOrderTraverse(fun);
}

/* ************************** */

template <typename Data>
template <typename Accumulator>
Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    BreadthTraverse(
        [fun, &acc](const Data& x) {
            acc = fun(x, acc);
        }
    );
    return acc;
}

template <typename Data>
void BreadthTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    BreadthTraverse(fun);
}

/* ************************************************************************** */

}
