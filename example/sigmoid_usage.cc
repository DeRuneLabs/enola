#include "../enola/function/sigmoid.hpp"
#include <iostream>

int main() {
  std::vector<float> input  = {-1.0f, 0.0f, 1.0f, 2.0f};
  std::vector<float> output = enola::function::sigmoid(input);

  std::cout << "input: ";
  for (float x : input) {
    std::cout << x << " ";
  }
  std::cout << std::endl << "output: ";
  for (float y : output) {
    std::cout << y << " ";
  }
  std::cout << std::endl;
  return 0;
}
