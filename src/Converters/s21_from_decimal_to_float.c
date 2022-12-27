#include "../Auxiliary/s21_secondary_funcs.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  convertation result = ERROR;
  if (dst) {
    *dst = 0;
    double tmp = 0;
    for (int i = 0; i < 96; i++) {
      if (get_bit(&src, i)) {
        tmp += pow(2.0, i);
      }
    }
    int scale = getScale(src);
    while (scale != 0) {
      tmp /= 10;
      scale--;
    }
    if (getSign(&src)) {
      tmp = -tmp;
    }
    *dst = tmp;
    result = OK;
  }
  return result;
}
