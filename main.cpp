#include <iostream>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Utility.h"

float density[] = {0.25, 0.5, 0.75, 1};
int sizes[] = {10, 50, 100, 500, 1000};

void Test() {
  std::ofstream file;
  file.open("Wyniki.csv");
  for (int k = 0; k < 4; k++) {
    for (int j = 0; j < 5; j++) {
      double timeList = 0;
      double timeMatrix = 0;
      for (int i = 0; i < 100; i++) {
        GenerateGraph(sizes[j], density[k], "test.txt");
        MatrixGraph matrixGraph;
        ListGraph listGraph;
        matrixGraph.LoadFromFile("test.txt");
        timeMatrix += Djikstra(&matrixGraph, false);
        listGraph.LoadFromFile("test.txt");
        timeList += Djikstra(&listGraph, false);
      }
      file << "Matrix;" << density[k] << ";" << sizes[j] << ";" << timeMatrix;
      file << ";;List;" << density[k] << ";" << sizes[j] << ";" << timeList;
      file << std::endl;
      std::cout << "size:" << sizes[j] << " density:" << density[k] * 100
                << "% time: " << timeMatrix << " time : " << timeList;
      ;
      std::cout << std::endl;
    }
  }
  file.close();
}

int main() {
  //GenerateGraph(500, 0.25, "1.txt");
  MatrixGraph a;
  a.LoadFromFile("c50d25x39.txt");
  std::cout << Djikstra(&a,true);
  std::cin.get();
  //Test();
}
