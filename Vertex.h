#pragma once
template <typename T>
class Vertex {
 private:
  T data;

 public:
  Vertex() { data = 0; };
  Vertex(T dataParam) { this->data = dataParam; };
  void SetData(T param) { this->data = param; };
  T GetData() { return data; };
};
