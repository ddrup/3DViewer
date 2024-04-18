#include "s21_Viewer.h"
/* @brief
 * Function to create a new matrix
 * 0 - SUCCESS
 * 1 - incorrect matrix error
 */
int s21_createMatrix(int rows, int columns, s21_MatrixPoints* matrixPoints) {
  if (!matrixPoints) return NPE;
  if (rows < 1 || columns < 1) return ERR_MAT;
  int flag = SUCCESS;

  matrixPoints->rows = rows;
  matrixPoints->columns = columns;
  matrixPoints->matrix =
      (double**)calloc(rows * columns + rows, sizeof(double*));
  flag = ERR_MAT;
  if (matrixPoints->matrix != NULL) {
    double* ptr = (double*)(matrixPoints->matrix + rows);
    for (int i = 0; i < rows; i++) matrixPoints->matrix[i] = ptr + columns * i;
    flag = SUCCESS;
  }
  return flag;
}

/* @brief
// Function to remove a matrix and free its memory
*/
void s21_removeMatrix(s21_MatrixPoints* matrixPoints) {
  if (!matrixPoints) return;
  if (matrixPoints->matrix != NULL) {
    free(matrixPoints->matrix);
    matrixPoints->matrix = NULL;
  }
  matrixPoints->rows = 0;
  matrixPoints->columns = 0;
}

/* @brief
 *  Function to calloc a matrix
 *  error=0 - SUCCESS
 *  error=1 - null pointer error | incorrect matrix error
 */
s21_MatrixPoints* s21_callocMatrix(s21_MatrixPoints* matrixPoints,
                                   int increaseRows, int increaseColumns,
                                   int* error) {
  if (!matrixPoints) {
    *error = NPE;
    return NULL;
  }
  if (matrixPoints->rows < 1 || matrixPoints->columns < 1) {
    *error = ERR_MAT;
    return NULL;
  }
  if (!matrixPoints->matrix) {
    *error = ERR_MAT;
    return NULL;
  }
  s21_MatrixPoints* newMatrixPoints =
      (s21_MatrixPoints*)calloc(1, sizeof(s21_MatrixPoints));
  s21_createMatrix(matrixPoints->rows + increaseRows,
                   matrixPoints->columns + increaseColumns, newMatrixPoints);
  for (int i = 0; i < matrixPoints->rows; i++) {
    for (int j = 0; j < matrixPoints->columns; j++) {
      newMatrixPoints->matrix[i][j] = matrixPoints->matrix[i][j];
    }
  }
  free(matrixPoints->matrix);
  free(matrixPoints);
  *error = SUCCESS;
  return newMatrixPoints;
}
