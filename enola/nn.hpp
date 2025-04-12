#ifndef ENOLA_NN_HPP
#define ENOLA_NN_HPP

#include <unistd.h>

#include "function/sigmoid.hpp"
#include "score/mse.hpp"
#include "tensor/tensor_storage.hpp"
#include <memory>
#include <random>
#include <stdexcept>
#include <utility>

namespace enola {
namespace neural {

/**
 * @brief representing simple multi-layer neural network
 *
 * this class implementing feedforward neural network with arbitrary number of
 * layer it uses tensor storage for managing weights and biases and supports
 * forward propagation the sigmoid activation function is applied at each layer
 *
 * @tparam T data type use for computation
 */
template <typename T>
/**
 * @brief constructor to initialize the neural network
 *
 * intialize the neural network architecture based on the provided layer size
 * randomly initializes weights and biases for each layer using the CPU tensor
 * storage
 * @param layer_size vector specifying number of neurons in each layer eg: {2,
 * 3, 1} means 2 input neurons, 3 hidden neurons, and 1 output neuron
 * @throws std::invalid_argument if the number of layers is less than 2
 */
class NeuralNetwork {
 public:
  /**
   * @brief constructor to initialize the neural network
   *
   * initialize the neural network architecture based on the provide layer size,
   * randomly initialize weights and biases for each layer using dynamic storage
   *
   * @param layer_size vector specifying number of neurons in each layer
   *
   * @throws std::invalid_argument if the number of layers is less than 2
   */
  explicit NeuralNetwork(const std::vector<size_t>& layer_sizes)
      : layer_sizes_(layer_sizes) {
    // make sure only floating-point types are supported
    static_assert(std::is_floating_point_v<T>,
                  "only floating-point types are supported");

    // validate that are at least two layer
    if (layer_sizes.size() < 2) {
      throw std::invalid_argument("at least tow layer required");
    }

    // initialize weights and biases for each layer
    for (size_t i = 0; i < layer_sizes.size() - 1; ++i) {
      size_t input_size =
          layer_sizes[i];  // number of neurons in the current layer
      size_t output_size =
          layer_sizes[i + 1];  // number of neurons in the next layer

      // create weight tensor with shape [output_size, input_size]
      std::vector<size_t> weight_shape = {
          output_size, input_size};  // neuron in the current layer
      auto layer_weights = std::make_unique<tensor::DynamicStorage<T>>(
          weight_shape);  // neuron in the next layer

      // create bias tensor with shape [output_size]
      std::vector<size_t> bias_shape = {output_size};
      auto                layer_biases =
          std::make_unique<tensor::DynamicStorage<T>>(bias_shape);

      // randomly initialize weights and biases between [-1, 1]
      std::random_device                rd;
      std::mt19937                      gen(rd());
      std::uniform_real_distribution<T> dist(-1.0, 1.0);

      // initialize weights
      for (size_t j = 0; j < layer_weights->size(); ++j) {
        (*layer_weights)[j] = dist(gen);
      }

      // initialize biases
      for (size_t j = 0; j < layer_biases->size(); ++j) {
        (*layer_biases)[j] = dist(gen);
      }

      // store the initialized weights and biases
      weights_.emplace_back(std::move(layer_weights));
      biases_.emplace_back(std::move(layer_biases));
    }
  }

  /**
   * @brief perform forward propagation through the network
   *
   * propagate the input through all layer of the network, applying the sigmoid
   * activation function at each layer. The output of one layer becomes the
   * input to the next layer
   *
   * @param input the input vector to the network (shape [input_size])
   * @return output vector from the final layer (shape)
   *
   * @throws std::invalid_argument if the input does not match the input layer
   */
  std::vector<T> forward_propagation(const std::vector<T>& input) const {
    // validate the input size match the input layer size
    if (input.size() != layer_sizes_[0]) {
      throw std::invalid_argument(
          "input size does not match the network's input layer");
    }

    // start with the input the initial layer input
    std::vector<T> current_layer_output = input;

    // iterating trough each layer
    for (size_t i = 0; i < weights_.size(); ++i) {
      const auto& layer_weights =
          *weights_[i];  // weight for for the current layer
      const auto& layer_biases = *biases_[i];  // biases for the current layer

      // output this layer
      std::vector<T> next_layer_input(layer_biases.size());

      // computing the weighted sum for each neuron in the current layer
      for (size_t j = 0; j < layer_biases.size(); ++j) {
        T weighted_sum = layer_biases[j];  // start with the bias

        // add contributions from each input neuron
        for (size_t k = 0; k < layer_weights.size() / layer_biases.size();
             ++k) {
          weighted_sum +=
              layer_weights[j * (layer_weights.size() / layer_biases.size()) +
                            k] *
              current_layer_output[k];
        }
        // store the weighted sum for this neuron
        next_layer_input[j] = weighted_sum;
      }
      // apply the sigmoid activation function to the weighted sums
      current_layer_output = enola::function::sigmoid(next_layer_input);
    }

    // reutrn the output of the final layer
    return current_layer_output;
  }

  /**
   * @brief compute the loss between the network output and target
   *
   * this function calculate the mean squared error using MSE function
   *
   * @param output the network's output vector (predicted value)
   * @param target the target output vector (true value)
   * @return computed MSE loss as scalar value
   *
   * @throws std::invalid_argument if the output and target vector have
   * difference
   */
  double compute_loss(const std::vector<T>& output,
                      const std::vector<T>& target) const {
    // validating that output and target have the same size
    if (output.size() != target.size()) {
      throw std::invalid_argument(
          "output and target vector must have the same size");
    }

    // convert output and target vector to tensor
    std::vector<size_t> shape = {output.size()};
    auto output_tensor = std::make_unique<tensor::DynamicStorage<T>>(shape);
    auto target_tensor = std::make_unique<tensor::DynamicStorage<T>>(shape);

    for (size_t i = 0; i < output.size(); ++i) {
      output_tensor[i] = output[i];
      target_tensor[i] = target[i];
    }

    // use mse function to compute the loss
    return enola::score::mse(output_tensor, target_tensor);
  }

 private:
  std::vector<size_t>
      layer_sizes_;  // size of each layer (input, hidden, output)
  std::vector<std::unique_ptr<tensor::DynamicStorage<T>>>
      weights_;  // weights for each layer (stored as tensors
  std::vector<std::unique_ptr<tensor::DynamicStorage<T>>>
      biases_;  // biases for each layer (stored as tensors)
};
}  // namespace neural
}  // namespace enola

#endif  // !ENOLA_NN_HPP
