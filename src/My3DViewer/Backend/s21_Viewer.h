#ifndef S21_VIEWER_H
#define S21_VIEWER_H

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NPE 1

#define ERR_MAT 1
#define ERR_VECTOR 1
#define SUCCESS 0

typedef struct {
  int *data;
  int size;
  int capacity;
} s21_Vector;

typedef struct s21_MatrixPoints {
  double **matrix;
  int rows;
  int columns;
} s21_MatrixPoints;

typedef struct s21_Vertex {
  int amountVert;
  s21_MatrixPoints *coord;
  double minMaxX[2];
  double minMaxY[2];
  double minMaxZ[2];
} s21_Vertex;

typedef struct s21_Polygons {
  int amountPolyg;
  int capacity;
  s21_Vector **polygons;
} s21_Polygons;

typedef struct s21_Object3D {
  s21_Vertex *v;
  s21_Polygons *p;
} s21_Object3D;

int s21_createMatrix(int rows, int columns, s21_MatrixPoints *matrixPoints);
void s21_removeMatrix(s21_MatrixPoints *matrixPoints);
s21_MatrixPoints *s21_callocMatrix(s21_MatrixPoints *matrixPoints,
                                   int increaseRows, int increaseColumns,
                                   int *error);

void s21_vectorPushBack(s21_Vector *vector, int value);
int s21_vectorGet(s21_Vector *vector, int index);
void s21_vectorFree(s21_Vector *vector);

double s21_atof(char *str, int *numLength);
int s21_atoi(char *str, int *numLength);

int s21_extractPolygon(char *str, s21_Object3D *object3D);
int s21_extractCoordinates(char *str, s21_Object3D *object3D);
int s21_parseObjFile(char *str, s21_Object3D *object3D);

#endif  // S21_VIEWER_H
