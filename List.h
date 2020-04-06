#pragma once
template <typename T>
class Node {
 private:
  T data;
  Node<T>* nextPtr;

 public:
  Node() {}
  Node(T elem) {
    data = elem;
    nextPtr = nullptr;
  }

  T& getData() { return this->data; }
  void setData(T elem) { this->data = elem; }
  Node<T>* getNext() const { return this->nextPtr; }
  void setNext(Node<T>* elem) { this->nextPtr = elem; }
};

template <typename T>
class List {
 private:
  Node<T>* head;
  Node<T>* tail;

 public:
  List() {
    this->head = nullptr;
    this->tail = nullptr;
  }
  List(Node<T> elem) {
    this->head = elem;
    this->tail = this->head;
  }
  ~List() {
    while (this->head->getNext() != nullptr) {
      Node<T>* tmp = this->head->getNext();
      delete this->head;
      this->head = tmp;
    }
    delete this->head;
  }
  Node<T>* getHead() { return this->head; }
  void addBack(T elem) {
    if (this->head != nullptr) {
      this->tail->setNext(new Node<T>(elem));
      this->tail = this->tail->getNext();
    } else {
      this->head = new Node<T>(elem);
      this->tail = this->head;
    }
  }
  void addFront(T elem) {
    Node<T>* tmp = new Node<T>(elem);
    tmp->setNext(this->head);
    this->head = tmp;
  }
};
