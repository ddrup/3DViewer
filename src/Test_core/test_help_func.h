#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../My3DViewer/Backend/s21_Viewer.h"
#include "../My3DViewer/Backend/s21_affine_transformation.h"

#endif  // TEST_HEADER_H

START_TEST(create_matrix_test1) {
  s21_MatrixPoints *Si = NULL;
  int rows = 3;
  int columns = 3;
  ck_assert_int_eq(NPE, s21_createMatrix(rows, columns, Si));
}

END_TEST

START_TEST(calloc_matrix_test1) {
  int error = 0;
  s21_callocMatrix(NULL, 1, 1, &error);
  ck_assert_int_eq(error, NPE);
  s21_MatrixPoints matrix = {0};
  s21_callocMatrix(&matrix, 1, 1, &error);
  ck_assert_int_eq(error, ERR_MAT);
  matrix.columns = 2;
  matrix.rows = 2;
  s21_callocMatrix(&matrix, 1, 1, &error);
  ck_assert_int_eq(error, ERR_MAT);
}

END_TEST

START_TEST(atof_test1) {
  char str[32] = "  1.2345e2";
  int indexStr = 0;
  double result = 0;
  result = s21_atof(str, &indexStr);
  ck_assert_ldouble_eq_tol(result, 123.45, 1e-2);
}

END_TEST

START_TEST(atof_test2) {
  char str[32] = "  100.2345e-2";
  int indexStr = 0;
  double result = 0;
  result = s21_atof(str, &indexStr);
  ck_assert_ldouble_eq_tol(result, 1.002345, 1e-6);
}

END_TEST

START_TEST(atoi_test1) {
  char str[32] = "  12345";
  int indexStr = 0;
  int result = 0;
  result = s21_atoi(str, &indexStr);
  ck_assert_int_eq(result, 12345);
}

END_TEST
