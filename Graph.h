#pragma once
#include "List.h"
class Graph {
 protected:
  int numberOfVertices = 0;
  int numberOfEdges = 0;
  int startingVertex = 0;

 public:
  int GetVertices() { return numberOfVertices; }
  int GetEdges() { return numberOfEdges; }
  int GetStartingVertex() { return startingVertex; } 
  virtual List<int>* Neighbours(int vertexIndex) {
    List<int>* tmp = new List<int>();
    return tmp;
  }
  virtual int GetEdgeWeigth(int vertex1, int vertex2) { return 0; }
  };