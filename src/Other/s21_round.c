#include "../Auxiliary/s21_secondary_funcs.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  decimal_init(result);
  int return_value = OK;
  int sign = getSign(&value);
  setSign(&value, 0);
  s21_decimal tmp = {{0}};
  s21_truncate(value, &tmp);
  s21_decimal tmp_copy = tmp;
  s21_sub(value, tmp, &tmp);
  s21_decimal zero_five = {{5, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  setScale(&zero_five, 1);
  if (s21_is_greater_or_equal(tmp, zero_five))
    return_value = s21_add(tmp_copy, one, result);
  else
    *result = tmp_copy;
  if (sign) setSign(result, 1);
  return return_value;
}
