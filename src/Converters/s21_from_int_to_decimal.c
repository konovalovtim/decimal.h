#include "../Auxiliary/s21_secondary_funcs.h"
#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  convertation result;
  if (!dst) {
    result = ERROR;
  } else {
    decimal_init(dst);
    if (src < 0) {
      src *= -1;
      set_bit(dst, 127);
    }
    dst->bits[0] = src;
    result = OK;
  }
  return result;
}