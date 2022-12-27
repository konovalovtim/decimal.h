#include "../Auxiliary/s21_secondary_funcs.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OKAY;
  s21_decimal buff_res = {0};
  decimal_init(&buff_res);
  if (is_zero(value_2)) {
    res = DIVISION_BY_ZERO;
  } else if (normalization(value_1, value_2, &value_1, &value_2)) {
    if (!is_zero(value_2)) {
      div_without_dot(value_1, value_2, S21_NULL, &buff_res);
      if (is_zero(buff_res)) {
        decimal_init(&buff_res);
      } else {
        setScale(&buff_res, getScale(value_1));
        setSign(&buff_res, getSign(&value_1));
      }
    }
    if (result && !res) {
      decimal_cpy(buff_res, result);
    }
  }
  return res;
}