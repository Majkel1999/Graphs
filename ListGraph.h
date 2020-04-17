#pragma once
#include <fstream>

#include "Edge.h"
#include "Graph.h"
#include "List.h"

class ListGraph : public Graph {
 private:
  List<Edge>** adjacencyList;

 public:
  ~ListGraph() {
    for (int i = 0; i < numberOfVertices; i++) {
      delete adjacencyList[i];
    }
    delete[] adjacencyList;
  }
  void LoadFromFile(std::string filename) {
    std::fstream file;
    file.open(filename);
    if (!file) {
      std::cerr << "File not opened\n";
      return;
    }
    file >> numberOfEdges;
    file >> numberOfVertices;
    file >> startingVertex;
    adjacencyList = new List<Edge>*[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
      adjacencyList[i] = new List<Edge>();
    }
    int startIndex;
    int endIndex;
    int weigth;
    while (file >> startIndex) {
      file >> endIndex;
      file >> weigth;
      Edge e1 = Edge(startIndex, endIndex, weigth);
      Edge e2 = Edge(endIndex, startIndex, weigth);
      adjacencyList[startIndex]->PushBack(e1);
      adjacencyList[endIndex]->PushBack(e2);
    }
    file.close();
  }

  void Print() {
    for (int i = 0; i < numberOfVertices; i++) {
      std::cout << i << ": ";
      for (unsigned int j = 0; j < adjacencyList[i]->Size(); j++) {
        std::cout << (*adjacencyList[i])[j].GetEnd() << "  ";
      }
      std::cout << std::endl;
    }
  }

  List<Edge>* Neighbours(int vertexIndex) {
    List<Edge>* tmp = new List<Edge>();
    for (unsigned int i = 0; i < adjacencyList[vertexIndex]->Size(); i++) {
      tmp->PushBack((*adjacencyList[vertexIndex])[i]);
    }
    return tmp;
  }
  int GetEdgeWeigth(int vertex1, int vertex2) {
    for (unsigned int i = 0; i < adjacencyList[vertex1]->Size(); i++) {
      if ((*adjacencyList[vertex1])[i].GetEnd() == vertex2) {
        return (*adjacencyList[vertex1])[i].GetWeigth();
      }
    }
    return 0;
  }
};
