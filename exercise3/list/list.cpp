#include "list.hpp"
namespace lasd {
    
/* ************************************************************************** */

// Specific constructors (Node)
template <typename Data>
List<Data>::Node::Node(const Data& new_dato) {
    dato = new_dato;
}

template <typename Data>
List<Data>::Node::Node(Data&& new_dato) noexcept {
    std::swap(dato , new_dato);
}

/* ************************************************************************** */

//Copy constructor (Node)
template <typename Data>
List<Data>::Node::Node(const Node& new_nodo) {
    dato = new_nodo.dato;
    next = new_nodo.next;
}

//Move constructor (Node)
template <typename Data>
List<Data>::Node::Node(Node&& new_nodo) noexcept {
    std::swap(dato, new_nodo.dato);
    std::swap(next, new_nodo.next);
}

/* ************************************************************************** */

//Destructor (Node)
template <typename Data>
inline List<Data>::Node::~Node() {
    delete next;
}

/* ************************************************************************** */

//Comparison operators (Node)
template <typename Data>
bool List<Data>::Node::operator == (const Node& new_nodo) {
    return (new_nodo.dato == dato);
}

/* ************************************************************************** */
//LISTE

// Specific constructor (A list obtained from a TraversableContainer)
template <typename Data>
List<Data>::List(const TraversableContainer<Data>& cont) {
    cont.Traverse(
        [this](const Data& dato) {
            InsertAtBack(dato);
        }
    );
}


//Specific constructor (A list obtained from a MappableContainer)
template <typename Data>
List<Data>::List(MappableContainer<Data>&& cont) {
    cont.Map(
        [this](Data& dat) {
            InsertAtBack(std::move(dat));
        }
    );
}

/* ************************************************************************** */

// Copy constructor (Liste)
template <typename Data>
List<Data>::List(const List<Data>& lista) {
    if(!(size = lista.size))
        return;

    testa = new Node(*(lista.testa));
    coda = testa;

    Node *tmp = lista.testa->next;
    
    while(tmp != nullptr){
        coda->next = new Node(*tmp);
        coda = coda->next;
        tmp = tmp->next;
    }
}


//Move constructor (Liste)
template <typename Data>
List<Data>::List(List<Data>&& lista) {
    std::swap(testa, lista.testa); // Scambio il puntatore alla testa della lista con il puntatore alla testa della lista passata come parametro
    std::swap(coda, lista.coda); // Scambio il puntatore alla coda della lista con il puntatore alla coda della lista passata come parametro
    std::swap(size, lista.size); // Scambio la dimensione della lista con la dimensione della lista passata come parametro
}

/* ************************************************************************** */

//Destructor (Liste)
template <typename Data>
List<Data>::~List() {
    Clear(); // Chiamo la funzione Clear per eliminare tutti gli elementi della lista uno ad uno
}

/* ************************************************************************** */

//Copy assignment (Liste)
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& lista) {
if (this != &lista) { // Controllo l'auto-assegnazione
    Clear(); // Elimino tutti gli elementi della lista corrente
    if (lista.size > 0) {
        testa = new Node(*(lista.testa));

        Node* current = testa;
        Node* listaCurrent = lista.testa->next;
        while (listaCurrent != nullptr) {
            current->next = new Node(*listaCurrent);
            current = current->next;
            listaCurrent = listaCurrent->next;
        }
        coda = current;
    }
    size = lista.size;
}
return *this;
}


//Move assignment (Liste)
template <typename Data>
List<Data>& List<Data>::operator = (List&& lista) {
    std::swap(lista.testa, testa);
    std::swap(lista.coda, coda);
    std::swap(lista.size, size);
    return *this;
}

/* ************************************************************************** */

//Comparison operators (Liste)
template <typename Data>
bool List<Data>::operator == (const List& lista) const noexcept {
    if(size != lista.size)  // Se le dimensioni delle liste sono diverse
        return false;
    
    Node* currentList = testa; // Creo un puntatore costante alla lista corrente
    Node* NewList = lista.testa; // Creo un puntatore costante alla nuova lista passata come parametro
    while (currentList != nullptr) { 
        if(currentList->dato != NewList->dato)  // Se gli elementi correnti sono diversi
            return false;
        //scorro la lista
        currentList = currentList->next; 
        NewList = NewList->next; 
    }
    return true;
}

/* ************************************************************************** */

// Specific member functions (List)

template<typename Data>
void List<Data>::InsertAtFront(const Data& new_dato) {
    Node* tmp = new Node(new_dato); // Creo un nuovo nodo con il dato passato come parametro
    tmp->next = testa; // Imposto il puntatore al prossimo nodo del nuovo nodo come la testa della lista
    testa = tmp; // Imposto la testa della lista come il nuovo nodo
    size++; // Incremento la dimensione della lista

    if(coda == nullptr) // Se la coda è vuota
        coda = testa; // Imposto la coda come la testa
}

template<typename Data>
void List<Data>::InsertAtFront(Data&& dato) {
    Node* tmp = new Node(std::move(dato));
    tmp->next = testa;
    testa = tmp;
    size++;

    if(coda == nullptr)
        coda = testa;
}


template <typename Data>
void List<Data>::RemoveFromFront() {
    if(Empty()) //Se la lista è vuota lancio l'eccezione
        throw std::length_error("The list is empty");

    Node* tmp = testa;  //Mi creo un nodo temporaneo e lo inizializzo con la testa della lista
    if(testa == coda)  // se ho un solo elemento imposto il puntatore alla testa e coda a nullptr
        testa = coda = nullptr;
    else {
        testa = testa->next;   //altrimenti scorro il puntatore della testa
        tmp->next = nullptr;    //elimino il collegamento del primo nodo con il successivo
    }
    delete tmp;     //e successivamente dealloco il nodo
    size--;
}

template <typename Data>
Data List<Data>::FrontNRemove() {
    if(Empty())
        throw std::length_error("The list is empty");

    Data old_dato = testa->dato;    //inizializzio old_dato con il dato della testa della lista
    RemoveFromFront();  // successivamente rimuovo la testa e ritorno il dato eliminato
    return old_dato;
}

template<typename Data>
void List<Data>::InsertAtBack(const Data& new_dato) {
    Node* newNode = new Node(new_dato);
    if (size == 0) {
        testa = coda = newNode;
    } else {
        coda->next = newNode;
        coda = newNode;
    }
    size++;
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& dato) {
    Node* newNode = new Node(std::move(dato));
    if (size == 0) {
        testa = coda = newNode;
    } else {
        coda->next = newNode;
        coda = newNode;
    }
    size++;
}

/* ************************************************************************** */

//Specific member function (List) (inherit from ClearableContainer)

template <typename Data>
void List<Data>::Clear() {
    delete testa;
    testa = nullptr;
    coda = nullptr;
    size = 0;
}

/* ************************************************************************** */

//specific member function (List) (inherited from DictionaryContainer)

template <typename Data>
bool List<Data>::Insert(const Data& dato) {
    if(Exists(dato))    // Se l'elemento è già presente nella lista ritorna falso
        return false;

    InsertAtBack(dato); // Altrimenti lo inserisco in coda
    return true;
}


template <typename Data>
bool List<Data>::Insert(Data&& dato) noexcept {
    if(Exists(dato))    // Se l'elemento è già presente nella lista ritorna falso
        return false;
        
    InsertAtBack(std::move(dato));
    return true;
}


template <typename Data>  
inline bool List<Data>::Remove(const Data & data){
    if(!size)   //se la lista è vuota ritorna falso
        return false;

    if(testa->dato == data){    //se l'elemento da eliminare è in testa
        RemoveFromFront();
        return true;
    }

    Node *temp = testa->next;
    Node *x = testa;

    while(temp != nullptr){

        if(temp->dato == data){ 
            x->next = temp->next;

            if(temp->next){     //se l'elemento da eliminare non è l'ultimo
                temp->next = nullptr;
            } else{
                coda = x;   //se l'elemento da eliminare è l'ultimo aggiorno la coda
            }

            delete temp;
            --size;
            return true;
        }
        //scorro la lista
        x = temp;
        temp = temp->next;
    }
    return false; //in caso non trovi l'elemento
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)

template <typename Data>
const Data& List<Data>::operator[](ulong i) const {
    if(!Empty() && i<size) { 
        Node* nodo = testa; // Creo un nodo e lo inizializzo con la testa della lista
        for(ulong j=0; j<i; j++) { // Scorro la lista fino all'indice i
            nodo = nodo->next; // Imposto il nodo come il prossimo nodo della lista
        }
        return nodo->dato; // Restituisco l'elemento del nodo
    }
    throw std::out_of_range("Index out of range"); //se l'indice è maggiore della dimensione della lista lancio l'eccezione
}

template <typename Data>
Data& List<Data>::operator[](ulong i) {
    if(!Empty() && i<size) { 
        Node* nodo = testa;
        for(ulong j = 0; j < i; j++) {
            nodo = nodo->next;
        }
        return nodo->dato;
    }
    throw std::out_of_range("Index out of range");
}


template <typename Data>
const Data& List<Data>::Front() const {
    if(!Empty()) // Se la lista non è vuota
        return testa->dato; // Restituisco il primo elemento
    throw std::length_error("Access to an empty list");
}

template <typename Data>
Data& List<Data>::Front() {
    if(!Empty())
        return testa->dato;
    throw std::length_error("Access to an empty list");
}


template <typename Data>
const Data& List<Data>::Back() const {
    if(!Empty()){    // Se la lista non è vuota
        return coda->dato;  // Restituisco l'ultimo elemento
    }
    throw std::length_error("Access to an empty list");
};

template <typename Data>
Data& List<Data>::Back() {
    if(!Empty()){
        return coda->dato;
    }
    throw std::length_error("Access to an empty list");
};

/* ************************************************************************** */

// Specific member function (inherited from TraversableContainer)
template <typename Data>
inline void List<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

// Specific member function (inherited from PreOrderTraversableContainer)
template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
  PreOrderTraverse(fun, testa);
}

// Specific member function (inherited from PostOrderTraversableContainer)
template <typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
  PostOrderTraverse(fun, testa);
}

// Specific member function (inherited from MappableContainer)
template <typename Data> 
inline void List<Data>::Map(MapFun fun)  {
  PreOrderMap(fun);
}

// Specific member function (inherited from PreOrderMappableContainer)
template <typename Data> 
inline void List<Data>::PreOrderMap(MapFun fun)  {
  PreOrderMap(fun, testa);
}

// Specific member function (inherited from PostOrderMappableContainer)
template <typename Data> 
inline void List<Data>::PostOrderMap(MapFun fun)  {
  PostOrderMap(fun, testa);
}

/* ************************************************************************** */

//auxiliary function (List) (for traversableContainer)

template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun, Node* tmp) const {
    if(!tmp)
        return;

    fun(tmp->dato);
    PreOrderTraverse(fun, tmp->next);
}


template <typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun, Node* tmp) const {
    if(tmp != nullptr){    //scorro la lista
        PostOrderTraverse(fun, tmp->next);    
        fun(tmp->dato);    
    }
}

/* ************************************************************************** */

//auxiliary function (List) (for MappableContainer)

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node* tmp)  {
    if(!tmp)
        return;

    fun(tmp->dato);
    PreOrderMap(fun, tmp->next);

}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node* tmp)  {
    if(tmp != nullptr){    
        PostOrderMap(fun, tmp->next);    
        fun(tmp->dato);   
    }
}

/* ************************************************************************** */

}