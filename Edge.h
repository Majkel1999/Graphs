#pragma once
#include "Vertex.h"
class Edge {
 private:
  int startPoint = -1;
  int endPoint = -1;
  int weigth = -1;

 public:
  Edge() { weigth = 0; }
  Edge(int start, int end, int weigthParam) {
    this->startPoint = start;
    this->endPoint = end;
    this->weigth = weigthParam;
  }
  int GetStart() { return this->startPoint; }
  int GetEnd() { return this->endPoint; }
  int GetWeigth() { return this->weigth; }
};