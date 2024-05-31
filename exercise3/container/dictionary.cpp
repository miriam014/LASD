
namespace lasd {

/* ************************************************************************** */

//True if all are inserted
template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &cont) {
  bool result = true;
  cont.Traverse(
    [this, &result](const Data &dato) {
    result &= this->Insert(dato);
    }
  );
  return result;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&cont) {
  bool result = true;
  cont.Map(
    [this, &result](const Data &dato) {
    result &= this->Insert(std::move(dato));
    }
  );
  return result;
}

//True if all are removed
template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &cont) {
  bool result = true;
  cont.Traverse(
    [this, &result](const Data &dato) {
      result &= this->Remove(dato);
    }
  );
  return result;
}


//True if some is inserted
template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &cont) {
  bool result = false;
  cont.Traverse(
    [this, &result](const Data &dato) {
    result |= this->Insert(dato);
    }
  );
  return result;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&cont) {
  bool result = false;
  cont.Map(
    [this, &result](const Data &dato) {
    result |= this->Insert(std::move(dato));
    }
  );
  return result;
}


//True if some is removed
template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &cont) {
  bool result = false;
  cont.Traverse(
    [this, &result](const Data &dato) {
    result |= this->Remove(dato);
    }
  );
  return result;
}

/* ************************************************************************** */

}