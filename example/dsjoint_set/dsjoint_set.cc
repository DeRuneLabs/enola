#include "../../enola/dsjoint_set/dsjoint_set.hpp"
#include <iostream>

int main() {
  dsu dsjoint(6);

  std::cout << "initial state" << std::endl;

  for (uint64_t i = 0; i < 6; ++i) {
    std::cout << "element " << i << ": parent = " << dsjoint.findSet(i)
              << ", size = " << dsjoint.size(i)
              << ", min = " << dsjoint.get_min(i)
              << ", max = " << dsjoint.get_max(i) << std::endl;
  }

  return 0;
}
