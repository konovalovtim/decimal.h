#include "../Auxiliary/s21_secondary_funcs.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  convertation result = ERROR;
  if (dst) {
    while (minusScale_truncate(&src)) {
    }
    int index = getHighestBit(src);
    if (index < 31) {
      *dst = src.bits[0];
      if (getSign(&src)) {
        *dst *= -1;
      }
      result = OK;
    }
    if (getSign(&src) && src.bits[0] == (int)2147483648 && index < 32) {
      *dst = 0b10000000000000000000000000000000;
      result = OK;
    }
  }
  return result;
}
