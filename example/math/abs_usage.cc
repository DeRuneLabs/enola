#include "../../enola/math/abs.hpp"
#include <iostream>

int main() {
  std::vector<std::size_t> shape = {2, 3};

  enola::tensor::Storage<int, enola::tensor::CPU> tensor(shape);
  tensor[0] = -1;
  tensor[1] = 2;
  tensor[2] = -3;
  tensor[3] = 4;
  tensor[4] = -5;
  tensor[5] = 6;

  auto abs_tensor = enola::math::abs(tensor);

  std::cout << "absolute the value: " << std::endl;
  for (std::size_t i = 0; i < abs_tensor.size(); ++i) {
    std::cout << abs_tensor[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
