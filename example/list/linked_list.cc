#include "../../enola/list/linked_list.hpp"

#include <iostream>

int main() {
  linked_list<int> list;

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  std::cout << "list after push back: " << list << std::endl;
  
  list.push_front(5);
  std::cout << "list after push front: " << list << std::endl;

  list.erase(20);
  std::cout << "list after erasing 20: " << list << std::endl;

  return 0;
}
