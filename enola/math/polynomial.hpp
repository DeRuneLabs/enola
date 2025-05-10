#ifndef ENOLA_MATH_POLYNOMIAL_HPP
#define ENOLA_MATH_POLYNOMIAL_HPP

#include "vector_buff.hpp"

namespace enola {

/**
 * @class Polynomial
 * @brief representing a polynomial using vector coefficient
 *
 * polynomial object is define by its coefficient in increasing power
 * P(x) = coeff[0] * x^0 + coeff[1] * x^1 + ... + coeff[n] * x^n
 * information:
 * - evaluating at given x value
 * - add/multiply two polynomial
 * - find the degree of the polynomial
 * - trim trailing zero coefficient
 */
class Polynomial {
 public:
  // vector of coefficient where index corresponds to power of x
  enola::vector_buff coeff;

  /**
   * @brief default constructor
   * initialize empty polynomial with no coefficient
   */
  Polynomial() : coeff() {}

  /**
   * @brief constructor from existing coefficient vector
   * @param c vector of coefficient
   */
  Polynomial(const enola::vector_buff& c) : coeff(c) {}

  /**
   * @brief destructor
   */
  ~Polynomial() {}

  /**
   * @brief constructor from initializer list
   * allowing construction like polynomial p = {1.0, 2.0, 3.0};
   * @param l initializer list of coefficient
   */
  Polynomial(std::initializer_list<real> l) : coeff(l) {}

  /**
   * @brief access operator for modifying coefficient
   * @param i index/power of x
   * @return reference to coefficient at index i
   */
  inline real& operator[](int i) { return coeff[i]; }

  /**
   * @brief accessor for reading coefficient (const)
   * @param i index of x or power of x
   * @return a value of coefficient at index i
   */
  inline real get(int i) const { return coeff[i]; }

  /**
   * @brief evaluating polynomial at given x
   * @param x real number input
   * @return result of evaluating polynomial at x
   */
  inline real eval(real x) const {
    real res = 0;
    for (int i = 0; i < coeff.size(); ++i) {
      if (coeff[i] != 0) {
        res += coeff[i] * enola::pow(x, i);
      }
    }
    return res;
  }

  /**
   * @brief function call operator
   * @param x input value
   * @return result evaluation
   */
  inline real operator()(real x) const { return eval(x); }

  /**
   * @brief find the order of the polynomial
   * return the highest power with non-zero coefficient
   * @return degree of the polynomial
   */
  inline int find_order() const {
    for (int i = coeff.size() - 1; i >= 0; --i) {
      if (coeff[i] != 0) {
        return i;
      }
    }
    // zero polynomial cases
    return 0;
  }

  /**
   * @brief remove trailing zero coefficient
   *
   * modifying the coefficient vector by removing trailing zero element
   * useful after arithmetic operations that may result in leading zero
   */
  inline int trim() {
    for (int i = coeff.size() - 1; i >= 0; --i) {
      if (coeff[i] != 0) {
        break;
      }
      coeff.pop_back();
    }
  }

  inline size_t size() const { return coeff.size(); }

  /**
   * @brief add two polynomial
   *
   * add this polynomial to another one and return the result
   * only add up the min size of both
   * @param p right-hand side polynomial
   * @return new polynomial representing the sum
   */
  inline Polynomial operator+(const Polynomial& p) const {
    Polynomial r(coeff);
    for (int i = 0; i < enola::min(r.size(), p.size()); ++i) {
      r[i] += p.get(i);
    }
    return r;
  }

  /**
   * @brief multiply two polynomial
   *
   * computing the product using convolution-like method
   * the result degree is deg(p1) + deg(p2), and the size is adjusted
   * accordingly
   * @param p right-hand side polynomial
   * @return new polynomial representing the product
   */
  inline Polynomial operator*(const Polynomial& p) const {
    Polynomial r = Polynomial();
    r.coeff.resize(this->size() + p.size() - 1);

    for (int i = 0; i < size(); ++i) {
      for (int j = 0; j < p.size(); ++j) {
        r[i + j] += coeff[i] * p.get(j);
      }
    }
    return r;
  }

  /**
   * @brief in place addition
   *
   * add another polynomial to this one and update the coefficient
   * only affect indices up the smaller size
   * @param p right-hand side polynomial
   * @return reference to update polynomial
   */
  inline Polynomial operator+=(const Polynomial& p) {
    for (int i = 0; i < enola::min(size(), p.size()); ++i) {
      coeff[i] += p.get(i);
    }
    return *this;
  }

  /**
   * @brief in-place subtraction
   *
   * subtraction another polynomial from this one
   * only affect indices upt the smaller size
   * @param p right-hand side polynomial
   * @return reference to update polynomial
   */
  inline Polynomial& operator-=(const Polynomial& p) {
    for (int i = 0; i < enola::min(size(), p.size()); ++i) {
      coeff[i] -= p.get(i);
    }
    return *this;
  }

  /**
   * @brief in-place multiplication
   *
   * multiplication this polynomial by another and store the result in place
   * internally compute the full product and assings back to this object
   * @param p right-hand side polynomial
   * @return reference to update polynomial
   */
  inline Polynomial& operator*=(const Polynomial& p) {
    Polynomial r = Polynomial();
    r.coeff.resize(this->size() + p.size() -
                   1);  // allocation space for product

    for (int i = 0; i < size(); ++i) {
      for (int j = 0; j < p.size(); ++j) {
        r[i + j] += coeff[i] * p.get(j);
      }
    }
    *this = r;  // assing computed product back to this
    return *this;
  }
};
}  // namespace enola

#endif  // !ENOLA_MATH_POLYNOMIAL_HPP
