#pragma once
#include <iostream>

#include "Util.h"

template <typename T>
class DynamicArray {
 private:
  T* data;
  unsigned int size;
  unsigned int allocatedMem;
  bool isEmpty;
  unsigned int defaultMem = sizeof(T) * 10;

  void checkMem();
  void insertElem(T element, unsigned int index);

 public:
  // Constructors and Destructor
  DynamicArray();  // Create empty object with default memory preallocated
  DynamicArray(unsigned int nOfElems);  // Create object and preallocate memory
                                        // for given items
  DynamicArray(T* array,
               unsigned int nOfElems);  // Create object,copy data and allocate
                                        // some more memory
  ~DynamicArray();
  // Random Acces Operators
  T& operator[](unsigned int index);
  T operator[](unsigned int index) const;
  // Modifiyng Methods
  void pushBack(T element);
  void insert(T element, unsigned int index);
  void AddSize(int addedSize);
  void Resize(int resizeSize);
  void ClearAndResize(int resizeSize);
  // Getter
  unsigned int getSize() const;
};

template <typename T>
DynamicArray<T>::DynamicArray(void) {
  data = new T[defaultMem];
  allocatedMem = defaultMem;
  size = 10;
  isEmpty = true;
}

template <typename T>
DynamicArray<T>::DynamicArray(unsigned int nOfElems) {
  data = new T[nOfElems];
  allocatedMem = nOfElems;
  size = nOfElems;
  isEmpty = true;
}

template <typename T>
DynamicArray<T>::DynamicArray(T* array, unsigned int nOfElems) {
  try {
    data = new T[nOfElems + defaultMem];
    for (int i = 0; i < nOfElems; i++) {
      data[i] = array[i];
    }
  } catch (...) {
    std::cout << "DynamicArray(copy data) std::cout <<ed an exception."
              << std::endl;
  }
  allocatedMem = nOfElems + defaultMem;
  size = nOfElems;
  isEmpty = false;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  if (data != nullptr) {
    try {
      delete[] data;
    } catch (...) {
      std::cout << "~DynamicArray throwed an exception." << std::endl;
    }
  }
  data = nullptr;
}

template <typename T>
T& DynamicArray<T>::operator[](unsigned int index) {
  if (index > size - 1) {
    std::cout << "Index out of range" << std::endl;
    exit(-997);
  } else {
    isEmpty = false;
    return data[index];
  }
}

template <typename T>
T DynamicArray<T>::operator[](unsigned int index) const {
  if (index > size - 1) {
    std::cout << "Index out of range" << std::endl;
    exit(-997);
  } else {
    isEmpty = false;
    return data[index];
  }
}

template <typename T>
unsigned int DynamicArray<T>::getSize() const {
  return this->size;
}

template <typename T>
void DynamicArray<T>::checkMem() {
  if (size == allocatedMem) {
    T* temp = new T[size + defaultMem];
    for (unsigned int i = 0; i < size; i++) {
      temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    allocatedMem = size + defaultMem;
  }
}

template <typename T>
void DynamicArray<T>::insertElem(T element, unsigned int index) {
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
void DynamicArray<T>::AddSize(int addedSize) {
  T* temp = new T[size + addedSize];
  for (int i = size - 1; i >= 0; i--) {
    temp[i] = data[i];
  }
  size += addedSize;
  delete[] data;
  data = temp;
  allocatedMem = size + addedSize * sizeof(T);
}
template <typename T>
void DynamicArray<T>::Resize(int resizeSize) {
  if (resizeSize <= size) {
    std::cerr << "Size cannot be less than actual\n";
  } else {
    T* temp = new T[resizeSize];
    for (int i = 0; i < size; i++) {
      try {
        temp[i] = data[i];
      } catch (...) {
        std::cerr << "no data to copy\n";
      }
      size = resizeSize;
      delete[] data;
      data = temp;
      allocatedMem = resizeSize * sizeof(T);
    }
  }
}
template <typename T>
void DynamicArray<T>::ClearAndResize(int resizeSize) {
  delete[] data;
  data = new T[resizeSize];
  allocatedMem = resizeSize * sizeof(T);
  this->size = resizeSize;
  for (int i = 0; i < size; i++) {
    data[i] = nullptr;
  }
}

template <typename T>
void DynamicArray<T>::pushBack(T element) {
  isEmpty = false;
  this->checkMem();
  data[size] = element;
  size++;
}

template <typename T>
void DynamicArray<T>::insert(T element, unsigned int index) {
  isEmpty = false;
  if (index > size) {
    std::cout << "Index out of range" << std::endl;
  } else if (index < size) {
    this->insertElem(element, index);
  } else if (index == size) {
    this->pushBack(element);
  }
}
