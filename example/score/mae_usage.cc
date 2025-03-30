#include "../../enola/score/mae.hpp"
#include <iostream>

int main() {
  std::vector<std::size_t> shape = {2, 3};

  enola::tensor::Storage<int, enola::tensor::CPU> predict(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> actual(shape);

  predict[0] = 1;
  predict[1] = 4;
  predict[2] = 3;
  predict[3] = 2;
  predict[4] = 5;
  predict[5] = 6;

  actual[0] = 1;
  actual[1] = 2;
  actual[2] = 3;
  actual[3] = 4;
  actual[4] = 5;
  actual[5] = 6;

  try {
    double score = enola::score::mae(predict, actual);
    std::cout << "MAE score: " << score << std::endl;
  } catch (const std::exception& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }
  return 0;
}
