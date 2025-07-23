
namespace lasd {
/* ************************************************************************** */

// Specific constructor (Vector)

//creo nuovo vettore
template<typename Data>
Vector<Data>::Vector(const ulong N) { 
    size = N;
    Vett = new Data[N]{};
}


//creo vettore con dimensione di traversable container
template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & vett) {
    size = vett.Size();
    Vett = new Data[size]{};
    ulong i = 0;
    vett.Traverse(
        [this, &i](const Data & dato) {
            Vett[i++] = dato;
        }
    );
}


//creo vettore con dimensione di MappableContainer container
template<typename Data>
Vector<Data>::Vector(MappableContainer<Data> && vett) noexcept {
    size = vett.Size();
    Vett = new Data[size] {};
    ulong i = 0;
    vett.Map(
        [this, &i](Data & dato) {
           Vett[i++] = std::move(dato);
        }
    );
}

/* ************************************************************************** */

//Copy costructor (Vector)
template<typename Data>
Vector<Data>::Vector(const Vector<Data> & cont) {
    size = cont.size;
    Vett = new Data[size];
    std::copy(cont.Vett, cont.Vett + size, Vett);
}

//Move constructor (Vector)
template<typename Data>
Vector<Data>::Vector(Vector<Data> && cont) noexcept {
    std::swap(size, cont.size);
    std::swap(Vett, cont.Vett);
}


/* ************************************************************************** */

//Copy assignment (Vector)
template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & cont) {
    delete[]Vett;
    size = cont.size;
    Vett = new Data[cont.size];
    std::copy(cont.Vett, cont.Vett+size, Vett);
    return *this; 
}


//Move assignment (Vector)
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector&& cont) noexcept {
    std::swap(Vett, cont.Vett);
    std::swap(size, cont.size);
    return *this;
}

/* ************************************************************************** */

//Comparison operator (Vector)
template<typename Data>
bool Vector<Data>::operator == (const Vector<Data> & cont) const noexcept{
    if(size == cont.size){
        for(ulong i=0; i < size; ++i){
            if(Vett[i] != cont.Vett[i]){
                return false;   //se anche un solo elemento è diverso, i due vettori non sono uguali
            }
        }
        return true;    //se esce dal for vuol dire che tutti gli elementi sono uguali
    } 
    return false;
}

/* ************************************************************************** */

//Specific member function (Vector) (inherited from ClearableContainer) 
template<typename Data>
void Vector<Data>::Clear() {
    delete[] Vett;   // Dealloca la memoria occupata dal vettore
    Vett = nullptr;  // Imposta il puntatore a nullptr per evitare accessi non validi
    size = 0;        // Imposta la dimensione del vettore a 0
}

/* ************************************************************************** */
//Specific member function (Vector) (inherited from ResizableContainer)
template<typename Data>
void Vector<Data>::Resize(const ulong N){
    if(N == 0){   //se la nuova grandezza del vettore è 0 ovvimante chiamiamo Clear()
        Clear();
    } else if(size != N){
        Data * TempVett = new Data[N]{};      //alloco un vettore temporaneo di dimensione N
        ulong min_size = (size < N) ? size : N;   //prendo la dimensione minore tra size e N e la memorizzo in min_size
        for(ulong i =0; i < min_size; ++i){
            std::swap(Vett[i], TempVett[i]); //scambio gli elementi del vettore originale con quelli del vettore temporaneo
        }
        std::swap(Vett, TempVett);   //scambio dei punattori
        size = N;    //dopo aver scambiato tutti gli elementi aggiorno size con il valore della nuova dimensione
        delete[] TempVett;
    }
}

/* ************************************************************************** */
//funzioni prendono in input l'indice i dell'elemento dell'array da accedere. 
//se questo indice non esiste e quindi è >= di size allora viene lanciata un'eccezione altrimentiritorna l'elemento 
template<typename Data>
const Data & Vector<Data>::operator[](const ulong i) const {
    if(i < size)
        return Vett[i];
    throw std::out_of_range("Access at position " + std::to_string(i));
}

template<typename Data>
Data & Vector<Data>::operator[](const ulong i) {
    if(i < size)
        return Vett[i];
    throw std::out_of_range("Access at position " + std::to_string(i));
}


// Specific member functions (inherited from LinearContainer)
template<typename Data>
const Data & Vector<Data>::Front() const {
    if(size > 0){
        return Vett[0];
    }
    throw std::length_error("Access to an empty vector");
}

template<typename Data>
Data & Vector<Data>::Front() {
    if(size > 0){
        return Vett[0];
    }
    throw std::length_error("Access to an empty vector");
}


template<typename Data>
const Data & Vector<Data>::Back() const {
    if(size > 0){
        return Vett[size - 1];
    }
    throw std::length_error("Access to an empty vector");
}

template<typename Data>
Data & Vector<Data>::Back() {
    if(size > 0){
        return Vett[size - 1];
    }
    throw std::length_error("Access to an empty vector");
}

/* ************************************************************************** */

//Copy assignment (SortableVector)
template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector &vett) {
  Vector<Data>::operator=(vett);   //chiamo l'operatore di assegnamento della classe base
  return *this;
}

//Move assignment (SortableVector)
template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(SortableVector &&vett) noexcept {
  Vector<Data>::operator=(std::move(vett));
  return *this;
}

/* ************************************************************************** */

}