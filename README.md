# Enola
Library for perform some tensor operation for specific project, built with C++17

currently including:
- Neural Network
- Function:
  - Sigmoid
  - Activation Function:
    - Binary Step
    - Exponential Linear Unit (ELU)
    - Rectified Linear Unit (RELU)
    - Softplus
    - Squareplus
    - Swish
- Operation:
  - Deep Copy
- Score:
  - Mean Absolute Error
  - Mean Square Error
- Tensor:
  - Operation
  - Storage ( Currently Support on CPU Process )
  - Tensor View

## basic usage

**Simple neural Network**

```cpp
#include "<enola/nn.hpp>"
#include <exception>
#include <iostream>

int main() {
  try {
    // define the arch of neural network
    // each value in the vector representing number of neuron in layer
    // - first value is size of input layer
    // - intermediate value representing hidden layers
    // last value is size of the output layer
    std::vector<size_t> layer_size = {
        2,  // inputs: 2 neuron (two features)
        3,  // hidden layer: 3 neuron
        1,  // output: 1 neuron (binary classification or regression)
    };

    // initialize neural network with specific architecture
    enola::neural::NeuralNetwork<double> nn(layer_size);

    // prepare input data for neural network
    // this example use simple input vector with two values
    std::vector<double>                  input  = {0.5, 0.8};

    // perform forward propagation to computing the output of neural network
    std::vector<double>                  output = nn.forward_propagation(input);

    // print output of the neural network
    std::cout << "output: ";
    for (double val : output) {
      std::cout << val << " "; // print each output
    }
    std::cout << std::endl;
  } catch (const std::exception &error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return 0;
}
```

for more example check on [example](example) folder.

## Tensor Storage With GPU process

Enola currently support Tensor Storage processing by GPU with OpenCL (open computing language) for perform tensor storage and processing task, OpenCL is good for help for processing gpu, OpenCL provide APIs to manage memory on the GPU explicitly, so we can allocate memory buffer for tensors, for more information you can check [here](https://www.khronos.org/opencl/) about OpenCL
