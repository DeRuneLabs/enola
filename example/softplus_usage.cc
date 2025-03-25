#include "../enola/function/activation/softplus.hpp"
#include <exception>
#include <iostream>
#include <vector>

int main() {
  try {
    std::vector<double> input  = {2.3, 0.6, -2.0, -3.8};
    auto                result = enola::function::softplus(input);
    std::cout << "result softplus function: ";
    for (auto val : result) {
      std::cout << val << " ";
    }
    std::cout << std::endl;

    double raw_input[] = {-9.2, -0.3, 0.45, -4.56};
    size_t size        = sizeof(raw_input) / sizeof(raw_input[0]);
    auto   ptr_result  = enola::function::softplus(raw_input, size);
    std::cout << "softplus result: ";
    for (size_t i = 0; i < size; ++i) {
      std::cout << (*ptr_result)[i] << " ";
    }
    std::cout << std::endl;
  } catch (const std::exception& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return 0;
}
