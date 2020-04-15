#pragma once
#include <time.h>

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

void Djikstra(Graph* graph) {
  int numberOfVertices = graph->GetVertices();
  int numberOfEdges = graph->GetEdges();
  int startingIndex = graph->GetStartingVertex();
  unsigned int* distance = new unsigned int[numberOfVertices];
  int* previousVertex = new int[numberOfVertices];
  List<int> queued, solved;

  for (int i = 0; i < numberOfVertices; i++) {
    queued.PushBack(i);
    distance[i] = 0xffffffff;
    previousVertex[i] = -1;
  }
  distance[startingIndex] = 0;

  while (!queued.IsEmpty()) {
    int cost = 0xffffffff;
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

    List<int>* neighbours = graph->Neighbours(workingVertex);

    while (!neighbours->IsEmpty()) {
      int neighbouringVertex = neighbours->PopFront();
      unsigned int i = 0;
      bool isQueued = false;
      while (i < queued.Size()) {
        if (neighbouringVertex == queued[i]) {
          isQueued = true;
          break;
        }
        i++;
      }
      if (!isQueued) {
        continue;
      } else {
        int alterantive =
            distance[workingVertex] +
            graph->GetEdgeWeigth(workingVertex, neighbouringVertex);
        if (distance[neighbouringVertex] > alterantive) {
          distance[neighbouringVertex] = alterantive;
          previousVertex[neighbouringVertex] = workingVertex;
        }
      }
    }
  }
  for (int i = 0; i < numberOfVertices; i++) {
    std::cout << std::setw(6) << i;
  }
  std::cout << std::endl << std::endl;
  for (int i = 0; i < numberOfVertices; i++) {
    if (distance[i] == 0xffffffff) {
      std::cout << std::setw(6) << "-";
    } else {
      std::cout << std::setw(6) << distance[i];
    }
  }
  std::cout << std::endl;
  for (int i = 0; i < numberOfVertices; i++) {
    if (previousVertex[i] == -1) {
      std::cout << std::setw(6) << "-";
    } else {
      std::cout << std::setw(6) << previousVertex[i];
    }
  }
  std::cout << std::endl;
  delete[] distance;
  delete[] previousVertex;
}

void GenerateGraph(int size, float density, std::string filename) {
  srand(time(NULL));
  int numberOfEdges = size * ((size - 1) / 2) * density;
  int** tmp = new int*[size];
  for (int i = 0; i < size; i++) {
    tmp[i] = new int[size];
    for (int j = 0; j < size; j++) {
      tmp[i][j] = 0;
    }
  }
  for (int i = 0; i < size - 1; i++) {
    tmp[i][i + 1] = 1;
    tmp[i + 1][i] = 1;
  }
  for (int i = size - 1; i < numberOfEdges; i++) {
    int x1 = rand() % size;
    int x2 = rand() % size;
    while (x1 == x2) {
      x2 = rand() % size;
    }
    while (tmp[x1][x2] == 1) {
      int x1 = rand() % size;
      int x2 = rand() % size;
      while (x1 == x2) {
        x2 = rand() % size;
      }
    }
    tmp[x1][x2] = 1;
    tmp[x2][x1] = 1;
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