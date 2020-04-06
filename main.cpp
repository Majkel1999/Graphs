#include <iostream>

#include "DynamicArray.h"
#include "matGraph.h"

int main() {
  std::cin.get();
  MatrixGraph<int>* a = new MatrixGraph<int>("Test.txt");
  std::cin.get();
  a->SaveToFile("outputpis.txt");
  std::cin.get();
  delete a;
  std::cin.get();
  //(*(*a)[2])[1] = 1412;
}