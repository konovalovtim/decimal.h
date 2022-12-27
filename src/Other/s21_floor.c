#include "../Auxiliary/s21_secondary_funcs.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 1;
  if (result) {
    if (getScale(value) > 0) {
      int mod_f = 0, sign = getSign(&value);
      s21_decimal mod = {0}, ten = {{10, 0, 0, 0}};
      div_without_dot(value, ten, S21_NULL, &mod);
      while (minusScale_truncate(&value)) {
        if (!mod_f && !is_zero(mod)) {
          mod_f = 1;
          div_without_dot(value, ten, S21_NULL, &mod);
        }
      }
      if (sign && mod_f) {
        setSign(&value, sign);
        plusBit(&value, 0);
      }
    }
    decimal_cpy(value, result);
    res = 0;
  }
  return res;
}
