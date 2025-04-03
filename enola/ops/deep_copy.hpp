#ifndef ENOLA_OPS_DEEP_COPY_HPP
#define ENOLA_OPS_DEEP_COPY_HPP

#include <memory>
#include <vector>
namespace enola {
namespace ops {

/**
 * @brief generic DeepCopy function for any type T
 *
 * this function use copy constructor of T to create deep copy.
 * it assume that T has properly implemented copy constructor
 *
 * @tparam T the type of the object to be copied
 * @param input object to be deep-copied
 * @return deep copy input object
 */
template <typename T>
T DeepCopy(const T& input) {
  // use copy constructor of T for create new instance
  // this will works for simple type like int, float or custom classes with copy
  // constructor
  return T(input);
}

/**
 * @brief specialization of DeepCopy for std::vector<T>
 *
 * this function perform deep copy of all element in the vector
 * it will iterating over each element and recursively call DeepCopy on it
 *
 * @tparam T type element stored in the vector
 * @param input vector to be deep-copied
 * @return deep copy of the input vector
 */
template <typename T>
std::vector<T> DeepCopy(const std::vector<T>& input) {
  // create new vector to store the deep-copied element
  std::vector<T> result;
  // reserve memory for the result vector to improve performance
  // this will be try avoid multiple reallocation as element are added
  result.reserve(input.size());
  // iterate over each element in input vector
  for (const auto& element : input) {
    // recursively call DeepCopy on each element to ensure all nested object are
    // copied
    result.push_back(DeepCopy(element));
  }
  return result;
}

/**
 * @brief specialization of DeepCopy for std::shared_ptr<T>
 *
 * this function perform deep copy of the underlying object managerd by the
 * shared_ptr if the input pointer is null, return nullptr
 *
 * @tparam T type of the object managed by the shared_ptr
 * @param input shared_ptr to be deep-copied
 * @return deep-copied of the input shared_ptr
 */
template <typename T>
std::shared_ptr<T> DeepCopy(const std::shared_ptr<T>& input) {
  // check input shared_ptr is null
  if (!input) {
    return nullptr;
  }
  // deference input pointer to access underlying object
  // call DeepCopy recursively to create a DeepCopy of the object
  // wrapping the deep-copied object in a new shared_ptr and return it
  return std::make_shared<T>(DeepCopy(*input));
}

}  // namespace ops
}  // namespace enola

#endif  // !ENOLA_OPS_DEEP_COPY_HPP
