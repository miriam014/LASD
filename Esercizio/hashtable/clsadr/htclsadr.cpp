
namespace lasd {

/* ************************************************************************** */

//Default constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
    table = new lasd::List<Data>[tableSize] {}; //aray di liste vuote
}


/* *********************************************** */

//Specific constructors
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong new_size) {
    tableSize = std::pow(2, std::ceil(log2((new_size <= 16) ? 16 : new_size)));     //se new_size è minore di 16, tableSize = log(16)arrotondato per eccesso^2, altrimenti tableSize = log(new_size)^2
    table = new lasd::List<Data>[tableSize] {};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& other) : HashTableClsAdr(other.Size()) {
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong new_size, const TraversableContainer<Data>& other) : HashTableClsAdr(new_size) {
    InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& other) : HashTableClsAdr(other.Size()) {
    InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong new_size, MappableContainer<Data>&& other) : HashTableClsAdr(new_size) {
    InsertAll(std::move(other));
}

/* *********************************************** */
//Copy constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& other) : HashTable<Data>(other) {
    table = new lasd::List<Data>[other.tableSize] {};     

    for(ulong i=0; i < tableSize; i++) {
        table[i] = other.table[i];
    }
}

//Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& other) noexcept : HashTable<Data>(std::move(other)) {
    std::swap(table, other.table);
}

/* *********************************************** */
//Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& other) {
    HashTable<Data>::operator=(other);
    delete[] table;

    table = new lasd::List<Data>[other.tableSize] {}; 
    for(ulong i=0; i < tableSize; i++) {
        table[i] = other.table[i];
    }
    return *this;
}

//Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& other) noexcept {
    HashTable<Data>::operator=(std::move(other));
    std::swap(table, other.table);
    return *this;
}

/* *********************************************** */
//Comparison operators
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& other) const noexcept {
    if(size != other.size) {
        return false;
    }

    for(ulong i=0; i < tableSize; i++) {
        table[i].Traverse(
            [&other, i](const Data& dat) {      //verifico se l'elemento dat è presente nella tabella other tramite la funzione Exists
                if(!other.Exists(dat)) {        //se non è presente, ritorno false perchè le due tabelle non sono uguali
                    return false;
                }
                return true;
            }
        );
    }
    return true;
}

/*******************************************************/
// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& dat) {
    bool result = false;
    //calcolo l'indice in cui l'elemento dat dovrebbe essere inserito nella tabella hash chiamando la funzione HasKey
    ulong index = HashKey(Hashable<Data>()(dat));       
    result = table[index].Insert(dat);
    if(result)
        size++;
    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& dat) noexcept {
    bool result = false;
    ulong index = HashKey(Hashable<Data>()(dat));
    result = table[index].Insert(std::move(dat));
    if(result)
        size++;
    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& dat) {
    bool result = false;
    ulong index = HashKey(Hashable<Data>()(dat));
    result = table[index].Remove(dat);
    if(result)
        size--;
    return result;
}

/*******************************************************/
// Specific member functions (inherited from TestableContainer)
template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& dat) const noexcept {
    ulong index = HashKey(Hashable<Data>()(dat));
    return (table[index].Exists(dat)); 
    //controll ase nell'indice passatogli per riferimento ci sia effettivamente l'elemento dat    
}

/*********************************************************/
// Specific member functions (inherited from ResizableContainer)
template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong new_size) {
    ulong newTableSize = (new_size <= 16)? 16 : std::pow(2, std::ceil(log2(new_size)));
    size = 0;       //pongo la dimensione della tabella a 0 perchè durante il resize vado a reinserire gli elementi nella tabella
    
    lasd::List<Data>* newTable = new lasd::List<Data>[newTableSize] {};
    std::swap(newTable, table);
    std::swap(newTableSize, tableSize);
    for(ulong i = 0; i < newTableSize; i++){
        InsertAll(newTable[i]); //reinserisco gli elementi della vecchia tabella nella nuova
    }
    delete[] newTable;
}

/*********************************************************/
// Specific member functions (inherited from ClearableContainer)
template <typename Data>
void HashTableClsAdr<Data>::Clear() {
    delete[] table;
    table = new lasd::List<Data>[tableSize] {}; //creo una nuova tabella dalle stesse dimensioni di quella appena eliminata
    size = 0;   //imposto size a 0 perchè la tabella è vuota
}

/* ************************************************************************** */

}
