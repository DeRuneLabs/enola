#include "../enola/function/activation/binary_step.hpp"
#include <exception>
#include <iostream>

int main() {
  try {
    std::vector<double> input  = {-1.2, 0, 2, 1.45, -3.7, 0.3};
    std::vector<int>    result = enola::function::binary_step(input);
    std::cout << "result: ";
    for (int value : result) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  } catch (const std::exception &error) {
    std::cerr << "Error " << error.what() << std::endl;
  }

  return 0;
}
