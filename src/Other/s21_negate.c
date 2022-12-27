#include "../Auxiliary/s21_secondary_funcs.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  int sign = getSign(result);
  if (sign)
    setSign(result, 0);
  else
    setSign(result, 1);
  return OK;
}