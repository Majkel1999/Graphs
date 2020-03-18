#pragma once
#include <iostream>
#include "Util.h"

constexpr unsigned int defaultMem = 50;

template <typename T>
class DynArray {
 private:
  T* data;
  unsigned int size;
  unsigned int allocatedMem;
  bool isEmpty;

  void checkMem();
  void insertElem(T element, unsigned int index);

 public:
  // Constructors and Destructor
  DynArray();  // Create empty object with default memory preallocated
  DynArray(unsigned int nOfElems);  // Create object and preallocate memory for
                                    // given items
  DynArray(T* array,
           unsigned int nOfElems);  // Create object,copy data and allocate some
                                    // more memory
  ~DynArray();
  // Random Acces Operators
  T& operator[](unsigned int index);
  T operator[](unsigned int index) const;
  // Modifiyng Methods
  void pushBack(T element);
  void insert(T element, unsigned int index);
   //Getter
  unsigned int getSize() const;
};

template <typename T>
DynArray<T>::DynArray(void) {
  data = new T[defaultMem];
  allocatedMem = defaultMem;
  size = 0;
  isEmpty = true;
}

template <typename T>
DynArray<T>::DynArray(unsigned int nOfElems) {
  data = new T[nOfElems];
  allocatedMem = nOfElems;
  size = nOfElems;
  isEmpty = true;
}

template <typename T>
DynArray<T>::DynArray(T* array, unsigned int nOfElems) {
  try {
    data = new T[nOfElems + defaultMem];
    for (int i = 0; i < nOfElems; i++) {
      data[i] = array[i];
    }
  } catch (...) {
    std::cout << "DynArray(copy data) throwed an exception." << std::endl;
  }
  allocatedMem = nOfElems + defaultMem;
  size = nOfElems;
  isEmpty = false;
}

template <typename T>
DynArray<T>::~DynArray() {
  try {
    delete[] data;
  } catch (...) {
    std::cout << "~DynArray throwed an exception." << std::endl;
  }
}

template <typename T>
T& DynArray<T>::operator[](unsigned int index) {
  if (index > size - 1) {
    throw "Index out of range";
  } else {
    return data[index];
  }
}

template <typename T>
T DynArray<T>::operator[](unsigned int index) const {
  if (index > size - 1) {
    throw "Index out of range";
  } else {
    return data[index];
  }
}

template <typename T>
unsigned int DynArray<T>::getSize() const{
  return this->size;
}

template <typename T>
void DynArray<T>::checkMem() {
  if (size == allocatedMem) {
    T* temp = new T[size + defaultMem];
    for (int i = 0; i < size; i++) {
      temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    allocatedMem = size + defaultMem;
  }
}

template <typename T>
void DynArray<T>::insertElem(T element, unsigned int index) {
  if (size == allocatedMem) {
    T* temp = new T[size + defaultMem];
    for (int i = size; i > index; i--) {
      temp[i] = data[i - 1];
    }
    temp[index] = element;
    for (int i = index - 1; i >= 0; i--) {
      temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    allocatedMem = size + defaultMem;
  } else {
    for (int i = size; i > index; i--) {
      data[i] = data[i - 1];
    }
    data[index] = element;
  }
  size++;
}

template <typename T>
void DynArray<T>::pushBack(T element) {
  this->checkMem();
  data[size] = element;
  size++;
}

template <typename T>
void DynArray<T>::insert(T element, unsigned int index) {
  if (index > size) {
    throw "Index out of range";
  } else if (index < size) {
    this->insertElem(element, index);
  }
  else if (index == size) {
    this->pushBack(element);
  }
}