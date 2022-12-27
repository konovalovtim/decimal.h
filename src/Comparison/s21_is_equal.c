#include "../Auxiliary/s21_secondary_funcs.h"
#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int out = TRUE;
  if ((value_1.bits[0] + value_1.bits[1] + value_1.bits[2]) == 0 &&
      (value_2.bits[0] + value_2.bits[1] + value_2.bits[2]) == 0) {
    out = TRUE;
  }
  for (int i = 0; i < 3; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      out = FALSE;
      break;
    }
  }
  return out;
}
