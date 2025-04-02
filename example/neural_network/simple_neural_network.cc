#include "../../enola/nn.hpp"
#include <exception>
#include <iostream>

int main() {
  try {
    std::vector<size_t> layer_size = {
        2,  // inputs
        3,  // hidden layer
        1,  // output
    };

    enola::neural::NeuralNetwork<double> nn(layer_size);
    std::vector<double>                  input  = {0.5, 0.2};
    std::vector<double>                  target = {0.8};
    std::vector<double>                  output = nn.forward_propagation(input);

    float loss = nn.compute_loss(output, target);

    std::cout << "output: ";
    for (double val : output) {
      std::cout << val << " ";
    }
    std::cout << std::endl << "LOSS with MSE: " << loss << std::endl;
    std::cout << std::endl;
  } catch (const std::exception &error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return 0;
}
