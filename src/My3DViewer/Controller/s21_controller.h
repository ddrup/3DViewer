#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../Backend/FileParserFacade.h"
#include "../Backend/s21_affine_transformation.h"
namespace s21 {

class Controller {
 public:
  Controller(const std::string& filePath)
      : FileParserModel_(new FileParserFacade(filePath)) {
    if (!FileParserModel_->processFile()) {
      throw std::invalid_argument("File name is not correct!");
    }
  }
  ~Controller() { delete FileParserModel_; }

  void glRotate(double mov, Coordinate value_coordinate);
  void glTranslated(double mov, Coordinate value_coordinate);
  void glScaled(double scale_factor);

  const std::vector<float>& getVertexes() const;
  const std::vector<unsigned int>& getIndexes() const;
  std::vector<std::vector<float>> getMatrix() const;

 private:
  FileParserFacade* FileParserModel_;
};

}  // namespace s21

#endif  // CONTROLLER_H_
