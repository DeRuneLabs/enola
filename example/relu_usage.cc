#include "../enola/function/activation/relu.hpp"
#include <iostream>

int main() {
  std::vector<double> input  = {-1000.0, -1.0, 0.0, 1.0, 1000.0};
  std::vector<double> output = enola::function::relu(input);

  std::cout << "input: ";
  for (double x : input) {
    std::cout << x << " ";
  }

  std::cout << std::endl << "output: ";
  for (double y : output) {
    std::cout << y << " ";
  }
  std::cout << std::endl;

  return 0;
}
