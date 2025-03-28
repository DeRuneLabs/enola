#include "../enola/nn.hpp"

#include <gtest/gtest.h>

TEST(NeuralNetworkTest, SingleLayerNetwork) {
  std::vector<size_t>                  layer_size = {1, 1};
  enola::neural::NeuralNetwork<double> nn(layer_size);

  std::vector<double> input  = {0.5};
  std::vector<double> output = nn.forward_propagation(input);

  ASSERT_EQ(output.size(), 1);
  EXPECT_GE(output[0], 0.0);
  EXPECT_LE(output[0], 1.0);
}

TEST(NeuralNetworkTest, MultiLayerNetwork) {
  std::vector<size_t>                  layer_size = {2, 3, 1};
  enola::neural::NeuralNetwork<double> nn(layer_size);

  std::vector<double> input  = {0.5, 0.8};
  std::vector<double> output = nn.forward_propagation(input);

  ASSERT_EQ(output.size(), 1);

  EXPECT_GE(output[0], 0.0);
  EXPECT_LE(output[0], 1.0);
}

TEST(NeuralNetworkTest, InvalidInput) {
  std::vector<size_t> layer_size = {2, 3, 1};
  enola::neural::NeuralNetwork<double> nn(layer_size);
  
  std::vector<double> input = {0.5};
  
  EXPECT_THROW(nn.forward_propagation(input), std::invalid_argument);
}

TEST(NeuralNetworkTest, EmptyLayerSize) {
  std::vector<size_t> layer_size = {};

  EXPECT_THROW(enola::neural::NeuralNetwork<double> nn(layer_size),
               std::invalid_argument);
}

TEST(NeuralNetworkTest, NonFloatingPointType) {
  std::vector<size_t> layer_size = {2, 3, 1};

#ifdef COMPILE_TIME_CHECK
  EXPECT_TRUE(false);
#endif  // COMPILE_TIME_CHECK
}
