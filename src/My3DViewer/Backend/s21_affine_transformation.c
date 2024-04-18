#include "s21_affine_transformation.h"

int s21_centerVertex(s21_Vertex *vertex) {  // check correct matrix, need or no?

  s21_MatrixPoints *vetrexCoordinates = vertex->coord;
  int errCode = OK;
  if (s21_check_correct_matrix(vetrexCoordinates)) {
    errCode = ERROR;
  } else {
    errCode = SUCCESS;
    double d_X = s21_max(vetrexCoordinates, X) - s21_min(vetrexCoordinates, X);
    double d_Y = s21_max(vetrexCoordinates, Y) - s21_min(vetrexCoordinates, Y);
    double d_Z = s21_max(vetrexCoordinates, Z) - s21_min(vetrexCoordinates, Z);
    double centerX = s21_min(vetrexCoordinates, X) + d_X / 2;
    double centerY = s21_min(vetrexCoordinates, Y) + d_Y / 2;
    double centerZ = s21_min(vetrexCoordinates, Z) + d_Z / 2;
    for (int i = 0; i < vetrexCoordinates->rows; i++) {
      vetrexCoordinates->matrix[i][0] -= centerX;
      vetrexCoordinates->matrix[i][1] -= centerY;
      vetrexCoordinates->matrix[i][2] -= centerZ;
    }
    double d_max = fmax(d_X, fmax(d_Y, d_Z));
    double scale =
        (0.5 - (0.5 * (-1))) / d_max;  // константа может не быть не корректной
    for (int i = 0; i < vetrexCoordinates->rows; i++) {
      vetrexCoordinates->matrix[i][0] *= scale;
      vetrexCoordinates->matrix[i][1] *= scale;
      vetrexCoordinates->matrix[i][2] *= scale;
    }
    vertex->minMaxX[0] = (vertex->minMaxX[0] - centerX) * scale;
    vertex->minMaxX[1] = (vertex->minMaxX[1] - centerX) * scale;
    vertex->minMaxY[0] = (vertex->minMaxY[0] - centerY) * scale;
    vertex->minMaxY[1] = (vertex->minMaxY[1] - centerY) * scale;
    vertex->minMaxZ[0] = (vertex->minMaxZ[0] - centerZ) * scale;
    vertex->minMaxZ[1] = (vertex->minMaxZ[1] - centerZ) * scale;
  }
  return errCode;
}

double s21_max(s21_MatrixPoints *vetrexCoordinates,
               coordinate valueCoordinate) {
  double maxValue = vetrexCoordinates->matrix[0][valueCoordinate];
  for (int i = 1; i < vetrexCoordinates->rows; i++) {
    if (vetrexCoordinates->matrix[i][valueCoordinate] > maxValue) {
      maxValue = vetrexCoordinates->matrix[i][valueCoordinate];
    }
  }
  return maxValue;
}

double s21_min(s21_MatrixPoints *vetrexCoordinates,
               coordinate valueCoordinate) {
  double minValue = vetrexCoordinates->matrix[0][valueCoordinate];
  for (int i = 1; i < vetrexCoordinates->rows; i++) {
    if (vetrexCoordinates->matrix[i][valueCoordinate] < minValue) {
      minValue = vetrexCoordinates->matrix[i][valueCoordinate];
    }
  }
  return minValue;
}

int s21_glTranslated(s21_MatrixPoints *vetrexCoordinates, double mov,
                     coordinate valueCoordinate) {
  int errCode = OK;
  if (s21_check_correct_matrix(vetrexCoordinates)) {
    errCode = ERROR;
  } else {
    for (int i = 0; i < vetrexCoordinates->rows; i++) {
      vetrexCoordinates->matrix[i][valueCoordinate] += mov;
    }
  }
  return errCode;
}

int s21_glScaled(s21_MatrixPoints *vetrexCoordinates, double scaleFactor,
                 double lastScaleFactor) {
  int errCode = OK;
  if (s21_check_correct_matrix(vetrexCoordinates)) {
    errCode = ERROR;
  } else {
    if (scaleFactor != 0 && lastScaleFactor != 0) {
      double scale = scaleFactor / lastScaleFactor;
      for (int i = 0; i < vetrexCoordinates->rows; i++) {
        for (int j = 0; j < vetrexCoordinates->columns; j++) {
          vetrexCoordinates->matrix[i][j] *= scale;
        }
      }
    }
  }
  return errCode;
}

int s21_glRotate(s21_MatrixPoints *vetrexCoordinates, double mov,
                 coordinate valueCoordinate) {
  int errCode = OK;
  if (s21_check_correct_matrix(vetrexCoordinates)) {
    errCode = ERROR;
  } else {
    mov = mov * PI / 180;
    for (int i = 0; i < vetrexCoordinates->rows; i++) {
      double x = vetrexCoordinates->matrix[i][0];
      double y = vetrexCoordinates->matrix[i][1];
      double z = vetrexCoordinates->matrix[i][2];
      if (valueCoordinate == Y) {
        vetrexCoordinates->matrix[i][0] = x * cos(mov) + z * sin(mov);
        vetrexCoordinates->matrix[i][2] = (-1) * x * sin(mov) + z * cos(mov);
      } else if (valueCoordinate == X) {
        vetrexCoordinates->matrix[i][1] = y * cos(mov) - z * sin(mov);
        vetrexCoordinates->matrix[i][2] = y * sin(mov) + z * cos(mov);
      } else {
        vetrexCoordinates->matrix[i][0] = x * cos(mov) - y * sin(mov);
        vetrexCoordinates->matrix[i][1] = x * sin(mov) + y * cos(mov);
      }
    }
  }
  return errCode;
}

int s21_check_correct_matrix(s21_MatrixPoints *vetrexCoordinates) {
  int errCode = OK;
  if (vetrexCoordinates == NULL || vetrexCoordinates->matrix == NULL) {
    errCode = ERROR;
  } else if (vetrexCoordinates->columns < 1 || vetrexCoordinates->rows < 1) {
    errCode = ERROR;
  }
  return errCode;
}
