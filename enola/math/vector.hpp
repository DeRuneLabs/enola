#ifndef ENOLA_MATH_VECTOR_HPP
#define ENOLA_MATH_VECTOR_HPP

#include "../utils/common.hpp"
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

  /**
   * @brief compute the cross product of this 3D vector with another
   *
   * if the dimension `N` is not 3, an empty Vector<3> is return
   *
   * @param other other 3D vector to compute the cross product with
   * @return a new Vector<3> representing the cross product result
   */
  inline Vector<3> cross(const Vector<3>& other) const {
    if (N != 3) {
      return Vector<3>();
    }

    Vector<3> res;

    res.data[0] = data[1] * other.data[2] - data[2] * other.data[1];
    res.data[1] = data[2] * other.data[0] - data[0] * other.data[2];
    res.data[2] = data[0] * other.data[1] - data[1] * other.data[0];

    return res;
  }

  /**
   * @brief add another vector component-wise to this vector
   *
   * @param other the vector to add
   */
  inline void operator+=(const Vector<N>& other) {
    for (int i = 0; i < N; ++i) {
      data[i] += other.data[i];
    }
  }

  /**
   * @brief subtract another vector component-wise from this vector
   *
   * @param other the vector to subtract
   */
  inline void operator-=(const Vector<N>& other) {
    for (int i = 0; i < N; ++i) {
      data[i] -= other.data[i];
    }
  }

  /**
   * @brief divide each component of the vector by scalar value
   *
   * @param scalar the scalar to divide by
   */
  inline void operator/=(real scalar) {
    for (int i = 0; i < N; ++i) {
      data[i] /= scalar;
    }
  }

  /**
   * @brief compute the magnitude (length) of the vector
   *
   * uses the euclid norm: sqrt(sum of square component)
   *
   * @return the magnitude of the vector
   */
  inline real magnitude() const {
    real m = 0;
    for (int i = 0; i < N; ++i) {
      m += data[i] * data[i];
    }
    return enola::sqrt(m);
  }

  /**
   * @brief convience alias for magnitude
   *
   * @return the length (magnitude) of the vector
   */
  inline real length() { return magnitude(); }

  /**
   * @brief compute the square of the magnitude without taking the square root
   *
   * useful for comparing length without needing to perform costly square root
   *
   * @return square of the magnitude
   */
  inline real square_magnitude() const {
    real m = 0;
    for (int i = 0; i < N; ++i) {
      m += data[i] * data[i];
    }
    return m;
  }

  /**
   * @brief convience alias for square_magnitude()
   *
   * @return square of the magnitude
   */
  inline real square_length() const { return square_magnitude(); }

  /**
   * @brief access the i-th component of the vector
   *
   * no bounds checking is performed
   *
   * @param i index of the component to access
   * @return reference to the i-th component
   */
  inline real& operator[](int i) { return data[i]; }

  /**
   * @brief access the i-th component of the vector
   *
   * no bounds checking is performed
   *
   * @param i index of the component to access
   * @return reference to the i-th component
   */
  inline real& at(int i) { return data[i]; }

  /**
   * @brief gets the i-th component of the vector (read-only)
   *
   * @param i index of the component
   * @return value of the i-th component
   */
  inline real get(int i) const { return data[i]; }

  /**
   * @brief sets the i-th component of the vector
   *
   * @param i index of the component
   * @param x new value for the component
   */
  inline void set(int i, real x) { data[i] = x; }

  /**
   * @brief normalize the vector to unit length
   *
   * if the vector magnitude is zero, normalization is skipped to avoid
   * division by zero
   */
  inline void normalize() {
    real m = magnitude();

    if (m == 0) {
      return;
    }

    for (int i = 0; i < N; ++i) {
      data[i] /= m;
    }
  }
};

}  // namespace enola

#endif  // !ENOLA_MATH_VECTOR_HPP
