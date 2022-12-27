#include "../Auxiliary/s21_secondary_funcs.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;
  s21_decimal buff_res = {0};
  decimal_init(&buff_res);
  if (normalization(value_1, value_2, &value_1, &value_2)) {
    // меняю местами если второй больше без знака, копирую больший в результат
    if (switch_to_high_without_sign(&value_1, &value_2)) {
      if (getSign(&value_1) == getSign(&value_2)) {
        while (!add_without_check_scale(value_1, value_2, &buff_res)) {
          if (getScale(value_1) > 0 && getScale(value_2) > 0) {
            minusScale_bank_round(&value_1);
            minusScale_bank_round(&value_2);
          } else {
            if (getSign(&value_1)) {
              res = NEGATIVE_INF;
            } else {
              res = INF;
            }
            break;
          }
        }
      } else {
        sub_without_check_scale(value_1, value_2, &buff_res);
      }
      setSign(&buff_res, getSign(&value_1));
      if (result && !res) {
        decimal_cpy(buff_res, result);
      }
    }
  }
  return res;
}
