#ifndef ENOLA_UTILS_COMMON_HPP
#define ENOLA_UTILS_COMMON_HPP

#include "constant.hpp"

namespace enola {

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
 * @brief compute the tangent of angle in radians
 *
 * tan(x) = sin(x) / cos(x)
 *
 * @param x angle in radians
 * @return tangent of x
 */
inline real tan(real x) {
  return sin(x) / cos(x);  // using enola::sin and assume enola::cos exists
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
  return cos(x) / sin(x);  // assume enola::cos exists
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

/**
 * @brief return the greated of two value
 *
 * @param x first value
 * @param y seconds value
 * @return larger of x or y
 */
inline real max(real x, real y) { return x > y ? x : y; }

/**
 * @brief return the samller of two value
 *
 * @param x first value
 * @param y second value
 * @return the smaller of x or y
 */
inline real min(real x, real y) { return x > y ? y : x; }

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
