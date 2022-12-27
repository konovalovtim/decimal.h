#include "../Auxiliary/s21_secondary_funcs.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int res = FALSE;
  normalization(value_1, value_2, &value_1, &value_2);
  res = find_not_equal_bit(value_1, value_2);
  int sign_1 = getSign(&value_1), sign_2 = getSign(&value_2);
  if (res > -1) {
    int bit_1 = get_bit(&value_1, res);
    if (bit_1) {
      res = FALSE;
    } else {
      res = TRUE;
    }
    if (sign_1 && sign_2) {
      res ^= 1;
    } else if (sign_1) {
      res = TRUE;
    } else if (sign_2) {
      res = FALSE;
    }
  } else {
    res = FALSE;
    if (sign_1 && !sign_2) {
      res = TRUE;
    }
  }
  return res;
}
