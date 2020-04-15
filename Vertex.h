#pragma once
#include "List.h"
template <typename T>
class Vertex {
 private:
  Node<Vertex<T>>* listPtr = nullptr;
  T data;

 public:
  Vertex() { data = 0; };
  Vertex(T dataParam) { this->data = dataParam; }
  void SetData(T param) { this->data = param; }
  T GetData() { return data; }
  void SetPointer(Node<Vertex<T>>* ptr) { this->listPtr = ptr; }
  Node<Vertex<T>>* GetPointer() { return this->listPtr; }
};
