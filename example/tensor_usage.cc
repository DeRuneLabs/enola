#include "../enola/tensor/tensor_storage.hpp"
#include <array>
#include <iostream>

int main() {
  std::array<std::size_t, 2> shape = {2, 2};

  tensor::Storage<double, tensor::CPU> storage(shape);
  for (std::size_t i = 0; i < storage.size(); ++i) {
    storage[i] = static_cast<double>(i + 1);
  };

  std::cout << "element at index 0: " << storage[0] << std::endl;
  std::cout << "element at index 5: " << storage[5] << std::endl;

  std::cout << "element in storage: " << std::endl;
  for (auto it = storage.begin(); it != storage.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "element in the storage (range base for loop): " << std::endl;
  for (const auto& element : storage) {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  std::size_t total_elements = tensor::num_elements(shape);
  std::cout << "total number of element in the tensor: " << total_elements << std::endl;

  return 0;
}
