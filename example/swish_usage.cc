#include "../enola/function/activation/swish.hpp"
#include <iostream>

int main() {
  std::vector<float> input = {-1.0f, 1.0f, 2.0f};
  float              beta  = 2.0f;

  std::vector<float> output = enola::function::swish(input, beta);

  std::cout << "output from function swish: ";
  for (float val : output) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  return 0;
}
