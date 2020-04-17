#pragma once
template <typename T>
class Node {
 private:
  T element;
  Node<T>* nextPtr;
  Node<T>* previousPtr;

 public:
  Node() {}
  Node(T elem) {
    this->element = elem;
    this->nextPtr = nullptr;
    this->previousPtr = nullptr;
  }

  T GetData() { return this->element; }
  T* GetDataPointer() { return &(this->element); }
  void SetData(T elem) { this->element = elem; }
  Node<T>* GetNext() { return this->nextPtr; }
  void SetNext(Node<T>* elem) { this->nextPtr = elem; }
  Node<T>* GetPrevious() { return this->previousPtr; }
  void SetPrevious(Node<T>* elem) { this->previousPtr = elem; }
};

template <typename T>
class List {
 private:
  Node<T>* head;
  Node<T>* tail;
  unsigned int size = 0;

 public:
  List() {
    this->head = nullptr;
    this->tail = nullptr;
  }
  List(T elem) {
    Node<T>* tmp = new Node<T>(elem);
    this->head = tmp;
    this->tail = this->head;
    size = 1;
  }
  ~List() {
    if (!this->IsEmpty()) {
      while (this->head!=this->tail) {
        Node<T>* tmp = this->head->GetNext();
        delete this->head;
        this->head = tmp;
      }
      delete this->head;
    }
  }
  void Clear() {
    if (!this->IsEmpty()) {
      while (this->head->GetNext() != nullptr) {
        Node<T>* tmp = this->head->GetNext();
        delete this->head;
        this->head = tmp;
      }
      delete this->head;
    }
    size = 0;
  }
  T operator[](unsigned int index) {
    if (!this->IsEmpty()) {
      if (index < this->Size()) {
        Node<T>* tmp = this->head;
        while (index != 0) {
          tmp = tmp->GetNext();
          index--;
        }
        return tmp->GetData();
      } else {
        throw "Index out of range";
      }
    } else {
      throw "List is empty";
    }
  }
  Node<T>* GetNode(unsigned int index) {
    if (!this->IsEmpty()) {
      if (index < this->Size()) {
        Node<T>* tmp = this->head;
        while (index != 0) {
          tmp = tmp->GetNext();
          index--;
        }
        return tmp;
      } else {
        throw "Index out of range\n";
        return nullptr;
      }
    } else {
      throw "List is empty\n";
      return nullptr;
    }
  }
  bool IsEmpty() {
    if (head == nullptr) {
      return true;
    } else {
      return false;
    }
  }
  unsigned int Size() { return size;
  }
  void PushFront(T elem) {
    if (!this->IsEmpty()) {
      Node<T>* tmp = new Node<T>(elem);
      tmp->SetNext(this->head);
      this->head->SetPrevious(tmp);
      this->head = tmp;
    } else {
      this->head = new Node<T>(elem);
      this->tail = this->head;
    }
    size++;
  }
  T PopFront() {
    if (!this->IsEmpty()) {
      Node<T> tmp = *this->head;
      if (this->Size() > 1) {
        delete this->head;
        this->head = tmp.GetNext();
        this->head->SetPrevious(nullptr);
      } else {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
      }
      size--;
      return tmp.GetData();
    } else {
      throw "List is empty\n";
    }
  }
  void Insert(T elem, unsigned int index) {
    if (!this->IsEmpty()) {
      if (index == 0) {
        this->PushFront(elem);
      } else if (index == this->Size()-1) {
        this->PushBack(elem);
      } else if (index < this->Size()-1) {
        Node<T>* prev = this->head;
        while (index > 1) {
          prev = prev->GetNext();
          index--;
        }
        Node<T>* next = prev->GetNext();
        Node<T>* tmp = new Node<T>(elem);
        prev->SetNext(tmp);
        tmp->SetPrevious(prev);
        tmp->SetNext(next);
        next->SetPrevious(tmp);
      }
      size++;
    } else if (index == 0) {
      this->PushFront(elem);
      size++;
    } else {
      throw "List is empty and index > 0\n";
    }
  }
  void Remove(int index) {
    if (!this->IsEmpty()) {
      if (index == 0) {
        this->PopFront();
      } else if (index == this->Size()-1) {
        this->PopBack();
      } else if (index < this->Size()-1) {
        Node<T>* tmp = this->head;
        while (index > 0) {
          tmp = tmp->GetNext();
          index--;
        }
        Node<T>* next = tmp->GetNext();
        Node<T>* prev = tmp->GetPrevious();
        prev->SetNext(next);
        next->SetPrevious(prev);
        delete tmp;
      }
      size--;
    } else {
      throw "List is empty and index > 0\n";
    }
  }
  T PullOut(unsigned int index) {
    if (!this->IsEmpty()) {
      if (index == 0) {
        return this->PopFront();
      } else if (index == this->Size()-1) {
        return this->PopBack();
      } else if (index < this->Size()-1) {
        Node<T>* tmp = this->head;
        while (index > 0) {
          tmp = tmp->GetNext();
          index--;
        }
        Node<T>* next = tmp->GetNext();
        Node<T>* prev = tmp->GetPrevious();
        prev->SetNext(next);
        next->SetPrevious(prev);
        T holder = tmp->GetData();
        delete tmp;
        size--;
        return holder;
      }
    } else {
      throw "List is empty and index > 0\n";
    }
  }
  void PushBack(T elem) {
    if (!this->IsEmpty()) {
      Node<T>* tmp = new Node<T>(elem);
      tmp->SetPrevious(this->tail);
      this->tail->SetNext(tmp);
      this->tail = tmp;
    } else {
      this->head = new Node<T>(elem);
      this->tail = this->head;
    }
    size++;
  }
  T PopBack() {
    if (!this->IsEmpty()) {
      Node<T> tmp = *(this->tail);
      if (this->Size() > 1) {
        delete this->tail;
        this->tail = tmp.GetPrevious();
        this->tail->SetNext(nullptr);
      } else {
        delete this->tail;
        this->tail = nullptr;
        this->head = nullptr;
      }
      size--;
      return tmp.GetData();
    } else {
      throw "List is empty\n";
    }
  }
  void Modify(int index, T elem) {
    if (!this->IsEmpty()) {
      if (index < this->size()) {
        Node<T>* tmp = this->head;
        while (index > 0) {
          tmp = tmp->GetNext();
          index--;
        }
        tmp->SetData(elem);
      } else {
        throw "Index out of range\n";
      }
    } else {
      throw "List is empty\n";
    }
  }
  T* Find(T elem) {
    if (!this->IsEmpty()) {
      Node<T>* tmp = this->head;
      int index = 0;
      while (index < this->Size()) {
        if (tmp->GetData() == elem) {
          return tmp;
        } else {
          return nullptr;
        }
      }
    }
    return nullptr;
  }
};
