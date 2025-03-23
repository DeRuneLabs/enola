#include "../enola/function/activation/relu.hpp"
#include <iostream>

int main() {
  std::vector<float> input = {-1.0f, 0.0f, 1.0f, 2.0f};
  auto output = enola::function::relu_derivative(input);
  
  std::cout << "ReLU derivative output: " << std::endl;
  for (const auto& value : output) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
  return 0;
}
