#ifndef FILEPARSERFACADE_H
#define FILEPARSERFACADE_H

#include <array>
#include <cmath>
#include <fstream>
#include <optional>
#include <regex>
#include <string>
#include <vector>

#include "s21_affine_transformation.h"

namespace s21 {
// enum class Coordinate { kX = 0, kY = 1, kZ = 2 };
class FileHandler {
 public:
  FileHandler(const std::string& filePath);
  ~FileHandler();
  std::fstream file;
};

class Parser {
 public:
  Parser();
  ~Parser();
  std::optional<std::array<float, 3>> parseIndices(const std::string& line);
  std::optional<std::array<float, 3>> parseVertex(const std::string& line);

 private:
  const std::regex mRegexF_1;
  const std::regex mRegexF_2;
  const std::regex mRegexF_3;
  const std::regex mRegexV;
  std::smatch mSmatch;
};

class FileParserFacade {
 public:
  FileParserFacade(const std::string& filePath);
  ~FileParserFacade();
  const std::vector<float>& getVertexes();
  const std::vector<unsigned int>& getIndexes();
  bool processFile();

 private:
  void normalizeCoords(std::vector<float>& coords);
  void CenterVertex();
  float s21Max(Coordinate value_coordinate);
  float s21Min(Coordinate value_coordinate);
  FileHandler mFileHandler;
  Parser mParser;
  std::vector<float> mVertexes;
  std::vector<unsigned int> mIndexes;
  int mVertexCount = 0;
};
}  // namespace s21
#endif  // FILEPARSERFACADE_H
