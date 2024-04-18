#ifndef SRC_S21_AFFINE_TRANSFORMATION_H_
#define SRC_S21_AFFINE_TRANSFORMATION_H_

#include <stdio.h>

#include "s21_Viewer.h"

#define PI 3.14159265358979323846264

#define OK 0
#define ERROR 1

typedef enum Coordinate { X = 0, Y = 1, Z = 2 } coordinate;

int s21_centerVertex(s21_Vertex *vertex);
double s21_min(s21_MatrixPoints *vetrexCoordinates, coordinate valueCoordinate);
double s21_max(s21_MatrixPoints *vetrexCoordinates, coordinate valueCoordinate);

int s21_glTranslated(s21_MatrixPoints *vetrexCoordinates, double mov,
                     coordinate valueCoordinate);
int s21_glScaled(s21_MatrixPoints *vetrexCoordinates, double scaleFactor,
                 double lastScaleFactor);
int s21_glRotate(s21_MatrixPoints *vetrexCoordinates, double mov,
                 coordinate valueCoordinate);
int s21_check_correct_matrix(s21_MatrixPoints *vetrexCoordinates);

#endif  // SRC_S21_AFFINE_TRANSFORMATION_H_
