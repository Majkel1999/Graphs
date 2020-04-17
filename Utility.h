#pragma once
#include <time.h>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Graph.h"
#include "List.h"
template <typename T>
void swap(T& s1, T& s2) {
  T temp = s1;
  s1 = s2;
  s2 = temp;
}

double Djikstra(Graph* graph, bool ToFile) {
  int numberOfVertices = graph->GetVertices();
  int numberOfEdges = graph->GetEdges();
  int startingIndex = graph->GetStartingVertex();
  unsigned int* distance = new unsigned int[numberOfVertices];
  int* previousVertex = new int[numberOfVertices];
  List<int> queued, solved;
  bool* isQueued = new bool[numberOfVertices];
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < numberOfVertices; i++) {
    queued.PushBack(i);
    distance[i] = 0xffffffff;
    previousVertex[i] = -1;
    isQueued[i] = true;
  }
  distance[startingIndex] = 0;

  while (!queued.IsEmpty()) {
    unsigned int cost = 0xffffffff;
    int workingVertex = 0;
    int indexInList = 0;
    for (unsigned int i = 0; i < queued.Size(); i++) {
      if (distance[queued[i]] < cost) {
        cost = distance[queued[i]];
        workingVertex = queued[i];
        indexInList = i;
      }
    }
    solved.PushBack(queued.PullOut(indexInList));
    isQueued[solved[solved.Size() - 1]] = false;
    List<Edge>* neighbours = graph->Neighbours(workingVertex);

    while (!neighbours->IsEmpty()) {
      Edge neighbouringEdge = neighbours->PopFront();
      int neighbouringVertex = neighbouringEdge.GetEnd();
      unsigned int i = 0;
      if (!isQueued[neighbouringVertex]) {
        continue;
      } else {
        unsigned int alterantive =
            distance[workingVertex] + neighbouringEdge.GetWeigth();
        if (distance[neighbouringVertex] > alterantive) {
          distance[neighbouringVertex] = alterantive;
          previousVertex[neighbouringVertex] = workingVertex;
        }
      }
    }
    delete neighbours;
  }
  auto stop = std::chrono::high_resolution_clock::now();
  if (ToFile) {
    std::ofstream file;
    std::string s1;
    std::cout << "Podaj nazwe pliku do zapisu: ";
    std::cin >> s1;
    std::cout << std::endl;
    file.open(s1);
    if (!file) {
      throw "File not opened!";
    }
    for (int i = 0; i < numberOfVertices; i++) {
      file << i << "<-";
      int tmp = previousVertex[i];
      if (tmp == -1) {
        file << "Poczatek sciezki";
      } else {
        file << tmp << "<-";
      }
      while (tmp != -1) {
        tmp = previousVertex[tmp];
        if (tmp == -1) {
          file << "Poczatek sciezki";
        } else {
          file << tmp << "<-";
        }
      }
      file << "    Laczny koszt:" << distance[i];
      file << std::endl << std::endl;
    }
    file << "Czas wykonywania algorytmu: "
         << std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
                .count()
         << "us";
    file.close();
  }
  delete[] distance;
  delete[] previousVertex;
  return (std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
              .count());
}

void GenerateGraph(int size, float density, std::string filename) {
  srand(time(NULL));
  int numberOfEdges;
  int** tmp;
  if (density == 1) {
    numberOfEdges = size * ((size - 1) / 2);
    tmp = new int*[size];
    for (int i = 0; i < size; i++) {
      tmp[i] = new int[size];
      for (int j = 0; j < size; j++) {
        if (j == i) {
          tmp[i][j] = 0;
        } else {
          tmp[i][j] = 1;
        }
      }
    }
  } else {
    numberOfEdges = size * ((size - 1) / 2) * density;
    tmp = new int*[size];
    for (int i = 0; i < size; i++) {
      tmp[i] = new int[size];
      for (int j = 0; j < size; j++) {
        tmp[i][j] = 0;
      }
    }
    for (int i = 0; i < size; i++) {
      tmp[i][0] = 1;
      tmp[0][i] = 1;
    }
    for (int i = size; i < numberOfEdges; i++) {
      int x1 = rand() % size;
      int x2 = rand() % size;
      while (x1 == x2) {
        x2 = rand() % size;
      }
      while (tmp[x1][x2] == 1) {
        x1 = rand() % size;
        x2 = rand() % size;
        while (x1 == x2) {
          x2 = rand() % size;
        }
      }
      tmp[x1][x2] = 1;
      tmp[x2][x1] = 1;
    }
  }
  std::ofstream file;
  file.open(filename);
  if (!file) {
    std::cerr << "Problem\n";
    return;
  }
  file << numberOfEdges << " " << size << " " << rand() % size << std::endl;
  for (int i = 0; i < size; i++) {
    for (int j = i; j < size; j++) {
      if (tmp[i][j] == 1) {
        file << i << " " << j << " " << rand() % 50 << std::endl;
      }
    }
  }
  file.close();
  for (int i = 0; i < size; i++) {
    delete[] tmp[i];
  }
  delete[] tmp;
}