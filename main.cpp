#include <iostream>

#include "DynamicArray.h"
#include "matGraph.h"

int main() {
  std::cin.get();
  MatrixGraph<int>* a = new MatrixGraph<int>("Test.txt");
  a->InsertEdge(4, 5, 20);
  a->InsertEdge(9, 9, 10);
  Vertex<int>* tmp = new Vertex<int>();
  a->InsertVertex(tmp);
  a->InsertEdge(10,10,4);
  std::cin.get();
  a->SaveToFile("outputpis.txt");
  std::cin.get();
  delete a;
  std::cin.get();
  //(*(*a)[2])[1] = 1412;
}