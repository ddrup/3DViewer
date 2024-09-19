#include <gtest/gtest.h>

#include "../Backend/FileParserFacade.h"
#include "../Backend/s21_affine_transformation.h"

TEST(FileParserFacade, Test1) {
  s21::FileParserFacade parser("My3DViewer/Test/for_test.obj");
  EXPECT_EQ(parser.processFile(), true);
  EXPECT_EQ(parser.getIndexes()[0], 4);
  EXPECT_EQ(parser.getIndexes()[1], 2);
  EXPECT_EQ(parser.getIndexes()[2], 2);
  EXPECT_EQ(parser.getIndexes()[3], 1);
  EXPECT_EQ(parser.getIndexes()[4], 1);
  EXPECT_EQ(parser.getIndexes()[5], 4);
  EXPECT_EQ(parser.getIndexes()[6], 1);
  EXPECT_EQ(parser.getVertexes()[4], 0.2f);
}

void CreateMatrix(std::vector<std::vector<float>>& matrix) {
  matrix = std::vector<std::vector<float>>(4, std::vector<float>(4, 0.0));
  for (size_t i = 0; i < matrix.size(); ++i) {
    matrix[i][i] = 1;
  }
}

TEST(TestAffineTransformation, Test2) {
  s21::AffineTransformation& obj = s21::AffineTransformation::GetInstance();

  obj.glScaled(2);
  obj.glTranslated(4, s21::Coordinate::kZ);

  s21::AffineTransformation::Matrix matrix;
  CreateMatrix(matrix);
  for (size_t i = 0; i < 3; ++i) {
    matrix[i][i] *= 2;
  }
  matrix[2][3] = 4;

  obj.glRotate(5, s21::Coordinate::kX);
  obj.glRotate(1, s21::Coordinate::kY);
  obj.glRotate(3, s21::Coordinate::kZ);

  matrix[0][0] = 0.99863f;
  matrix[0][1] = 0.052336f;
  matrix[0][2] = 0.0174524f;

  matrix[1][0] = -0.052336f;
  matrix[1][1] = 0.99863f;
  matrix[1][2] = -0.0871557f;

  matrix[2][0] = -0.0174524f;
  matrix[2][1] = 0.0871557f;
  matrix[2][2] = 0.999848f;

  float epsilon = 1e-5;
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      EXPECT_NEAR(obj.GetMatrix()[i][j], matrix[i][j], epsilon);
    }
  }
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
