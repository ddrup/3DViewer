#include "s21_affine_transformation.h"

using namespace s21;

void AffineTransformation::glTranslated(double mov,
                                        Coordinate value_coordinate) {
  int value = static_cast<int>(value_coordinate);
  matrix_[value][3] += mov;
}

void AffineTransformation::glScaled(double scale_factor) {
  for (size_t i = 0; i < matrix_.size() - 1; ++i) {
    matrix_[i][i] *= scale_factor;
  }
}

void AffineTransformation::glRotate(double mov, Coordinate value_coordinate) {
  mov = mov * M_PI / 180;

  if (value_coordinate == Coordinate::kY) {
    matrix_[0][0] = cos(-mov);
    matrix_[0][2] = -sin(-mov);
    matrix_[2][0] = sin(-mov);
    matrix_[2][2] = cos(-mov);

  } else if (value_coordinate == Coordinate::kX) {
    matrix_[1][1] = cos(mov);
    matrix_[1][2] = -sin(mov);
    matrix_[2][1] = sin(mov);
    matrix_[2][2] = cos(mov);

  } else if (value_coordinate == Coordinate::kZ) {
    matrix_[0][0] = cos(-mov);
    matrix_[0][1] = -sin(-mov);
    matrix_[1][0] = sin(-mov);
    matrix_[1][1] = cos(-mov);
  }
}

AffineTransformation::Matrix AffineTransformation::GetMatrix() const {
  return matrix_;
}