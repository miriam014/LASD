
namespace lasd {

/* ************************************************************************** */

//Default constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
    table = new Data[tableSize] {};
    tableFlag = new Flag[tableSize] {};
}

/* *********************************** */

//Specific constructors
template <typename Data> 
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong new_size) {
    tableSize = std::pow(2, std::ceil(log2((new_size < 16) ? 16 : new_size)));
    table = new Data[tableSize] {};
    tableFlag = new Flag[tableSize] {};
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& other) : HashTableOpnAdr(other.Size()*2) {
    InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size, const TraversableContainer<Data>& other) : HashTableOpnAdr(size) {
    InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& other) : HashTableOpnAdr(other.Size()*2) {
    InsertAll(std::move(other));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size, MappableContainer<Data>&& other) : HashTableOpnAdr(size) {
    InsertAll(std::move(other));
}

/* *********************************** */

//Copy constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& other) : HashTable<Data>(other) {
    table = new Data[tableSize] {};
    tableFlag = new Flag[tableSize] {};
    for(ulong i=0; i < tableSize; i++) {
        table[i] = other.table[i];
        tableFlag[i] = other.tableFlag[i];
    }
}

//Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& other) noexcept : HashTable<Data>(std::move(other)) {
    std::swap(table, other.table);
    std::swap(tableFlag, other.tableFlag);
}

/* *********************************** */

//Destructor
template <typename Data>
inline HashTableOpnAdr<Data>::~HashTableOpnAdr() {
    delete[] table;
    delete[] tableFlag;
}

/* *********************************** */

//Copy assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& other) {
    HashTable<Data>::operator=(other);
    delete[] table;
    delete[] tableFlag;
    table = new Data[tableSize] {};
    tableFlag = new Flag[tableSize] {};
    for(ulong i=0; i < tableSize; i++) {
        table[i] = other.table[i];
        tableFlag[i] = other.tableFlag[i];
    }
    return *this;
}

//Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& other) noexcept {
    HashTable<Data>::operator=(std::move(other));
    std::swap(table, other.table);
    std::swap(tableFlag, other.tableFlag);
    return *this;
}

/* *********************************** */

//Comparison operators
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data> &other) const noexcept {
    if(size != other.Size()) {
        return false;
    }

    // non mi serve verificare anche le posizioni vuote poichè ho già verificato che abbiamo lo stesso numero di elmenti validi tramite il size
    for(ulong i=0; i < tableSize; i++) {
        if(tableFlag[i] == full) {      //se la posizione continene un elemento valido quindi non canecllato o vuoto 
            if(!other.Exists(table[i])){        //controlla se esiste nell'altra tabella nella stessa posizione
                return false;
            }
        }
    }
    return true;
}

/* *********************************** */

//Specific member functions (inherited from DictionaryContainer)
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data &element) {
    //il valore porbindex mi serve per gestire le collisioni, in caso di collisione incremento il valore di prob_index 
    //per veitare di ritornare sempre sulla stessa posizione e generare cicli infiniti
    ulong prob_index = 0;   
    if(size*2 >= tableSize) {   //se la tabella è per metà piena, raddoppio la dimensione prima del nuovo inserimento
        Resize(tableSize * 2);
    }

    ulong index = FindEmpty(element, prob_index);
    if(tableFlag[index] != full){
        table[index] = element;
        tableFlag[index] = full;
        ++size;
        return !Remove(++prob_index, element); //rimuovo eventuali duplicati dell'elemento appena inserito
    }   
    prob_index = 0;
    return false;
}


template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data &&element) noexcept {
    ulong prob_index = 0;
    if(size*2 >= tableSize) {
        Resize(tableSize * 2);
    }
    ulong index = FindEmpty(element, prob_index);
    if(tableFlag[index] != full){
        table[index] = std::move(element);
        tableFlag[index] = full;
        ++size;
        return !Remove(++prob_index, element); 
    }
    prob_index = 0;
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data &element) {
    ulong index = 0;
    return Remove(index, element);
}

/* *********************************** */

//Specific member functions (inherited from TestableContainer)
template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data &element) const noexcept {
    ulong prob_index = 0;
    ulong index = HashKey(Hashable<Data>()(element));
    return Find(index, prob_index, element);
}

/* *********************************** */

// Specific member functions (inherited from ResizableContainer)
template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong new_size) {
    if(new_size == 0){
        Clear();
        return;
    }

   unsigned long tmp_size = (new_size <= 16) ? 16 : std::pow(2, std::ceil(log2(new_size)));

    Data* tmp_table = new Data[tmp_size] {};
    Flag* tmp_tableFlag = new Flag[tmp_size] {};

    std::swap(tableSize, tmp_size);
    std::swap(table, tmp_table);
    std::swap(tableFlag, tmp_tableFlag);

    size=0;
    for(ulong i=0; i < tmp_size; i++) {
        if(tmp_tableFlag[i] == full) {
            Insert(tmp_table[i]);
        }
    }
    delete[] tmp_table;
    delete[] tmp_tableFlag;
}

/* *********************************** */

// Specific member functions (inherited from ClearableContainer)
template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    for(ulong i=0; i < tableSize; i++) {
        tableFlag[i] = dirty;
    }
    size = 0;
}

/* *********************************** */

//Auxiliary member functions

//HashKey
template <typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const Data& key, ulong& porb_value) const noexcept {
    ulong index = HashKey(Hashable<Data>()(key));
    return (index + tableSize + ((porb_value * porb_value) + porb_value)/2) % tableSize;
}

//Find
template <typename Data>
bool HashTableOpnAdr<Data>::Find(ulong& index, ulong& prob_value, const Data& element) const noexcept {
    ulong jumps = 0;
    ulong tmp_index = HashKey(element, prob_value);
    do{
        if(jumps == tableSize-1)
            return false;
        if((tableFlag[tmp_index] == full) && (table[tmp_index] == element)){
            index = tmp_index;
            return true;
        }
        tmp_index = HashKey(element, ++prob_value);
        jumps++;
    }while(!(tableFlag[tmp_index] == empt));

    return false;
}

//FindEmpty
template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data& element, ulong& prob_index) const noexcept {
    ulong tmp_index = HashKey(element, prob_index);
    while((tableFlag[tmp_index] == full) && (table[tmp_index] != element)) {   //esaco dal ciclo quando trovo una posizione vuota o trovo l'elemento
        tmp_index = HashKey(element, ++prob_index);
    }
    return tmp_index;
}

//Remove
template <typename Data>
bool HashTableOpnAdr<Data>::Remove(ulong& prob_index, const Data &key) noexcept {
    ulong tmp_index;
    if(Find(tmp_index, prob_index, key)){
        tableFlag[tmp_index] = dirty;
        size--;
        prob_index = 0;
        //se la tabella è per meno di 1/5 piena dimezzo la dimensione
        if(size < (tableSize / 5)) {     
            Resize(tableSize / 2);
        }
        return true;
    }
    prob_index = 0;
    return false;
}


/* ************************************************************************** */

}
