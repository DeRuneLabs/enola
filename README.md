# enola
library for perform some tensor operation for specific project, built with C++17

## basic usage

```cpp
#include <enola/tensor/tensor_storage.hpp>
#include <array>
#include <iostream>

using namespace enola;

int main() {
  std::array<std::size_t, 2> shape = {2, 2};

  tensor::Storage<double, tensor::CPU> storage(shape);
  for (std::size_t i = 0; i < storage.size(); ++i) {
    storage[i] = static_cast<double>(i + 1);
  };

  std::cout << "element at index 0: " << storage[0] << std::endl;
  std::cout << "element at index 5: " << storage[5] << std::endl;

  std::cout << "element in storage: " << std::endl;
  for (auto it = storage.begin(); it != storage.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  return 0;
}
```

for more example check on [example](example) folder.
