#ifndef ENOLA_MATH_VECTOR_HPP
#define ENOLA_MATH_VECTOR_HPP

#include "../utils/common.hpp"
#include "vector_buff.hpp"
#include <algorithm>
#include <initializer_list>

namespace enola {

/**
 * @class vector
 * @brief fixed-size mathematical vector class templated on size N
 *
 * this class representing a vector in N-dimensional space with real-number
 * components it support standard arithmetic operations, dot product, and
 * initializtion for list
 */
template <unsigned int N>
class Vector {
 public:
  /**
   * @brief compile-time constant specifying the dimensionality of the vector
   */
  static constexpr unsigned int size = N;

  /**
   * @brief underlying data storage as a raw array of N real numbers
   */
  real data[N];

  /**
   * @brief default constructor
   * initializes vector with unitialized data
   */
  Vector() = default;

  /**
   * @brief copy constructor
   *
   * copies each element from another vector
   * @param other vector to copy from
   */
  Vector(const Vector<N>& other) {
    for (int i = 0; i < N; ++i) {
      data[i] = other.data[i];
    }
  }

  /**
   * @brief copy assignment operator
   *
   * assign each element from another vector<N>
   * @param other vector to assing from
   * @return reference to this vector after assignment
   */
  Vector<N>& operator=(const Vector<N>& other) {
    for (int i = 0; i < N; ++i) {
      data[i] = other.data[i];
    }
    return *this;
  }

  /**
   * @brief constructor from initializer list
   *
   * initialize the vector from a list values
   * if the number of element doesn't match N, behaviour is undefined
   * @param l initializer list of real numbers
   */
  Vector(std::initializer_list<real> l) {
    if (l.size() != N) {
      return;
    }
    std::copy(l.begin(), l.end(), &data[0]);
  }

  /**
   * @brief destructor
   * trivially default
   */
  ~Vector() = default;

  /**
   * @brief vector addition
   *
   * return new vector where each component is the sum of corresponding
   * components
   * @param other right-hand side vector
   * @return resullt vector: `(*this) + other`
   */
  inline Vector<N> operator+(const Vector<N>& other) const {
    Vector<N> result;
    for (int i = 0; i < N; ++i) {
      result.data[i] = data[i] + other.data[i];
    }
    return result;
  }

  /**
   * @brief vector substraction
   *
   * return new bector where each component is the difference of corresponding
   * @param other right-hand side vector
   * @return resulting vector: `(*this) - other`
   */
  inline Vector<N> operator-(const Vector<N>& other) const {
    Vector<N> result;
    for (int i = 0; i < N; ++i) {
      result.data[i] = data[i] - other.data[i];
    }
    return result;
  }

  /**
   * @brief scalar multiplication (from right)
   *
   * multiplies each component by a scalar value
   *
   * @param scalar scalar multiple
   * @return vector result: `(*this) - other`
   */
  inline Vector<N> operator*(real scalar) const {
    Vector<N> result;
    for (int i = 0; i < N; ++i) {
      result.data[i] = scalar * data[i];
    }
    return result;
  }

  /**
   * @brief scalar division
   *
   * divide each component by a scalar value
   *
   * @param scalar scalar division
   * @return vector result: `(*this) / scalar`
   */
  inline Vector<N> operator/(real scalar) const {
    Vector<N> result;
    for (int i = 0; i < N; ++i) {
      result.data[i] = data[i] / scalar;
    }
    return result;
  }

  /**
   * @brief dot product
   *
   * compute the eucledian dot product with another vector
   *
   * @param other right-hand side vector
   * @return real number representing the dot product
   */
  inline real dot(const Vector<N>& other) const {
    real result = 0;
    for (int i = 0; i < N; ++i) {
      result += data[i] * other.data[i];
    }
    return result;
  }

  /**
   * @brief overloaded multiplication operator for dot product
   *
   * allow using `*` syntax between two vector to compute dot product
   *
   * @param other right-hand side vector
   * @return real number representing the dot product
   */
  inline real operator*(const Vector<N>& other) const { return dot(other); }
};

}  // namespace enola

#endif  // !ENOLA_MATH_VECTOR_HPP
