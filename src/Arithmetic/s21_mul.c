#include "../Auxiliary/s21_secondary_funcs.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  decimal_init(result);
  int out = OKAY;
  int sign;
  if (getSign(&value_1) != getSign(&value_2)) {
    sign = 1;
  } else {
    sign = 0;
  }
  int scale = getScale(value_1) + getScale(value_2);
  setScale(&value_1, 0);
  setSign(&value_1, 0);
  setScale(&value_2, 0);
  setSign(&value_2, 0);
  if (s21_is_less(value_1, value_2)) {
    s21_decimal greater = value_2;
    value_2 = value_1;
    value_1 = greater;
  }
  int lastBit = getHighestBit(value_1);
  s21_decimal tmp = {{0, 0, 0, 0}};
  int addResult = OKAY;
  for (int i = 0; i <= lastBit; i++) {
    decimal_init(&tmp);
    int bitValue = get_bit(&value_1, i);
    if (bitValue) {
      tmp = value_2;
      shiftLeft(&tmp, i);
      addResult = s21_add(*result, tmp, result);
    }
  }
  if (addResult == INF) {
    if (sign)
      out = NEGATIVE_INF;
    else
      out = INF;
    decimal_init(result);
  } else {
    setScale(result, scale);
    setSign(result, sign);
  }
  return out;
}