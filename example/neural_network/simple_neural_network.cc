#include "../../enola/function/sigmoid.hpp"
#include <iostream>
#include <random>

template <typename T>
T forward_propagation(T expected, size_t number_propagations, T initial_value) {
  static_assert(std::is_floating_point_v<T>,
                "only floating point types are support");

  if (number_propagations == 0) {
    throw std::invalid_argument("number propagation must greater than zero");
  }
  if (expected <= 0 || initial_value <= 0) {
    throw std::invalid_argument("expected and initial value must be positive");
  }

  std::random_device                rd;
  std::mt19937                      gen(rd());
  std::uniform_real_distribution<T> dist(-1.0, 1.0);
  T                                 weight = dist(gen);

  for (size_t i = 0; i < number_propagations; ++i) {
    std::vector<T> input_vector  = {initial_value * weight};
    T              layer_1       = enola::function::sigmoid(input_vector)[0];
    T              layer_1_error = (expected / 100.0) - layer_1;
    T              layer_1_detla = layer_1_error * layer_1 * (1.0 - layer_1);
    weight += initial_value * layer_1_detla;
  }

  std::vector<T> final_input_vector = {initial_value * weight};
  return enola::function::sigmoid(final_input_vector)[0] * 100.0;
}

int main() {
  try {
    double target_value        = 32.0;
    size_t number_propagations = 450000;
    double initial_value       = 1.0;

    double result =
        forward_propagation(target_value, number_propagations, initial_value);
    std::cout << "final output: " << result << std::endl;

    if (result > 31.0 && result < 33.0) {
      std::cout << "test passing" << std::endl;
    } else {
      std::cout << "test fail" << std::endl;
    }
  } catch (const std::exception &error) {
    std::cout << "error: " << error.what() << std::endl;
  }

  return 0;
}
