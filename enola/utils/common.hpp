#ifndef ENOLA_UTILS_COMMON_HPP
#define ENOLA_UTILS_COMMON_HPP

#include "constant.hpp"
#include <cmath>

namespace enola {

/**
 * @brief compute the square of given number
 *
 * this function return the result of multiple the input value by itself
 *
 * @param x input value to be squared
 * @return the square of x (x * x)
 */
inline real square(real x) {
  return x * x;  // multiply x by itself to compute x^2
}

/**
 * @brief compute the cube of a given number
 *
 * this function return the result of multiplying the input value by itself
 * twice it is an efficient way to calculate x^2
 *
 * @param x input value to be cubed
 * @return the cubed of x  (x * x * x)
 */
inline real cube(real x) {
  return x * x * x;  // multiply x three times to compute x^3
}

/**
 * @brief compute the square root of float point using x87 FPU
 *
 * this function using inline assembly to compute square root directly on x86
 * which is can be faster than std lib call in certain context
 *
 * @param x input value (must be non-negative)
 * @return square root of x
 */
inline real sqrt(real x) {
#ifdef MSVC_ASM
  // microsoft visual c++ syntax for inline asm
  __asm {
    fld x  // load x into fpu stack
  fsqrt  // compute the square root
  }
#else
  // gcc / clang syntax for inline asm
  asm("fsqrt" : "+t"(x));
  return x;
#endif  // MSVC_ASM
}

/**
 * @brief compute the absolute value of floating-pointer number using x87 FPU
 *
 * uses inline assembly to execute the `fabs` FPU instruction
 *
 * @param x input value
 * @return absolute value of x
 */
inline real abs(real x) {
#ifdef MSVC_ASM
  __asm {
    fld x  // load x into FPU stack
  fabs  // take absolute value
  }
#else
  asm("fabs" : "+t"(x));
  return x;
#endif  // MSVC_ASM
}

inline int sgn(real x) { return (x > 0) ? 1 : (x < 0 ? -1 : 0); }

/**
 * @brief return the greated of two value
 *
 * @param x first value
 * @param y seconds value
 * @return larger of x or y
 */
inline real max(real x, real y) {
#ifdef ENOLA_BRANCHLESS
  return (x + y + abs(x - y)) / 2.0;
#else
  return x > y ? x : y;

#endif  // ENOLA_BRANCHLESS
}

/**
 * @brief return the samller of two value
 *
 * @param x first value
 * @param y second value
 * @return the smaller of x or y
 */
inline real min(real x, real y) {
#ifdef ENOLA_BRANCHLESS
  return (x + y - abs(x - y)) / 2.0;
#else
  return x > y ? y : x;
#endif  // ENOLA_BRANCHLESS
}

/**
 * @brief clamp value between minimum and maximum boundary
 *
 * if x < a -> return a
 * if x > b -> return b
 * else -> return x
 *
 * @param x value to clamp
 * @param a minimum allowed value
 * @param b maximum allowed value
 * @return clamped value
 */
inline real clamp(real x, real a, real b) {
  return x > b ? b : (x < a ? a : x);
}

inline real fyl2x(real x, real y) {
  real res;
#ifdef MSVC_ASM
// TODO: implemented
#else
  asm("fyl2x" : "=t"(res) : "0"(x), "u"(y) : "st(1)");
#endif  // MSVC_ASM
  return res;
}

inline real f2xm1(real x) {
#ifdef MSVC_ASM
  __asm {
    fld x
  f2xm1
  }
#else
  asm("f2xm1" : "+t"(x));
#endif  // MSVC_ASM
  return x;
}

/**
 * @brief compute log base of 2 number using FPU
 *
 * using identity: log2(x) = fyl2x(x, 1.0)
 *
 * @param x input value > 0
 * @return approximate value of log2(x)
 */
inline real log2(real x) { return fyl2x(x, 1.0); }

/**
 * @brief compute log base of 10 of number using FPU
 *
 * @param x input value > 0
 * @return approximate value of log10(x)
 */
inline real log10(real x) { return fyl2x(x, 1.0 / LOGBASE10EULER); }

/**
 * @brief compute natural logarithm (ln) using FPU
 *
 * @param x input value > 0
 * @return approximate value of ln(x)
 */
inline real ln(real x) { return fyl2x(x, 1.0 / LOGBASE2EULER); }

/**
 * @brief compute integer power of a floating-point number
 *
 * compute x^n where n is an integer (positive, negative or zero)
 *
 * @param x base value
 * @param n exponent
 * @return raised to the power of n
 */
inline real pow(real x, int n) {
  real res;

  if (n > 0) {
    // multiply x by itself n times
    res = x;
    for (int i = 1; i < n; ++i) {
      res *= x;
    }
  } else if (n < 0) {
    // invert and divide for negative exponent
    res = 1 / x;
    for (int i = 1; i < -n; ++i) {
      res /= x;
    }
  } else {
    // any non-zero number ot the power if 0 is 1
    return 1.0;
  }
  return res;
}

/**
 * @brief fast approx of e^x using FPU
 *
 * splits x into integer and fractional parts
 * e^x = e^ integer_part * e ^ fractional_part
 *
 * the fractional part is computed using:
 * e^x = (2^(x / log2(e))) = f2xm1(x / (2 * ln(2))) + 1 squared
 *
 * @param real number exponent
 * @return approximation of e^x
 */
inline real exp_approx(real x) {
  int  x_int   = enola::abs(int(x - 0.5));  // rounding to nearest integer
  real x_fract = enola::abs(x - x_int);     // fractional remainder

  return enola::pow(EULER, x_int) *
         square(f2xm1(x_fract / (2 * NATURALLOG2)) + 1);
}

/**
 * @brief fast approximation of x ^ a using FPU intrinsics
 *
 * supports both positive and negative exponent
 *
 * @param x base value
 * @param a exponent
 * @return approximation of x ^ a
 */
inline real powf_approx(real x, real a) {
  if (a < 0) {
    // using reciprocal for negative exponent
    return 1.0 / powf_approx(x, abs(a));
  }
  int  a_int     = enola::abs(int(a - 0.5));  // integer part
  real a_fract   = enola::abs(a - a_int);     // fractional part
  real x_int_pwr = enola::pow(x, a_int);      // compute x ^ a_int

  // using exp(log(x) * fract) for the fractional component
  return x_int_pwr * (a_fract >= APPROXIMATION_TOLERANCE
                          ? exp_approx(fyl2x(x, a_fract / LOGBASE2EULER))
                          : 1);
}

/**
 * @brief compute the euler number raised to a power
 *
 * using powf_approx with base e
 *
 * @param x exponent
 * @return approximation of e^x
 */
inline real exp(real x) { return powf_approx(EULER, x); }

/**
 * @brief compute sin of angle in radians using x86 FPU
 *
 * using inline assembly to leeverage x87 fpu `fsin` instruction for fast
 * computation
 *
 * @param x angle in radian
 * @return sin of x
 */
inline real sin(real x) {
#ifdef MSVC_ASM
  __asm {
      fld x  // load x into FPU stack
    fsin  // compute sin
  }
#else
  asm("fsin" : "+t"(x));
  return x;
#endif  // MSVC_ASM
}

/**
 * @brief compute the cosine of angle using x87 FPU
 *
 * this function calculate the cosine of given angle `x` (in radians) using
 * the x87 floating-point unit `fcos` instruction directly
 *
 * @param x angle in radians
 * @return cosine of x
 */
inline real cos(real x) {
  // using conditional compilation to handle different compile
#ifdef MSVC_ASM
  __asm {
    fld x  // load `x` into FPU stack
  fcos  // computing cosine of ST(0); replace ST(0) with cos(ST(0))
  }
#else
  asm("fcos" : "+t"(x));
#endif  // MSVC_ASM
  return x;
}

/**
 * @brief compute the tangent of angle in radians
 *
 * tan(x) = sin(x) / cos(x)
 *
 * @param x angle in radians
 * @return tangent of x
 */
inline real tan(real x) {
  real s, c;
#ifdef MSVC_ASM
// TODO: IMPLEMENTED
#else
  asm("fsincos" : "=t"(c), "=u"(s) : "0"(x));
#endif  // MSVC_ASM
  return s / c;
}

/**
 * @brief compute the cottangent of an angle in radians
 *
 * cot(x) = cos(x) / sin(x)
 *
 * @param x angle in radians
 * @return cottangent of x
 */
inline real cot(real x) {
  real s, c;

#ifdef MSVC_ASM
// TODO: implemented
#else
  asm("fsincos" : "=t"(c), "=u"(s) : "0"(x));
#endif  // MSVC_ASM
  return c / s;
}

/**
 * @brief compute the arctangent of number using an approximation
 *
 * this an approximate implementation atan(x) for performance reason
 * avoiding expensive transcendal operation, it uses a piecewise formula
 * based on the symetry and range reduction
 *
 * if |x| > 1, it uses the identity: atan(x) = π/2 - atan(1/x)
 *
 * for |x| <= 1, it uses a polynomial approximation:
 *  atan(x) ≈ (π/4)*x - x*(|x| - 1)*(0.2447 + 0.0663*|x|)
 *
 * @param x input value
 * @return approximate value of arctangent of x in radians
 */
inline real atan(real x) {
  if (abs(x) > 1) {
    // use identity: atan(x) = pi / 2 - atan(1/x) for |x| > 1
    return atan(PI2 - atan(1 / x));
  }

  // polynomizal approximation for small x
  return PI4 * x - x * (abs(x) - 1) * (0.2447 + 0.0663 * abs(x));
}

/**
 * @brief compute the arcsine (inverse sin) of number
 *
 * use identity:
 * asin(x) = atan(x / sqrt(1 - x^2))
 *
 * @param x value in the range [-1, 1]
 * @return angle whose sin is x, in radians
 */
inline real asin(real x) { return atan(x / enola::sqrt(1 - x * x)); }

/**
 * @brief compute the arccosin (inverse sin) of number
 *
 * uses the identity
 * acos(x) = atan(sqrt(1 - x^2) / x)
 *
 * @param x value in the range [-1, 1]
 * @return the angle whose cosine is x, in radians
 */
inline real acos(real x) { return atan(enola::sqrt(1 - x * x) / x); }

/**
 * @brief compute the 2-argument arctangent (atan2(y, x)) to determine angle in
 * correct quadrant
 *
 * atan2 returns the angle θ
 * x = r * cos(θ)
 * y = r * sin(θ)
 *
 * handles special cases like division by zero and quadrant adjustment
 *
 * @param y y-coordinate
 * @param x x-coordinate
 * @return angle between the positive x-axis and the point (x, y) in radians
 */
inline real atan2(real y, real x) {
  if (x == 0) {
    // special case: vertical axis
    return sgn(y) * PI2;  // pi / 2 depending on sign of y
  }
  real result = atan(y / x);
  result -= clamp(sgn(x), -1, 0) * PI * sgn(y);
  return result;
}

/**
 * @brief compute the hyperbolic sin of a number
 *
 * hyperbolic sin is defined as
 * sinh(x) = (e^x - e^-x) / 2
 *
 * @param x input value
 * @return hyperbolic sin of x
 */
inline real sinh(real x) { return (enola::exp(x) - enola::exp(-x)) / 2.0; }

/**
 * @brief compute the hyperbolic cosine of number
 *
 * hyperbolic cosine is defined as
 * cosh(x) = (e^x + e^-x) / 2
 *
 * @param x input value
 * @return hyperbolic cosine of x
 */
inline real cosh(real x) { return (enola::exp(x) + enola::exp(-x)) / 2.0; }

/**
 * @brief compute the hyperbolic tangent of a number
 *
 * tanh(x) = sinh(x) / cosh(x) = (e^2x - 1) / (e^2x + 1)
 *
 * @param x input value
 * @return hyperbolic tangent of x, in the range(-1, 1)
 */
inline real tanh(real x) {
  real exp_2x = enola::exp(2 * x);
  return (exp_2x - 1) / (exp_2x + 1);
}

/**
 * @brief compute the factorial of a non-negative integer n
 *
 * factoral(n) = n * (n - 1) x ... x 1
 *
 * @param n non-negative integer
 * @return factorial of n
 */
inline long long fact(unsigned int n) {
  long long res = 1;
  for (int i = n; i > 1; --i) {
    res *= i;
  }
  return res;
}

/**
 * @brief compute the binomial coefficient
 *
 * binomial coefficient defined as
 * C(n, m) = n! / (m! * (n - m)!)
 *
 * this implementation avoid full factorial computation for efficiency
 *
 * @param n total number of items
 * @param m number of selected items
 * @return the number of ways to choose m items from n, or 0 if n < m
 */
inline long long binomial_coeff(unsigned int n, unsigned int m) {
  if (n < m) {
    // invalid input
    return 0;
  }

  long long res = 1;
  for (int i = n; i > m; --i) {
    res *= i;
  }
  return res / fact(n - m);
}

/**
 * @brief convert degree to radians
 *
 * radians = degree x pi / 180
 *
 * @param degree angle in degree
 * @return equivalent angle in radians
 */
inline real radians(real degree) { return degree * DEG2RAD; }

/**
 * @brief convert radians to degree
 *
 * degree = radians x 180 / pi
 *
 * @param radian angle in radians
 * @return equivalent angle in degree
 */
inline real degree(real radian) {
  return radian * RAD2DEG;  // defined in constant.hpp
}

}  // namespace enola

#endif  // !ENOLA_UTILS_COMMON_HPP
