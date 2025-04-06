#include "../../enola/score/msle.hpp"
#include <exception>
#include <iostream>

int main() {
  std::vector<double> y_true = {1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> y_pred = {0.8, 2.1, 2.9, 4.2, 5.2};

  try {
    double msle = enola::score::mean_squared_logarithmic_error(y_true, y_pred);
    std::cout << "MSLE: " << msle << std::endl;
  } catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << std::endl;
  }

  return 0;
}
