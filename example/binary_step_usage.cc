#include "../enola/function/activation/binary_step.hpp"
#include <iostream>

int main() {
  std::vector<double> input  = {-1.0, 0.0, 1.5, -2.3};
  auto                result = enola::function::binary_step(input);

  for (const auto& value : result) {
    std::cout << value << " ";
  }

  return 0;
}
