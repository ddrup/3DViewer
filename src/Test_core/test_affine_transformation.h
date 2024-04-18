#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../My3DViewer/Backend/s21_Viewer.h"
#include "../My3DViewer/Backend/s21_affine_transformation.h"

#endif  // TEST_HEADER_H

START_TEST(test_affine_transformation_1) {
  s21_Vertex *input_matrix = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  input_matrix->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_Vertex *result = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  result->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_createMatrix(2, 3, input_matrix->coord);
  s21_createMatrix(2, 3, result->coord);
  // input matrix:
  input_matrix->coord->matrix[0][0] = 5;
  input_matrix->coord->matrix[0][1] = 4;
  input_matrix->coord->matrix[0][2] = 2;
  input_matrix->coord->matrix[1][0] = 5;
  input_matrix->coord->matrix[1][1] = 2;
  input_matrix->coord->matrix[1][2] = 0;

  // result matrix:
  result->coord->matrix[0][0] = 0;
  result->coord->matrix[0][1] = 0.5;
  result->coord->matrix[0][2] = 0.5;
  result->coord->matrix[1][0] = 0;
  result->coord->matrix[1][1] = -0.5;
  result->coord->matrix[1][2] = -0.5;

  s21_centerVertex(input_matrix);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(result->coord->matrix[i][j],
                          input_matrix->coord->matrix[i][j]);
    }
  }
  free(input_matrix->coord);
  free(result->coord);
  free(input_matrix);
  free(result);
}
END_TEST

START_TEST(test_affine_transformation_2) {
  s21_MatrixPoints input_matrix = {0};
  s21_MatrixPoints result = {0};
  int rows = 2;
  int columns = 3;
  // input matrix:
  s21_createMatrix(rows, columns, &input_matrix);
  input_matrix.matrix[0][0] = 10;
  input_matrix.matrix[0][1] = 3;
  input_matrix.matrix[0][2] = 2;
  input_matrix.matrix[1][0] = 11;
  input_matrix.matrix[1][1] = 5;
  input_matrix.matrix[1][2] = 4;

  // result matrix:
  s21_createMatrix(rows, columns, &result);
  result.matrix[0][0] = 20;
  result.matrix[0][1] = 6;
  result.matrix[0][2] = 4;
  result.matrix[1][0] = 22;
  result.matrix[1][1] = 10;
  result.matrix[1][2] = 8;

  s21_glScaled(&input_matrix, 2, 1);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], input_matrix.matrix[i][j]);
    }
  }
  s21_removeMatrix(&input_matrix);
  s21_removeMatrix(&result);
}
END_TEST

START_TEST(test_affine_transformation_3) {
  s21_MatrixPoints input_matrix = {0};
  s21_MatrixPoints result = {0};
  int rows = 2;
  int columns = 3;
  // input matrix:
  s21_createMatrix(rows, columns, &input_matrix);
  input_matrix.matrix[0][0] = 10;
  input_matrix.matrix[0][1] = 3;
  input_matrix.matrix[0][2] = 2;
  input_matrix.matrix[1][0] = 11;
  input_matrix.matrix[1][1] = 5;
  input_matrix.matrix[1][2] = 4;

  // result matrix:
  s21_createMatrix(rows, columns, &result);
  result.matrix[0][0] = 15;
  result.matrix[0][1] = 3;
  result.matrix[0][2] = 2;
  result.matrix[1][0] = 16;
  result.matrix[1][1] = 5;
  result.matrix[1][2] = 4;

  s21_glTranslated(&input_matrix, 5, 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], input_matrix.matrix[i][j]);
    }
  }
  s21_removeMatrix(&input_matrix);
  s21_removeMatrix(&result);
}
END_TEST

START_TEST(test_affine_transformation_4) {
  s21_MatrixPoints input_matrix = {0};
  s21_MatrixPoints result = {0};
  int rows = 2;
  int columns = 3;
  // input matrix:
  s21_createMatrix(rows, columns, &input_matrix);
  input_matrix.matrix[0][0] = 10;
  input_matrix.matrix[0][1] = 3;
  input_matrix.matrix[0][2] = 2;
  input_matrix.matrix[1][0] = 11;
  input_matrix.matrix[1][1] = 5;
  input_matrix.matrix[1][2] = 4;

  // result matrix:
  s21_createMatrix(rows, columns, &result);
  result.matrix[0][0] = 10;
  result.matrix[0][1] = 1.598076;
  result.matrix[0][2] = 3.232051;
  result.matrix[1][0] = 11;
  result.matrix[1][1] = 2.330127;
  result.matrix[1][2] = 5.964102;

  s21_glRotate(&input_matrix, 30, 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], input_matrix.matrix[i][j],
                              1e6);
    }
  }
  s21_removeMatrix(&input_matrix);
  s21_removeMatrix(&result);
}
END_TEST

START_TEST(test_affine_transformation_5) {
  s21_MatrixPoints input_matrix = {0};
  s21_MatrixPoints result = {0};
  int rows = 2;
  int columns = 3;
  // input matrix:
  s21_createMatrix(rows, columns, &input_matrix);
  input_matrix.matrix[0][0] = 10;
  input_matrix.matrix[0][1] = 3;
  input_matrix.matrix[0][2] = 2;
  input_matrix.matrix[1][0] = 11;
  input_matrix.matrix[1][1] = 5;
  input_matrix.matrix[1][2] = 4;

  // result matrix:
  s21_createMatrix(rows, columns, &result);
  result.matrix[0][0] = 9.660254;
  result.matrix[0][1] = 3;
  result.matrix[0][2] = -3.267949;
  result.matrix[1][0] = 11.526280;
  result.matrix[1][1] = 5;
  result.matrix[1][2] = -2.035898;

  s21_glRotate(&input_matrix, 30, 1);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], input_matrix.matrix[i][j],
                              1e6);
    }
  }
  s21_removeMatrix(&input_matrix);
  s21_removeMatrix(&result);
}
END_TEST

START_TEST(test_affine_transformation_6) {
  s21_MatrixPoints input_matrix = {0};
  s21_MatrixPoints result = {0};
  int rows = 2;
  int columns = 3;
  // input matrix:
  s21_createMatrix(rows, columns, &input_matrix);
  input_matrix.matrix[0][0] = 10;
  input_matrix.matrix[0][1] = 3;
  input_matrix.matrix[0][2] = 2;
  input_matrix.matrix[1][0] = 11;
  input_matrix.matrix[1][1] = 5;
  input_matrix.matrix[1][2] = 4;

  // result matrix:
  s21_createMatrix(rows, columns, &result);
  result.matrix[0][0] = 7.160254;
  result.matrix[0][1] = 7.598076;
  result.matrix[0][2] = 2;
  result.matrix[1][0] = 7.026279;
  result.matrix[1][1] = 9.830127;
  result.matrix[1][2] = 4;

  s21_glRotate(&input_matrix, 30, 2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], input_matrix.matrix[i][j],
                              1e6);
    }
  }
  s21_removeMatrix(&input_matrix);
  s21_removeMatrix(&result);
}
END_TEST

START_TEST(test_affine_transformation_7) {
  s21_Vertex *input_matrix = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  input_matrix->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_createMatrix(2, 1, input_matrix->coord);
  input_matrix->coord->rows = 0;
  int errCode = s21_centerVertex(input_matrix);
  ck_assert_int_eq(errCode, ERROR);
  free(input_matrix->coord);
  free(input_matrix);
}
END_TEST

START_TEST(test_affine_transformation_8) {
  s21_MatrixPoints input_matrix = {0};
  s21_createMatrix(2, 0, &input_matrix);

  int errCode = s21_glRotate(&input_matrix, 10, X);
  ck_assert_int_eq(errCode, ERROR);
}
END_TEST

START_TEST(test_affine_transformation_9) {
  s21_MatrixPoints input_matrix = {0};
  s21_createMatrix(2, 0, &input_matrix);

  int errCode = s21_glScaled(&input_matrix, 2, 1);
  ck_assert_int_eq(errCode, ERROR);
}
END_TEST

START_TEST(test_affine_transformation_10) {
  s21_MatrixPoints input_matrix = {0};
  s21_createMatrix(2, 3, &input_matrix);
  input_matrix.columns = 0;

  int errCode = s21_glTranslated(&input_matrix, 5, Y);
  ck_assert_int_eq(errCode, ERROR);
}
END_TEST