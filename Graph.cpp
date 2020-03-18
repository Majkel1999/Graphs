#include "DynamicArray.h"

int main() {
	
	DynArray<int>* dyn = new DynArray<int>();
  for (int i = 0; i < 100; i++) {
          dyn->pushBack(i);
  }
  dyn->insert(999999, 50);
  (*dyn)[2] = 999;
  for (int i = 0; i < dyn->getSize(); i++) {
    std::cout << (*dyn)[i] << std::endl;
  }

}