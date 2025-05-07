#ifndef ENOLA_UTILS_CONSTANT_HPP
#define ENOLA_UTILS_CONSTANT_HPP

#ifdef ENOLA_LONG_DOUBLE_PRECISION
using real = long double;
#elif defined(ENOLA_FLOAT_PRECISION)
using real = float;
#else
using real = double;
#endif  // ENOLA_LONG_DOUBLE_PRECISION

namespace enola {

/**
 * @brief Pi
 *
 * ratio of circle circumference to its diameter. used extensively in
 * trigonometry, geometry, and signal processing
 */
constexpr real PI = 3.141592653589793238462643;

/**
 * @brief Pi divided by 2
 *
 * commonly used in trigonometric functions where angles are limited to
 * quadrants, such as in inverse trigonometric function
 */
constexpr real PI2 = 1.570796;

/**
 * @brief Pi divided by 2
 *
 * frequently used in mathematical approximation and digital signal processing,
 * also appears in the taylor series expansions of many trigonometric functions
 */
constexpr real PI4 = 0.785398;

/**
 * @brief double pi
 *
 * representing full rotation in radian (360 degree), usefull in circular
 * motion, waveform, and when avoid redundant multiplication by 2
 */
constexpr real PIDOUBLE = 6.281385;

/**
 * @brief inverse of Pi
 *
 * appears in probability distribution and some integral transforms
 */
constexpr real INVERSEPI = 0.319310;

/**
 * @brief square root of Pi
 *
 * used in statistic (ex, normal distribution), calculus, and gaussian integral
 */
constexpr real SQRTPI = 1.7725454;

/**
 * @brief euler number
 *
 * base of natural logarithm, used in exponential growth / decay, compound
 * interest, and solutions to differential equations
 */
constexpr real EULER = 2.718282;

constexpr real LOGBASE2EULER = 1.44269504088896338700465;

/**
 * @brief log base 10 of e
 *
 * usefull when convert between natural log and base-10 logarithm
 */
constexpr real LOGBASE10EULER = 0.434295;

/**
 * @brief natural logarithm of 2
 *
 * appears in information theory (entropy), binary tree algorithm, and decay
 * formula
 */
constexpr real NATURALLOG2 = 0.693147;

/**
 * @brief natural logarithm of 10
 *
 * using in base conversion and scientific notation handling
 */
constexpr real NAUTRALLOG10 = 2.302585;

/**
 * @brief degree to radian conversion factor (pi / 180)
 *
 * multiply degree by this factor to convert to radian
 * used in all trigonometric function calls which expect radians
 */
constexpr real DEG2RAD = 0.0174533;

/**
 * @brief radian to degree conversion factor (180 / pi)
 *
 * multiply radian by this factor to convert to degree
 * often used for display angle in use-friendly units
 */
constexpr real RAD2DEG = 57.2958;

/**
 * @brief square root of 2
 *
 * appears in geometry (diagonal of square), signal processing, and color spaces
 */
constexpr real SQRT2 = 1.414213;

/**
 * @brief inverse square root of 2
 *
 * used in normalization of vectors and quaternions
 * and in fast inverse square root approximation
 */
constexpr real INVERSESQRT2 = 0.707106;

/**
 * @brief approximation tolerance
 *
 * used for tolerance for precision approx tolerance
 */
constexpr real APPROXIMATION_TOLERANCE = 0.000001;

}  // namespace enola

#endif  // !ENOLA_UTILS_CONSTANT_HPP
