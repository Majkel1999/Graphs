#pragma once
#include "Vertex.h"
template <typename T>
class Edge {
 private:
  Vertex<T>* startPoint = nullptr;
  Vertex<T>* endPoint = nullptr;
  int weigth;

 public:
  Edge() { weigth = 0; }
  Edge(Vertex<T>* start, Vertex<T>* end, int weigthParam) {
    this->startPoint = start;
    this->endPoint = endPoint;
    this->weigth = weigthParam;
  }
  Vertex<T>* GetStart() {
    return this->startPoint;
  }
  Vertex<T>* GetEnd() {
    return this->endPoint;
  }
  int GetWeigth() { return this->weigth; }
};