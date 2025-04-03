#include "../../enola/ops/deep_copy.hpp"
#include <iostream>

int main() {
  int x = 42;
  int y = enola::ops::DeepCopy(x);

  std::cout << "copied the integer: " << y << std::endl;

  std::vector<int> vec         = {1, 2, 3};
  std::vector<int> vector_copy = enola::ops::DeepCopy(vec);
  std::cout << "copied vector: ";
  for (int v : vector_copy) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  auto ptr      = std::make_shared<int>(100);
  auto ptr_copy = enola::ops::DeepCopy(ptr);
  std::cout << "copied shared_ptr value: " << *ptr_copy << std::endl;

  return 0;
}
