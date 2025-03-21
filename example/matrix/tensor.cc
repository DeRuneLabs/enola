#include "../../enola/matrix/tensor.hpp"

#include <iostream>

int main() {
  tensor t(2, 3, 4);

  t(0, 0, 0) = 42;  // modify
  t(1, 2, 3) = 99;

  std::cout << "element (0, 0, 0): " << t(0, 0, 0) << std::endl;
  std::cout << "element (1, 2, 3): " << t(1, 2, 3) << std::endl;

  auto [dim1, dim2, dim3] = t.get_dimension();
  std::cout << "dimensions: " << dim1 << " x " << dim2 << " x " << dim3
            << std::endl;

  return 0;
}
