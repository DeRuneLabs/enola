#include "../enola/function/activation/elu.hpp"
#include <iostream>

int main() {
  try {
    std::vector<float> input = {2.3f, 0.6f, -2.0f, -3.8f};
    float              alpha = 0.3f;

    std::vector<float> output =
        enola::function::exponential_linear_unit(input, alpha);
    std::cout << "ELU output: ";
    for (float val : output) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  } catch (const std::exception& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return 0;
}
