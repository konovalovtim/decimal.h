#include "../Auxiliary/s21_secondary_funcs.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 1;
  if (result) {
    int sign = getSign(&value);
    while (minusScale_truncate(&value)) {
    }
    decimal_cpy(value, result);
    setSign(result, sign);
    res = 0;
  }
  return res;
}