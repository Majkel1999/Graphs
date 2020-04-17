#pragma once
#include <fstream>
#include <string>

#include "Edge.h"
#include "Graph.h"
#include "List.h"

class MatrixGraph : public Graph {
 private:
  Edge ***adjacencyMatrix;

 public:
  ~MatrixGraph() {
    for (int i = 0; i < numberOfVertices; i++) {
      for (int j = i; j < numberOfVertices; j++) {
        if (adjacencyMatrix[i][j] != nullptr) {
          delete adjacencyMatrix[i][j];
        }
      }
      delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
  }
  int *EndVertices(Edge *edge) {
    int *tmp = new int[2];
    tmp[0] = edge->GetStart();
    tmp[1] = edge->GetEnd();
    return tmp;
  }
  int Opposite(int vertex, Edge *edge) {
    if (edge->GetStart() == vertex) {
      return edge->GetEnd();
    } else if (edge->GetEnd() == vertex) {
      return edge->GetStart();
    } else {
      return -1;
    }
  }
  bool AreAdjacent(int vertex1, int vertex2) {
    if (adjacencyMatrix[vertex1][vertex2] != nullptr ||
        adjacencyMatrix[vertex2][vertex1] != nullptr) {
      return true;
    } else {
      return false;
    }
  }
  List<Edge> *Neighbours(int vertexIndex) {
    List<Edge> *tmp = new List<Edge>();
    for (int i = 0; i < numberOfVertices; i++) {
      if (adjacencyMatrix[vertexIndex][i] != nullptr) {
        tmp->PushBack(*adjacencyMatrix[vertexIndex][i]);
      }
    }
    return tmp;
  }
  int GetEdgeWeigth(int vertex1, int vertex2) {
    return adjacencyMatrix[vertex1][vertex2]->GetWeigth();
  }

  void InsertEdge(int vertex1, int vertex2, int weigth) {
    Edge *edge = new Edge(vertex1, vertex2, weigth);
    adjacencyMatrix[vertex1][vertex2] = edge;
    adjacencyMatrix[vertex2][vertex1] = edge;
    numberOfEdges++;
  }
  void InsertVertex(int numberOfVertices) {
    UpdateMatrix(numberOfVertices);
    this->numberOfVertices += numberOfVertices;
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
    adjacencyMatrix = new Edge **[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
      adjacencyMatrix[i] = new Edge *[numberOfVertices];
      for (int j = 0; j < numberOfVertices; j++) {
        adjacencyMatrix[i][j] = nullptr;
      }
    }
    int startIndex;
    int endIndex;
    int weigth;
    while (file >> startIndex) {
      file >> endIndex;
      file >> weigth;
      Edge *edge = new Edge(startIndex, endIndex, weigth);
      adjacencyMatrix[startIndex][endIndex] = edge;
      adjacencyMatrix[endIndex][startIndex] = edge;
    }
    file.close();
  }
  void Print() {
    for (int i = 0; i < numberOfVertices; i++) {
      for (int j = 0; j < numberOfVertices; j++) {
        if (adjacencyMatrix[i][j] == nullptr) {
          std::cout << "- ";
        } else {
          std::cout << adjacencyMatrix[i][j]->GetWeigth() << " ";
        }
      }
      std::cout << std::endl;
    }
  }

 private:
  void UpdateMatrix(int size) {
    Edge ***tmp = new Edge **[numberOfVertices + size];
    for (int i = 0; i < numberOfVertices + size; i++) {
      tmp[i] = new Edge *[numberOfVertices + size];
      for (int j = 0; j < numberOfVertices + size; j++) {
        tmp[i][j] = nullptr;
      }
    }

    for (int i = 0; i < numberOfVertices; i++) {
      for (int j = 0; j < numberOfVertices; j++) {
        tmp[i][j] = adjacencyMatrix[i][j];
      }
      delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
    adjacencyMatrix = tmp;
  }
};
