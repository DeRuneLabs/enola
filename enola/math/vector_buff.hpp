#ifndef ENOLA_MATH_VECTOR_BUFF_HPP
#define ENOLA_MATH_VECTOR_BUFF_HPP

#include "../utils/common.hpp"
#include <vector>

namespace enola {
using vector_buff = std::vector<real>;

/**
 * @brief compute the element-wise product sum (dot product) of two vector
 *
 * this function calculate the sum of element-wise product between two vector
 *
 * @param X first input vector
 * @param Y second input vector
 * @return the sum pairwise products (dot product), or 0 if vector differ size
 */
inline real product_sum(const vector_buff& X, const vector_buff& Y) {
  // check if vector have the same size
  if (X.size() != Y.size()) {
    return 0;  // return zero if size mismatch
  }
  // initialize result calculator
  real res = 0;
  // looping all elements and compute product sum
  for (int i = 0; i < X.size(); i++) {
    res += X[i] * Y[i];
  }
  return res;
}

/**
 * @brief compute the element wise product sum of three vector
 *
 * this function compute the sum of element-wise product of three vector
 *
 * @param X first the input vector
 * @param Y second input vector
 * @param Z third input vector
 * @return sum of triple products, or 0 if size don't match
 */
inline real product_sum(const vector_buff& X,
                        const vector_buff& Y,
                        const vector_buff& Z) {
  // make sure all three vector have the same size
  if (X.size() != Y.size() || X.size() != Z.size()) {
    return 0;  // return 0 if size mismatch
  }
  real res = 0;
  for (int i = 0; i < X.size(); i++) {
    res += X[i] * Y[i] * Z[i];
  }
  return res;
}

/**
 * @brief compute the element-wise quotient sum of two vector
 *
 * this function compute the sum of element-wise quotient
 *
 * @param X numerator vector
 * @param Y denominator vector
 * @return sum of element-wise quotient, or 0 if size mismatch
 */
inline real quotient_sum(const vector_buff& X, const vector_buff& Y) {
  if (X.size() != Y.size()) {
    return 0;
  }
  real res = 0;
  for (int i = 0; i < X.size(); i++) {
    res += X[i] / Y[i];
  }
  return res;
}

/**
 * @brief compute the sum of square of all elements in a vector
 *
 * this function compute Σ(X[i]^2) for i in [0, size)
 *
 * @param X input vector
 * @return sum of squared elements
 */
inline real sum_square(const vector_buff& X) {
  if (!X.size()) {
    return 0;
  }

  real res = 0;
  for (int i = 0; i < X.size(); i++) {
    res += X[i] * X[i];
  }
  return res;
}

/**
 * @brief compute the sum of all elements in a vector
 *
 * this function compute Σ(X[i]) for i in [0, size)
 *
 * @param X input vector
 * @return sum of all elements
 */
inline real sum(const vector_buff& X) {
  if (!X.size()) {
    return 0;
  }
  real res = 0;
  for (int i = 0; i < X.size(); i++) {
    res += X[i];
  }
  return res;
}

}  // namespace enola

#endif  // !ENOLA_MATH_VECTOR_BUFF_HPP
