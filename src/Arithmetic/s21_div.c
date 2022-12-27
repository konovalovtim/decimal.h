#include "../Auxiliary/s21_secondary_funcs.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OKAY;
  s21_decimal buff_res = {0};
  decimal_init(&buff_res);
  if (is_zero(value_2)) {
    res = DIVISION_BY_ZERO;
  }
  int sign_1 = getSign(&value_1), sign_2 = getSign(&value_2);
  if (normalization(value_1, value_2, &value_1, &value_2) && !res) {
    if (!is_zero(value_2)) {
      decimal_init(&buff_res);
      s21_decimal buffer = {0}, ten = {{10, 0, 0, 0}};
      int error_mul = 0;
      while (!error_mul) {
        div_without_dot(value_1, value_2, &buffer, &value_1);
        add_without_check_scale(buff_res, buffer, &buff_res);
        if (!mul_without_check_scale(value_1, ten, &value_1)) {
          minusScale_bank_round_without_check(&value_2);
        }
        if (is_zero(value_1) || is_zero(value_2)) {
          break;
        } else {
          if (getScale(buff_res) == 28) {
            error_mul++;
          } else if (!mul_on_ten(buff_res, &buff_res)) {
            error_mul++;
          }
        }
      }
      if (error_mul) {
        int mod = buffer.bits[0] % 2;
        div_without_dot(value_1, value_2, &buffer, S21_NULL);
        if (((buffer.bits[0] == 5) && mod) || (buffer.bits[0] > 5)) {
          plusBit(&buff_res, 0);
        }
      }
      setSign(&buff_res, sign_1 ^ sign_2);
      if (result && !res) {
        decimal_cpy(buff_res, result);
      }
    } else {
      // это работает только в том случае если после нормализации съела
      // значение после точки
      if (getSign(&value_1) == sign_2) {
        res = INF;
      } else {
        res = NEGATIVE_INF;
      }
    }
  }
  return res;
}