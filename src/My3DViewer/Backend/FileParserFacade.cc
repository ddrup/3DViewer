#include "FileParserFacade.h"

#include <iostream>

s21::FileHandler::FileHandler(const std::string& filePath) {
  file.open(filePath, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filePath;
  }
}

s21::FileHandler::~FileHandler() {
  if (file.is_open()) {
    file.close();
  }
}

s21::Parser::Parser()
    : mRegexF_1(R"(^f\s+(-?\d+)\/\S+\s+(-?\d+)\/\S+\s+(-?\d+)\/\S+)"),
      mRegexF_2(R"(^f\s+(-?\d+)\s+(-?\d+)\s+(-?\d+))"),
      mRegexF_3(R"(^f\s+(-?\d+)\s+(-?\d+))"),
      mRegexV(R"(^v\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(-?\d+.?\d*))") {}

s21::Parser::~Parser() {}

std::optional<std::array<float, 3>> s21::Parser::parseIndices(
    const std::string& line) {
  if (regex_search(line, mSmatch, mRegexF_1) && mSmatch.size() == 4) {
    return std::array<float, 3>{std::stof(mSmatch[1].str()),
                                std::stof(mSmatch[2].str()),
                                std::stof(mSmatch[3].str())};
  } else if (regex_search(line, mSmatch, mRegexF_2) && mSmatch.size() == 4) {
    return std::array<float, 3>{std::stof(mSmatch[1].str()),
                                std::stof(mSmatch[2].str()),
                                std::stof(mSmatch[3].str())};
  } else if (regex_search(line, mSmatch, mRegexF_3) && mSmatch.size() == 3) {
    return std::array<float, 3>{std::stof(mSmatch[1].str()),
                                std::stof(mSmatch[2].str()),
                                std::stof(mSmatch[2].str())};
  }
  return std::nullopt;
}
std::optional<std::array<float, 3>> s21::Parser::parseVertex(
    const std::string& line) {
  if (regex_search(line, mSmatch, mRegexV)) {
    return std::array<float, 3>{std::stof(mSmatch[1].str()),
                                std::stof(mSmatch[2].str()),
                                std::stof(mSmatch[3].str())};
  }
  return std::nullopt;
}

s21::FileParserFacade::FileParserFacade(const std::string& filePath)
    : mFileHandler(filePath), mParser() {}
s21::FileParserFacade::~FileParserFacade() {}

const std::vector<float>& s21::FileParserFacade::getVertexes() {
  return mVertexes;
}

const std::vector<unsigned int>& s21::FileParserFacade::getIndexes() {
  return mIndexes;
}

bool s21::FileParserFacade::processFile() {
  if (mFileHandler.file.is_open()) {
    std::optional<std::array<float, 3>> result;
    std::string line;
    while (getline(mFileHandler.file, line)) {
      if ((result = mParser.parseIndices(line)).has_value()) {
        std::array<float, 3> values = result.value();
        mIndexes.push_back(values[0] > 0 ? values[0] - 1
                                         : mVertexCount + values[0]);
        mIndexes.push_back(values[1] > 0 ? values[1] - 1
                                         : mVertexCount + values[1]);
        mIndexes.push_back(values[1] > 0 ? values[1] - 1
                                         : mVertexCount + values[1]);
        mIndexes.push_back(values[2] > 0 ? values[2] - 1
                                         : mVertexCount + values[2]);
        mIndexes.push_back(values[2] > 0 ? values[2] - 1
                                         : mVertexCount + values[2]);
        mIndexes.push_back(values[0] > 0 ? values[0] - 1
                                         : mVertexCount + values[0]);
      } else if ((result = mParser.parseVertex(line)).has_value()) {
        std::array<float, 3> values = result.value();
        mVertexes.push_back(values[0]);
        mVertexes.push_back(values[1]);
        mVertexes.push_back(values[2]);
        mVertexCount++;
      }
    }
    normalizeCoords(mVertexes);
    CenterVertex();
    mFileHandler.file.clear();                  // Сброс флага eof
    mFileHandler.file.seekg(0, std::ios::beg);  // Возврат к началу файла
    return true;
  }
  return false;
}

void s21::FileParserFacade::normalizeCoords(std::vector<float>& coords) {
  // Найдем минимальные и максимальные значения
  float minX = *std::min_element(coords.begin(), coords.end());
  float maxX = *std::max_element(coords.begin(), coords.end());

  // Вычислим коэффициенты масштабирования
  float scale = 2.0f / (maxX - minX);
  float offset = -0.5f * (maxX + minX) * scale;

  for (std::vector<float>::iterator it = coords.begin(); it != coords.end();
       ++it) {
    *it = *it * scale + offset;
  }
}
void s21::FileParserFacade::CenterVertex() {
  double d_x = s21Max(s21::Coordinate::kX) - s21Min(s21::Coordinate::kX);
  double d_y = s21Max(s21::Coordinate::kY) - s21Min(s21::Coordinate::kY);
  double d_z = s21Max(s21::Coordinate::kZ) - s21Min(s21::Coordinate::kZ);

  double center_x = s21Min(s21::Coordinate::kX) + d_x / 2;
  double center_y = s21Min(s21::Coordinate::kY) + d_y / 2;
  double center_z = s21Min(s21::Coordinate::kZ) + d_z / 2;

  for (size_t i = 0; i < mVertexes.size(); i += 3) {
    mVertexes[i] -= center_x;
    mVertexes[i + 1] -= center_y;
    mVertexes[i + 2] -= center_z;
  }

  double d_max = fmax(d_x, std::fmax(d_y, d_z));
  double scale = (0.5 - (0.5 * (-1))) / d_max;

  for (size_t i = 0; i < mVertexes.size(); ++i) {
    mVertexes[i] *= scale;
  }
}
float s21::FileParserFacade::s21Max(Coordinate value_coordinate) {
  size_t i = static_cast<size_t>(value_coordinate);
  float max_value = mVertexes[i];

  for (; i < mVertexes.size(); i += 3) {
    if (max_value < mVertexes[i]) {
      max_value = mVertexes[i];
    }
  }
  return max_value;
}

float s21::FileParserFacade::s21Min(Coordinate value_coordinate) {
  size_t i = static_cast<size_t>(value_coordinate);
  float min_value = mVertexes[i];

  for (; i < mVertexes.size(); i += 3) {
    if (min_value > mVertexes[i]) {
      min_value = mVertexes[i];
    }
  }
  return min_value;
}
