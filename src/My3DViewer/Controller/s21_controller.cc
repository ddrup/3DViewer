#include "s21_controller.h"

namespace s21 {

const std::vector<float>& Controller::getVertexes() const {
  return FileParserModel_->getVertexes();
}

const std::vector<unsigned int>& Controller::getIndexes() const {
  return FileParserModel_->getIndexes();
}

void Controller::glRotate(double mov, Coordinate value_coordinate) {
  AffineTransformation::GetInstance().glRotate(mov, value_coordinate);
}

void Controller::glTranslated(double mov, Coordinate value_coordinate) {
  AffineTransformation::GetInstance().glTranslated(mov, value_coordinate);
}

void Controller::glScaled(double scale_factor) {
  AffineTransformation::GetInstance().glScaled(scale_factor);
}

std::vector<std::vector<float>> Controller::getMatrix() const {
  return AffineTransformation::GetInstance().GetMatrix();
}

}  // namespace s21
