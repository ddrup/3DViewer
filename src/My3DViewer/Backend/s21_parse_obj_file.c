#include "s21_Viewer.h"

int s21_parseObjFile(char *str, s21_Object3D *object3D) {
  if (!str || !object3D) return NPE;
  int index = 0;
  if (str[index] == ' ') {
    while (str[index] == ' ') index++;
  }
  if (str[index] == 'v' && str[index + 1] == ' ') {
    s21_extractCoordinates(str, object3D);
  } else if (str[index] == 'f' && str[index + 1] == ' ') {
    s21_extractPolygon(str, object3D);
  }
  return SUCCESS;
}

int s21_extractCoordinates(char *str, s21_Object3D *object3D) {
  if (!str || !object3D) return NPE;
  int error = SUCCESS;
  int flagOneCoord = 0;
  if (object3D->v->amountVert == 0) {
    error = s21_createMatrix(1000, 3, object3D->v->coord);
    flagOneCoord = 1;
  } else if (object3D->v->amountVert == object3D->v->coord->rows) {
    object3D->v->coord = s21_callocMatrix(
        object3D->v->coord, object3D->v->amountVert * 2, 0, &error);
  }
  int numLength = 0;
  int lastCoord = object3D->v->amountVert;
  if (error == SUCCESS) {
    for (int i = 0; i < 3; i++) {
      while (!isdigit(*str) && *str != '\0' && *str != '-') str++;
      object3D->v->coord->matrix[lastCoord][i] = s21_atof(str, &numLength);
      str += numLength;
    }
    object3D->v->amountVert++;
    if (flagOneCoord) {
      object3D->v->minMaxX[1] = object3D->v->coord->matrix[lastCoord][0];
      object3D->v->minMaxX[0] = object3D->v->coord->matrix[lastCoord][0];
      object3D->v->minMaxY[1] = object3D->v->coord->matrix[lastCoord][1];
      object3D->v->minMaxY[0] = object3D->v->coord->matrix[lastCoord][1];
      object3D->v->minMaxZ[1] = object3D->v->coord->matrix[lastCoord][2];
      object3D->v->minMaxZ[0] = object3D->v->coord->matrix[lastCoord][2];
    }
    if (object3D->v->coord->matrix[lastCoord][0] > object3D->v->minMaxX[1])
      object3D->v->minMaxX[1] = object3D->v->coord->matrix[lastCoord][0];
    if (object3D->v->coord->matrix[lastCoord][0] < object3D->v->minMaxX[0])
      object3D->v->minMaxX[0] = object3D->v->coord->matrix[lastCoord][0];
    if (object3D->v->coord->matrix[lastCoord][1] > object3D->v->minMaxY[1])
      object3D->v->minMaxY[1] = object3D->v->coord->matrix[lastCoord][1];
    if (object3D->v->coord->matrix[lastCoord][1] < object3D->v->minMaxY[0])
      object3D->v->minMaxY[0] = object3D->v->coord->matrix[lastCoord][1];
    if (object3D->v->coord->matrix[lastCoord][2] > object3D->v->minMaxZ[1])
      object3D->v->minMaxZ[1] = object3D->v->coord->matrix[lastCoord][2];
    if (object3D->v->coord->matrix[lastCoord][2] < object3D->v->minMaxZ[0])
      object3D->v->minMaxZ[0] = object3D->v->coord->matrix[lastCoord][2];
  }
  return error;
}

int s21_extractPolygon(char *str, s21_Object3D *object3D) {
  if (!str || !object3D) return NPE;
  int error = SUCCESS;
  int numPolygon = object3D->p->amountPolyg;
  if (!object3D->p->polygons) {
    object3D->p->polygons = (s21_Vector **)calloc(1000, sizeof(s21_Vector *));
    if (!object3D->p->polygons) error = NPE;
    object3D->p->capacity = 1000;
  }
  if (object3D->p->amountPolyg == object3D->p->capacity) {
    object3D->p->polygons = (s21_Vector **)realloc(
        object3D->p->polygons,
        object3D->p->capacity * 2 * sizeof(s21_Vector *));
    if (!object3D->p->polygons) error = NPE;
    object3D->p->capacity *= 2;
  }
  object3D->p->polygons[numPolygon] =
      (s21_Vector *)calloc(1, sizeof(s21_Vector));
  if (!object3D->p->polygons[numPolygon]) error = NPE;
  int numLength = 0;
  if (error == SUCCESS) {
    for (; *str != '\0';) {
      while (!isdigit(*str) && *str != '\0' && *str != '-') str++;
      int tmp = s21_atoi(str, &numLength);
      // if(tmp < 0) tmp*=-1;
      if (tmp < 0) tmp = object3D->v->amountVert + tmp + 1;
      s21_vectorPushBack(object3D->p->polygons[numPolygon], tmp);
      str += numLength;
      if (*str == '/') {
        for (; *str != ' ' && *str != '\0';) str++;
      }
      while (!isdigit(*str) && *str != '\0' && *str != '-') str++;
    }
    object3D->p->amountPolyg++;
  }
  return error;
}
