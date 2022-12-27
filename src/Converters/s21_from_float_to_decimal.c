#include "../Auxiliary/s21_secondary_funcs.h"
#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  convertation result = OK;
  if (!dst || isnan(src) || isinf(src)) {
    result = ERROR;
  } else {
    result = OK;
    int sign = (src < 0) ? 1 : 0;
    double tmp = (double)src;
    int scale = 0;
    while (scale < 28 && (int)tmp / (int)powl(2, 21) ==
                             0) {  // приводим до первой значящей цифры
      tmp *= 10;
      scale++;
    }
    tmp = round(tmp);
    while (fmod(tmp, 10) == 0 && scale > 0) {
      scale--;
      tmp /= 10;
    }
    float fl = tmp;
    int exp = get_binary_exp(fl);
    if (exp < 96) {
      dst->bits[exp / 32] = 1 << exp % 32;
      for (int i = exp - 1, j = 22; j >= 0; i--, j--)
        if ((*(int *)&fl & (0x1 << j)) != 0) dst->bits[i / 32] |= 0x1 << i % 32;
    } else {
      result = ERROR;
      dst->bits[2] = dst->bits[1] = dst->bits[0] = 0xFFFFFFFF;
    }
    if (sign) {
      dst->bits[3] |= 1 << 31;
    }
    dst->bits[3] += scale << 16;
  }
  return result;
}