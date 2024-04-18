#include "s21_Viewer.h"

void s21_vectorPushBack(s21_Vector *vector, int value) {
  if (!vector) return;
  if (!vector->data) {
    vector->capacity = 1;
    vector->data = (int *)calloc(vector->capacity, sizeof(int));
  } else if (vector->size == vector->capacity) {
    vector->capacity *= 2;
    vector->data = (int *)realloc(vector->data, vector->capacity * sizeof(int));
  }

  vector->data[vector->size++] = value;
}

int s21_vectorGet(s21_Vector *vector, int index) {
  if (!vector) return NPE;
  if (index < vector->size) {
    return vector->data[index];
  } else {
    return ERR_VECTOR;
  }
}

void s21_vectorFree(s21_Vector *vector) {
  free(vector->data);
  vector->data = NULL;
  vector->size = vector->capacity = 0;
}
