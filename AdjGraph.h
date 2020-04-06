#pragma once
#include "DynamicArray.h"
#include "List.h"


template <typename T>
class listGraph {
 private:
  int noOfVertices;
  dynArray<Vertex<T>> vertexes;
  List<int>* li;

 public:
  listGraph() {
    this->noOfVertices = 0;
    li = new List<int>[100];
  }
  void addVertex() {
    (li + 1)->addFront(2);
    li->addFront(4);
    (li + 1)->addFront(7);
    (li + 1)->addFront(6);
    li->addFront(3);
    li->addFront(1);
    Node<int>* tmp = new Node<int>();
    tmp = li->getHead();
    for (int i = 0; i < 3; i++) {
      std::cout << tmp->getData();
      tmp = tmp->getNext();
    }
    std::cout << "\n";
    tmp = (li+1)->getHead();
    for (int i = 0; i < 3; i++) {
      std::cout << tmp->getData();
      tmp = tmp->getNext();
    }


    std::cout << (li + 1)->getHead()->getData();
  }
};

