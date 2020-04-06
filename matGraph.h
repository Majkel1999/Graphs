#pragma once
#include <fstream>
#include <string>

#include "DynamicArray.h"
#include "Edge.h"
#include "Vertex.h"

template <typename T>
class MatrixGraph {
 private:
  int numberOfVertices = 0;
  int numberOfEdges = 0;
  int startingVertex = 0;
  DynamicArray<Vertex<T>*> vertices;
  DynamicArray<DynamicArray<Edge<T>*>*>* adjacencyMatrix = nullptr;

 public:
  MatrixGraph(std::string fileName) { LoadFromFile(fileName); }
  ~MatrixGraph() {
    for (int i = 0; i < numberOfVertices; i++) delete (*adjacencyMatrix)[i];
    delete[] adjacencyMatrix;
    // delete[] vertices;
  }
  void SaveToFile(std::string fileName) {
    std::ofstream file;
    try {
      file.open(fileName);
    } catch (...) {
      std::cerr << "Zapis do pliku nie powiód³ siê\n";
      exit(-998);
    }
    file << numberOfVertices << " " << numberOfEdges << " " << startingVertex
         << std::endl;
    for (int i = 0; i < adjacencyMatrix->getSize(); i++) {
      for (int j = 0; j < adjacencyMatrix->getSize(); j++) {
        if ((*(*adjacencyMatrix)[i])[j] != nullptr) {
          file << (*(*adjacencyMatrix)[i])[j]->GetWeigth();
          file << " ";
        } else {
          file << "-";
          file << " ";
        }
      }
      file << std::endl;
    }
    file.close();
  }
  void InsertVertex(Vertex<T>* vertex) {
    numberOfVertices++;
    vertices.pushBack(vertex);
    for (int i = 0; i < numberOfVertices - 1; i++) {
      (*adjacencyMatrix)[i]->pushBack(nullptr);
    }
    adjacencyMatrix->pushBack(new DynamicArray<Edge<T>*>(numberOfVertices));
    for (int i = 0; i < numberOfVertices; i++) {
      (*(*adjacencyMatrix)[numberOfVertices - 1])[i] = nullptr;
    }
  }
  void InsertEdge(int start, int end, int weigth) {
    numberOfEdges++;
    (*(*adjacencyMatrix)[start])[end] =
        new Edge<T>(vertices[start], vertices[end], weigth);
  }

 private:
  void LoadFromFile(std::string fileName) {
    std::ifstream file;

    try {
      file.open(fileName);
    } catch (...) {
      std::cerr << "Otwarcie pliku nie powiod³o siê\n";
      exit(-999);
    }
    file >> this->numberOfEdges;
    file >> this->numberOfVertices;
    file >> this->startingVertex;
    adjacencyMatrix =
        new DynamicArray<DynamicArray<Edge<T>*>*>[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
      adjacencyMatrix->pushBack(new DynamicArray<Edge<T>*>(numberOfVertices));
      vertices.pushBack(new Vertex<T>());
    }
    for (int i = 0; i < numberOfVertices; i++) {
      for (int j = 0; j < numberOfVertices; j++) {
        (*(*adjacencyMatrix)[i])[j] = nullptr;
      }
    }
    int tmpX, tmpY, weight;
    while (file >> tmpX) {
      file >> tmpY;
      file >> weight;
      (*(*adjacencyMatrix)[tmpX])[tmpY] =
          new Edge<T>(vertices[tmpX], vertices[tmpY], weight);
    }
    file.close();
  }
};
