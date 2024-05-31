
namespace lasd {

/* ************************************************************************** */

//HASHABLE

template <>
class Hashable<int> {
    public:
        ulong operator()(const int & dat) const noexcept {
            return dat * dat;
        }
};

template<>
class Hashable<std::string> {
    public:
        ulong operator()(const std::string& dat) const noexcept {
            ulong hash = 0;
            for(ulong i=0; i < dat.length(); i++) {     //itero su ciascun carattere della stinga
                hash += dat[i] * i;      //sommo il valore ASCII del carattere moltiplicato per la sua posizione nella stringa
                //in questo modo pur avendo magari due stringe simili riesco a difefrenziarle poichè ogni signolo carattere 
                //in una determinata posizione contribuisce in modo diverso al calcolo dell'hash
            }
            return hash;
        }
};

template<>
class Hashable<double> {
    public:
        ulong operator()(const double& dat) const noexcept {
            ulong parteInt = floor(dat);        //mi restituise solo la parte intera
            ulong parteFraz = dat - parteInt;   //mi restituisce la parte frazionaria
            return (parteInt * parteFraz)+parteInt;
        }
};

/* ************************************************************************** */

//HASHTABLE

//Default constructor
template <typename Data>
HashTable<Data>::HashTable() {
    a = (genA(genera) * 2) + 1; //imposto a dispari
    b = std::pow(2, std::ceil(log2(genB(genera))));  //imposto b come potenza di 2 successiva al numero generato in modo randomico
}


/* ********************************************** */

//Copy constructor
template <typename Data>
HashTable<Data>::HashTable(const HashTable& other) {
    tableSize = other.tableSize;
    size = other.size;
    a = other.a;
    b = other.b;
}

//Move constructor
template <typename Data>
HashTable<Data>::HashTable(HashTable&& other) noexcept {
    std::swap(tableSize, other.tableSize);
    std::swap(size, other.size);
    std::swap(a, other.a);
    std::swap(b, other.b);
}

/* ********************************************** */

//Copy assignment
template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(const HashTable& other) {
    tableSize = other.tableSize;
    size = other.size;
    a = other.a;
    b = other.b;
    return *this;
}

//Move assignment
template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(HashTable&& other) noexcept {
    std::swap(tableSize, other.tableSize);
    std::swap(size, other.size);
    std::swap(a, other.a);
    std::swap(b, other.b);
    return *this;
}

/* ********************************************** */

// Auxiliary member functions
//presa in input una chiave la funzione restituisce il suo hash, ovvero l'indice in cui verrà inserito il dato
template <typename Data>
inline ulong HashTable<Data>::HashKey(ulong key) const noexcept {
    return (a * key + b) % tableSize;
}

/* ************************************************************************** */

}
