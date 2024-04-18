#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../My3DViewer/Backend/s21_Viewer.h"
#include "../My3DViewer/Backend/s21_affine_transformation.h"

#endif  // TEST_HEADER_H

START_TEST(vectors_test1) {
  int size = 3;
  int one = 1;
  int two = 2;
  s21_Vector **xs = (s21_Vector **)calloc(size, sizeof(s21_Vector *));
  for (int i = 0; i < size; i++) {
    xs[i] = (s21_Vector *)calloc(1, sizeof(s21_Vector));
  }
  for (int i = 0; i < size; i++) {
    s21_vectorPushBack(xs[i], one);
    s21_vectorPushBack(xs[i], two);
  }
  for (int i = 0; i < size; i++) {
    int rez1 = s21_vectorGet(xs[i], 0);
    int rez2 = s21_vectorGet(xs[i], 1);
    ck_assert_int_eq(rez1, one);
    ck_assert_int_eq(rez2, two);
  }
  ck_assert_int_eq(s21_vectorGet(xs[1], 100), ERR_VECTOR);
  for (int i = 0; i < size; i++) {
    free(xs[i]->data);
    free(xs[i]);
  }
  free(xs);
}

END_TEST

START_TEST(extractPolygon_test1) {
  printf("\nextractPolygon_test1\n");
  char str1[256] = "f 2 1 3 5  s d f  6 7 8";
  char str2[256] = "f 1 3 4";
  int array[2][10] = {{2, 1, 3, 5, 6, 7, 8}, {1, 3, 4}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->p = (s21_Polygons *)calloc(1, sizeof(s21_Polygons));
  int error = s21_extractPolygon(str1, object3D);
  if (error == NPE) ck_assert_int_eq(error, SUCCESS);
  error = s21_extractPolygon(str2, object3D);
  if (error == NPE) ck_assert_int_eq(error, SUCCESS);
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    printf("f");
    for (int j = 0; j < object3D->p->polygons[i]->size; j++) {
      int result = s21_vectorGet(object3D->p->polygons[i], j);
      printf(" %d;", result);
      ck_assert_int_eq(array[i][j], result);
    }
    printf("\n");
  }
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    free(object3D->p->polygons[i]->data);
    free(object3D->p->polygons[i]);
  }
  free(object3D->p->polygons);
  free(object3D->p);
  free(object3D);
}

END_TEST

START_TEST(extractPolygon_test2) {
  printf("\nextractPolygon_test2\n");
  char str1[256] = "f 1! 3 4\0";
  char str2[256] = "f 1 3; 4\0";
  char str3[256] = "f 1 3 $$ 4\0";
  char str4[256] = "f sd 1 3 4\0";
  char str5[256] = "f 1 3 4 gh\0";
  int array[10] = {1, 3, 4};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->p = (s21_Polygons *)calloc(1, sizeof(s21_Polygons));
  s21_extractPolygon(str1, object3D);
  s21_extractPolygon(str2, object3D);
  s21_extractPolygon(str3, object3D);
  s21_extractPolygon(str4, object3D);
  s21_extractPolygon(str5, object3D);
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    printf("f");
    for (int j = 0; j < object3D->p->polygons[i]->size; j++) {
      int result = s21_vectorGet(object3D->p->polygons[i], j);
      printf(" %d;", result);
      ck_assert_int_eq(array[j], result);
    }
    printf("\n");
  }
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    free(object3D->p->polygons[i]->data);
    free(object3D->p->polygons[i]);
  }
  free(object3D->p->polygons);
  free(object3D->p);
  free(object3D);
}

END_TEST

START_TEST(extractPolygon_test3) {
  printf("\nextractPolygon_test3\n");
  char str1[256] = "f 1";
  char str2[256] = "f 1 4";
  char str3[256] = "f 1 3 4";
  char str4[256] = "f 2 1 3 4";
  char str5[256] = "f 1 3 4 5 6";
  int array[5][10] = {{1}, {1, 4}, {1, 3, 4}, {2, 1, 3, 4}, {1, 3, 4, 5, 6}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->p = (s21_Polygons *)calloc(1, sizeof(s21_Polygons));
  s21_extractPolygon(str1, object3D);
  s21_extractPolygon(str2, object3D);
  s21_extractPolygon(str3, object3D);
  s21_extractPolygon(str4, object3D);
  s21_extractPolygon(str5, object3D);
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    printf("f");
    for (int j = 0; j < object3D->p->polygons[i]->size; j++) {
      int result = s21_vectorGet(object3D->p->polygons[i], j);
      printf(" %d;", result);
      ck_assert_int_eq(array[i][j], result);
    }
    printf("\n");
  }
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    free(object3D->p->polygons[i]->data);
    free(object3D->p->polygons[i]);
  }
  free(object3D->p->polygons);
  free(object3D->p);
  free(object3D);
}

END_TEST

START_TEST(extractCoordinates_test1) {
  printf("\nextractCoordinates_test1\n");
  char str1[256] = "v 1.234 2.345 1.111 12.0 ";
  double array[1][3] = {{1.234, 2.345, 1.111}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_extractCoordinates(str1, object3D);
  for (int i = 0; i < object3D->v->amountVert; i++) {
    printf("v:");
    for (int j = 0; j < object3D->v->coord->columns; j++) {
      printf(" %lf;", object3D->v->coord->matrix[i][j]);
      ck_assert_ldouble_eq_tol(object3D->v->coord->matrix[i][j], array[i][j],
                               1e-7);
    }
    printf("\n");
  }
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->v);
  free(object3D);
}

END_TEST

START_TEST(extractCoordinates_test2) {
  printf("\nextractCoordinates_test2\n");
  char str1[256] = "v 1.234 2.345 1.111 12.0 ";
  char str2[256] = "v 1.234 ggg2.345 hhhh1.111ghhhh 12.0 hhhhh ";
  double array[2][3] = {{1.234, 2.345, 1.111}, {1.234, 2.345, 1.111}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_extractCoordinates(str1, object3D);
  s21_extractCoordinates(str2, object3D);
  for (int i = 0; i < object3D->v->amountVert; i++) {
    printf("v:");
    for (int j = 0; j < object3D->v->coord->columns; j++) {
      printf(" %lf;", object3D->v->coord->matrix[i][j]);
      ck_assert_ldouble_eq_tol(object3D->v->coord->matrix[i][j], array[i][j],
                               1e-7);
    }
    printf("\n");
  }
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->v);
  free(object3D);
}

END_TEST

START_TEST(extractCoordinates_test3) {
  printf("\nextractCoordinates_test3\n");
  char str1[256] = "v 1.234 2.345 1.111 12.0 ";
  char str2[256] = "v 1.234 ggg2.345 hhhh1.111ghhhh 12.0 hhhhh ";
  char str3[256] = "v -1.234 2 10 1.0 ";
  double array[3][3] = {
      {1.234, 2.345, 1.111}, {1.234, 2.345, 1.111}, {-1.234, 2.0, 10}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_extractCoordinates(str1, object3D);
  s21_extractCoordinates(str2, object3D);
  s21_extractCoordinates(str3, object3D);
  for (int i = 0; i < object3D->v->amountVert; i++) {
    printf("v:");
    for (int j = 0; j < object3D->v->coord->columns; j++) {
      printf(" %lf;", object3D->v->coord->matrix[i][j]);
      ck_assert_ldouble_eq_tol(object3D->v->coord->matrix[i][j], array[i][j],
                               1e-7);
    }
    printf("\n");
  }
  printf("=%lf\n", object3D->v->minMaxX[0]);
  printf("=%lf\n", object3D->v->minMaxX[1]);
  printf("=%lf\n", object3D->v->minMaxY[0]);
  printf("=%lf\n", object3D->v->minMaxY[1]);
  printf("=%lf\n", object3D->v->minMaxZ[0]);
  printf("=%lf\n", object3D->v->minMaxZ[1]);
  ck_assert_double_eq_tol(object3D->v->minMaxX[0], array[2][0], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxX[1], array[0][0], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxY[0], array[2][1], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxY[1], array[0][1], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxZ[0], array[0][2], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxZ[1], array[2][2], 1e-7);
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->v);
  free(object3D);
}

END_TEST

START_TEST(extractCoordinates_test4) {
  printf("\nextractCoordinates_test4\n");
  char str1[256] = "v 1.234 -2.345 10 12.0 ";
  char str2[256] = "v 1.234 ggg-2.345 hhhh1.111ghhhh 12.0 hhhhh ";
  char str3[256] = "v 10.234 2 10 12.0 ";
  double array[3][3] = {
      {1.234, -2.345, 10}, {1.234, -2.345, 1.111}, {10.234, 2.0, 10.0}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_extractCoordinates(str1, object3D);
  s21_extractCoordinates(str2, object3D);
  s21_extractCoordinates(str3, object3D);
  for (int i = 0; i < object3D->v->amountVert; i++) {
    printf("v:");
    for (int j = 0; j < object3D->v->coord->columns; j++) {
      printf(" %lf;", object3D->v->coord->matrix[i][j]);
      ck_assert_ldouble_eq_tol(object3D->v->coord->matrix[i][j], array[i][j],
                               1e-7);
    }
    printf("\n");
  }
  printf("=%lf\n", object3D->v->minMaxX[0]);
  printf("=%lf\n", object3D->v->minMaxX[1]);
  printf("=%lf\n", object3D->v->minMaxY[0]);
  printf("=%lf\n", object3D->v->minMaxY[1]);
  printf("=%lf\n", object3D->v->minMaxZ[0]);
  printf("=%lf\n", object3D->v->minMaxZ[1]);
  ck_assert_double_eq_tol(object3D->v->minMaxX[0], array[0][0], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxX[1], array[2][0], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxY[0], array[0][1], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxY[1], array[2][1], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxZ[0], array[1][2], 1e-7);
  ck_assert_double_eq_tol(object3D->v->minMaxZ[1], array[0][2], 1e-7);
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->v);
  free(object3D);
}

END_TEST

START_TEST(parseObjFile_test1) {
  printf("\nparseObjFile_test1\n");
  char str1[256] = "v 1.234 -2.345 1.111 12.0 ";
  char str2[256] = "v 1.234 ggg-2.345 hhhh1.111ghhhh 12.0 hhhhh ";
  char str3[256] = "v -1.234 2 10 12.0 ";
  char str4[256] = "f 1";
  char str5[256] = "f 1 4";
  char str6[256] = "f 1 3 4";
  char str7[256] = "f 2 1 3 4";
  char str8[256] = "f 1 3 4 5 6";
  double array1[3][3] = {
      {1.234, -2.345, 1.111}, {1.234, -2.345, 1.111}, {-1.234, 2.0, 10.0}};
  int array2[5][10] = {{1}, {1, 4}, {1, 3, 4}, {2, 1, 3, 4}, {1, 3, 4, 5, 6}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->p = (s21_Polygons *)calloc(1, sizeof(s21_Polygons));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));

  s21_parseObjFile(str1, object3D);
  s21_parseObjFile(str2, object3D);
  s21_parseObjFile(str3, object3D);
  for (int i = 0; i < object3D->v->amountVert; i++) {
    printf("v:");
    for (int j = 0; j < object3D->v->coord->columns; j++) {
      printf(" %lf;", object3D->v->coord->matrix[i][j]);
      ck_assert_ldouble_eq_tol(object3D->v->coord->matrix[i][j], array1[i][j],
                               1e-7);
    }
    printf("\n");
  }
  s21_parseObjFile(str4, object3D);
  s21_parseObjFile(str5, object3D);
  s21_parseObjFile(str6, object3D);
  s21_parseObjFile(str7, object3D);
  s21_parseObjFile(str8, object3D);
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    printf("f");
    for (int j = 0; j < object3D->p->polygons[i]->size; j++) {
      int result = s21_vectorGet(object3D->p->polygons[i], j);
      printf(" %d;", result);
      ck_assert_int_eq(array2[i][j], result);
    }
    printf("\n");
  }

  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    free(object3D->p->polygons[i]->data);
    free(object3D->p->polygons[i]);
  }
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->p->polygons);
  free(object3D->v);
  free(object3D->p);
  free(object3D);
}
END_TEST

START_TEST(parseObjFile_test2) {
  printf("\nparseObjFile_test2\n");
  char str1[256] = "v 1.234 -2.345 1.111 12.0 ";
  char str2[256] = "f 1 3 4 5 6";
  // double array1[3] = {1.234, -2.345, 1.111};
  // int array2[10] = {1, 3, 4, 5, 6};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->p = (s21_Polygons *)calloc(1, sizeof(s21_Polygons));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));

  for (int i = 0; i < 1000050; i++) {
    s21_parseObjFile(str1, object3D);
  }
  // for(int i=0; i< object3D->v->amountVert; i++){
  //     printf("v:");
  //     for(int j=0; j< object3D->v->coord->columns; j++){
  //         printf(" %lf;", object3D->v->coord->matrix[i][j]);
  //         ck_assert_ldouble_eq_tol(object3D->v->coord->matrix[i][j],
  //         array1[j], 1e-7);
  //     }
  //     printf("\n");
  // }
  for (int i = 0; i < 1000050; i++) {
    s21_parseObjFile(str2, object3D);
  }
  // for(int i=0; i< object3D->p->amountPolyg; i++){
  //     printf("f");
  //     for(int j=0; j< object3D->p->polygons[i]->size; j++){
  //         int result = s21_vectorGet(object3D->p->polygons[i], j);
  //         printf(" %d;", result);
  //         ck_assert_int_eq(array2[j], result);
  //     }
  //     printf("\n");
  // }

  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    free(object3D->p->polygons[i]->data);
    free(object3D->p->polygons[i]);
  }
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->p->polygons);
  free(object3D->v);
  free(object3D->p);
  free(object3D);
}
END_TEST

START_TEST(callocMatrix_test) {
  int error = 0;
  s21_MatrixPoints *coord =
      (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));
  s21_createMatrix(1000, 3, coord);
  coord = s21_callocMatrix(coord, 1000 * 1000, 0, &error);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_int_eq(coord->rows, 1001000);
  ck_assert_int_eq(coord->columns, 3);
  for (int i = 0; i < coord->rows; i++) {
    for (int j = 0; j < coord->columns; j++) {
      if (coord->matrix[i][j] != 0.0) printf("\nerror\n");
    }
  }
  free(coord->matrix);
  free(coord);
}
END_TEST

START_TEST(rellocPoligon_test) {
  int error = 0;
  s21_Vector **pol = (s21_Vector **)calloc(1000, sizeof(s21_Vector *));
  for (int i = 0; i < 1000; i++) {
    pol[i] = (s21_Vector *)calloc(1, sizeof(s21_Vector));
    s21_vectorPushBack(pol[i], 1);
  }
  pol = (s21_Vector **)realloc(pol, 1000000 * sizeof(s21_Vector *));
  for (int i = 1000; i < 1000000; i++) {
    pol[i] = (s21_Vector *)calloc(1, sizeof(s21_Vector));
    s21_vectorPushBack(pol[i], 1);
  }
  ck_assert_int_eq(SUCCESS, error);
  for (int i = 0; i < 1000000; i++) {
    if (s21_vectorGet(pol[i], 0) != 1) printf("\nerror\n");
  }
  for (int i = 0; i < 1000000; i++) {
    free(pol[i]->data);
    free(pol[i]);
  }
  free(pol);
}
END_TEST

START_TEST(parseObjFile_test3) {
  printf("\nparseObjFile_test3\n");
  char str4[256] = "f 1";
  char str5[256] = "f 1 4";
  char str6[256] = "f -704//-704 -703//-703 -738//-738   \n";
  char str7[256] = "f 2//2 1 3 4 ";
  char str8[256] = "f 1 3 4 5 6";
  int array2[5][10] = {
      {1}, {1, 4}, {-703, -702, -737}, {2, 1, 3, 4}, {1, 3, 4, 5, 6}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->p = (s21_Polygons *)calloc(1, sizeof(s21_Polygons));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));

  s21_parseObjFile(str4, object3D);
  s21_parseObjFile(str5, object3D);
  s21_parseObjFile(str6, object3D);
  s21_parseObjFile(str7, object3D);
  s21_parseObjFile(str8, object3D);
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    printf("f");
    for (int j = 0; j < object3D->p->polygons[i]->size; j++) {
      int result = s21_vectorGet(object3D->p->polygons[i], j);
      printf(" %d;", result);
      ck_assert_int_eq(array2[i][j],
                       result);  // trouble with brain(negative value)
    }
    printf("\n");
  }

  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    free(object3D->p->polygons[i]->data);
    free(object3D->p->polygons[i]);
  }
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->p->polygons);
  free(object3D->v);
  free(object3D->p);
  free(object3D);
}
END_TEST

START_TEST(parseObjFile_test4) {
  printf("\nparseObjFile_test3\n");
  char str4[256] = "  f 1e-3";
  char str5[256] = "f 1 4";
  char str6[256] = "f -704//-704 -703//-703 -738//-738   \n";
  char str7[256] = "f 2//2 1 3 4 ";
  char str8[256] = "f 1 3 4 5 6";
  int array2[5][10] = {
      {1, -2}, {1, 4}, {-703, -702, -737}, {2, 1, 3, 4}, {1, 3, 4, 5, 6}};
  s21_Object3D *object3D = (s21_Object3D *)calloc(1, sizeof(s21_Object3D));
  object3D->v = (s21_Vertex *)calloc(1, sizeof(s21_Vertex));
  object3D->p = (s21_Polygons *)calloc(1, sizeof(s21_Polygons));
  object3D->v->coord = (s21_MatrixPoints *)calloc(1, sizeof(s21_MatrixPoints));

  s21_parseObjFile(str4, object3D);
  s21_parseObjFile(str5, object3D);
  s21_parseObjFile(str6, object3D);
  s21_parseObjFile(str7, object3D);
  s21_parseObjFile(str8, object3D);
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    printf("f");
    for (int j = 0; j < object3D->p->polygons[i]->size; j++) {
      int result = s21_vectorGet(object3D->p->polygons[i], j);
      printf(" %d;", result);
      ck_assert_int_eq(array2[i][j], result);
    }
    printf("\n");
  }

  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    free(object3D->p->polygons[i]->data);
    free(object3D->p->polygons[i]);
  }
  free(object3D->v->coord->matrix);
  free(object3D->v->coord);
  free(object3D->p->polygons);
  free(object3D->v);
  free(object3D->p);
  free(object3D);
}
END_TEST

START_TEST(Test_vector) {
  s21_Vector *vector = (s21_Vector *)calloc(1, sizeof(s21_Vector));
  s21_vectorPushBack(vector, 5);
  s21_vectorFree(vector);
  free(vector);
}
END_TEST