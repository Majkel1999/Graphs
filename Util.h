#pragma once
template <typename T>
void swap(T& s1, T& s2) {
  T temp = s1;
  s1 = s2;
  s2 = temp;
}