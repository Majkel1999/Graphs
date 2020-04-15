#pragma once
#include <fstream>

#include "DynamicArray.h"
#include "Edge.h"
#include "Graph.h"
#include "List.h"

class ListGraph : public Graph {
 private:
  List<Edge*>* adjacencyList;

 public:
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
    adjacencyList = new List<Edge*>[numberOfVertices];
    int startIndex;
    int endIndex;
    int weigth;
    while (file >> startIndex) {
      file >> endIndex;
      file >> weigth;
      adjacencyList[startIndex].PushBack(new Edge(startIndex, endIndex, weigth));
      adjacencyList[endIndex].PushBack(new Edge(endIndex, startIndex, weigth));
    }
    file.close();
  }

  void Print() {
    for (int i = 0; i < numberOfVertices; i++) {
      std::cout << i << ": ";
      for (unsigned int j = 0; j < adjacencyList[i].Size(); j++) {
        std::cout << adjacencyList[i][j]->GetEnd() << "  ";
      }
      std::cout << std::endl;
    }
  }

  List<int>* Neighbours(int vertexIndex) {
    List<int>* tmp = new List<int>();
    for (unsigned int i = 0; i < adjacencyList[vertexIndex].Size(); i++) {
      tmp->PushBack((adjacencyList[vertexIndex])[i]->GetEnd());
    }
    return tmp;
  }
  int GetEdgeWeigth(int vertex1, int vertex2) {
    for (unsigned int i = 0; i < adjacencyList[vertex1].Size(); i++) {
      if (adjacencyList[vertex1][i]->GetEnd() == vertex2 ||
          adjacencyList[vertex1][i]->GetEnd() == vertex1) {
        return adjacencyList[vertex1][i]->GetWeigth();
      }
    }
    return 0;
  }
};
