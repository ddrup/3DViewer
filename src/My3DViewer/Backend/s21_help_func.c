#include "s21_Viewer.h"

double s21_atof(char* str, int* numLength) {
  double result = 0.0;
  double fraction = 1.0;
  int sign = 1;
  int decimal = 0;
  int i = 0;
  while (str[i] == ' ') {
    i++;
  }
  if (str[i] == '+' || str[i] == '-') {
    if (str[i] == '-') {
      sign = -1;
    }
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10.0 + (str[i] - '0');
    i++;
  }
  if (str[i] == '.') {
    i++;
    while (str[i] >= '0' && str[i] <= '9') {
      fraction /= 10.0;
      result = result + (str[i] - '0') * fraction;
      i++;
      decimal = 1;
    }
  }
  if ((str[i] == 'e' || str[i] == 'E') && decimal) {
    int exponent = 0;
    int expSign = 1;
    i++;
    if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        expSign = -1;
      }
      i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
      exponent = exponent * 10 + (str[i] - '0');
      i++;
    }
    result *= pow(10, expSign * exponent);
  }
  *numLength = i;
  return sign * result;
}

int s21_atoi(char* str, int* numLength) {
  int res = 0;
  int sign = 1;
  int i = 0;
  while (str[i] == ' ') {
    i++;
  }
  if (str[i] == '-' || str[i] == '+') {
    sign = (str[i] == '-') ? -1 : 1;
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9') {
    res = res * 10 + (str[i] - '0');
    i++;
  }
  *numLength = i;
  return sign * res;
}
