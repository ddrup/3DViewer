#ifndef SRC_AFFINE_TRANSFORMATION_H_
#define SRC_AFFINE_TRANSFORMATION_H_

#include <cmath>
#include <cstddef>
#include <vector>

namespace s21 {

enum class Coordinate { kX = 0, kY = 1, kZ = 2 };

class AffineTransformation {
 public:
  using Matrix = std::vector<std::vector<float>>;

  static AffineTransformation& GetInstance() {
    static AffineTransformation instance;
    return instance;
  }

  AffineTransformation(const AffineTransformation&) = delete;
  AffineTransformation& operator=(const AffineTransformation&) = delete;

  void glTranslated(double mov, Coordinate value_coordinate);
  void glScaled(double scale_factor);
  void glRotate(double mov, Coordinate value_coordinate);

  Matrix GetMatrix() const;

 private:
  AffineTransformation() = default;
  Matrix matrix_{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
};

}  // namespace s21

#endif  // SRC_AFFINE_TRANSFORMATION_H_