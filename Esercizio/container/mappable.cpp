
namespace lasd {

/* ************************************************************************** */
// Specific member function (inherited from PreOrderMappableContainer) OVERRIDE

template<typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun)  {
    PreOrderMap(fun);
}


template<typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun)  {
    PostOrderMap(fun);
}


template<typename Data>
void InOrderMappableContainer<Data>::Map(MapFun fun)  {
    InOrderMap(fun);
}


template<typename Data>
void BreadthMappableContainer<Data>::Map(MapFun fun)  {
    BreadthMap(fun);
}

/* ************************************************************************** */

}
