#ifndef MATRIX_TENSOR_HPP
#define MATRIX_TENSOR_HPP

#include <cstdint>
#include <tuple>
#include <vector>

/**
 * @struct _3d_matrix
 * @brief representing 3d matrix with metadata for dimension
 *
 * this structure encapsulate 3d matrix along with its dimension
 */
struct _3d_matrix {
  std::vector<std::vector<std::vector<int64_t>>> mat;
  int64_t dim1, dim2, dim3;
};

/**
 * @class tensor
 * @brief representing 3d tensor with dynamic resizing capabilities
 *
 * this class provide an interface for managing 3d tensor, it support initialize
 * with specified dimensions and ensures proper allocation of memory for the
 * underlying 3d matrix
 */
class tensor {
public:
  /**
   * @brief construct tensor with the specification dimension
   *
   * initialize a 3D tensor with dimensions `dim1 x dim2 x dim3`. internal
   * matrix is resized to accomodate the specified dimension
   *
   * @param dim1 size first dimension
   * @param dim2 size second dimension
   * @param dim3 size third dimension
   */
  explicit tensor(int64_t dim1, int64_t dim2, int64_t dim3)
      : matrix{_3d_matrix{}} {
    matrix.dim1 = dim1;
    matrix.dim2 = dim2;
    matrix.dim3 = dim3;
    // resize the 3d matrix to the specified dimensions
    matrix.mat.resize(dim1, std::vector<std::vector<int64_t>>(
                                dim2, std::vector<int64_t>(dim3)));
  }

  /**
   * @brief destructor for the tensor class
   11*/
  ~tensor() = default;

  /**
   * @brief retrieve dimension of the tensor
   *
   * @return tuple containing the dimension `dim1, dim2, dim3` of the tensor
   */
  std::tuple<int64_t, int64_t, int64_t> get_dimension() const {
    return {matrix.dim1, matrix.dim2, matrix.dim3};
  }

  /**
   * @brief accesses the element at the specified indices in the tensor.
   *
   * provides read/write access to the element at position `(i, j, k)` in the
   * tensor.
   *
   * @param i index along the first dimension.
   * @param j index along the second dimension.
   * @param k index along the third dimension.
   * @return reference to the element at `(i, j, k)`.
   */
  int64_t &operator()(int64_t i, int64_t j, int64_t k) {
    return matrix.mat.at(i).at(j).at(k);
  }

  /**
   * @brief accesses the element at the specified indices in the tensor (const
   * version)
   *
   * provides read-only access to the element at position `(i, j, k)` in the
   * tensor
   *
   * @param i index along the first dimension.
   * @param j index along the second dimension.
   * @param k index along the third dimension.
   * @return const reference to the element at `(i, j, k)`.
   */
  const int64_t &operator()(int64_t i, int64_t j, int64_t k) const {
    return matrix.mat.at(i).at(j).at(k);
  }

private:
  // internal representation of the 3d tensor
  _3d_matrix matrix;
};

#endif // !MATRIX_TENSOR_HPP
