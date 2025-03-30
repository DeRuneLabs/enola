#include "../enola/tensor/ops.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>

int main() {
  std::vector<std::size_t> shape = {2, 3};

  enola::tensor::Storage<int, enola::tensor::CPU> tensor1(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> tensor2(shape);

  for (std::size_t i = 0; i < tensor1.size(); ++i) {
    tensor1[i] = static_cast<int>(i + 1);
  }

  for (std::size_t i; i < tensor2.size(); ++i) {
    tensor2[i] = static_cast<int>(6 - i);
  }

  auto result_add = enola::tensor::add(tensor1, tensor2);
  std::cout << "add result: ";
  for (std::size_t i = 0; i < result_add.size(); ++i) {
    std::cout << result_add[i] << " ";
  }
  std::cout << std::endl;

  auto result_sub = enola::tensor::subtract(tensor1, tensor2);
  std::cout << "sub result: ";
  for (std::size_t i = 0; i < result_sub.size(); ++i) {
    std::cout << result_sub[i] << " ";
  }
  std::cout << std::endl;

  auto result_mul = enola::tensor::multiply(tensor1, tensor2);
  std::cout << "mul result: ";
  for (std::size_t i = 0; i < result_mul.size(); ++i) {
    std::cout << result_mul[i] << " ";
  }
  std::cout << std::endl;

  auto result_div = enola::tensor::divide(tensor1, tensor2);
  std::cout << "div result: ";
  for (std::size_t i = 0; i < result_div.size(); ++i) {
    std::cout << result_div[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
