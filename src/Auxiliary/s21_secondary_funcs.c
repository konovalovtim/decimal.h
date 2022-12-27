#include "s21_secondary_funcs.h"

bool normalization(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result_1, s21_decimal *result_2) {
  bool res = 0;
  if (result_1 && result_2) {
    res = 1;
    int scale_1 = getScale(value_1), scale_2 = getScale(value_2);
    while (scale_1 != scale_2) {
      if (scale_1 > scale_2) {
        res = equalScale(value_1, &value_1, value_2, &value_2);
      } else {
        res = equalScale(value_2, &value_2, value_1, &value_1);
      }
      scale_1 = getScale(value_1), scale_2 = getScale(value_2);
    }
    if (res) {
      decimal_cpy(value_1, result_1);
      decimal_cpy(value_2, result_2);
    }
  }
  return res;
}

bool equalScale(s21_decimal value_1, s21_decimal *result_1, s21_decimal value_2,
                s21_decimal *result_2) {
  bool res = 0;
  if (result_1 && result_2) {
    res = 1;
    if (!mul_on_ten(value_2, &value_2)) {
      res = minusScale_bank_round(&value_1);
    }
    if (res) {
      decimal_cpy(value_1, result_1);
      decimal_cpy(value_2, result_2);
    }
  }
  return res;
}

bool mul_on_ten(s21_decimal value, s21_decimal *result) {
  bool res = 0;
  if (result) {
    s21_decimal ten = {{10, 0, 0, 0}};
    int scale = getScale(value);
    if (scale < 28 && mul_without_check_scale(value, ten, &value)) {
      setScale(&value, scale + 1);
      res = 1;
      decimal_cpy(value, result);
    }
  }
  return res;
}

bool minusScale_bank_round(s21_decimal *result) {
  bool res = 0;
  if (result) {
    int scale = getScale(*result);
    int sign = getSign(result);
    if (scale > 0) {
      s21_decimal buffer = *result, ten = {{10, 0, 0, 0}};
      div_without_dot(buffer, ten, result, &buffer);
      int mod = buffer.bits[0];
      div_without_dot(*result, ten, S21_NULL, &buffer);
      if (buffer.bits[0] >= 5) {
        if (buffer.bits[0] == 5 && mod % 2) {
          plusBit(result, 0);
        } else if (buffer.bits[0] > 5) {
          plusBit(result, 0);
        }
      }
      setScale(result, scale - 1);
      setSign(result, sign);
      res = 1;
    }
  }
  return res;
}

bool minusScale_bank_round_without_check(s21_decimal *result) {
  bool res = 0;
  if (result) {
    s21_decimal buffer = *result, ten = {{10, 0, 0, 0}};
    div_without_dot(buffer, ten, result, &buffer);
    int mod = buffer.bits[0] % 2;
    div_without_dot(*result, ten, S21_NULL, &buffer);
    if ((buffer.bits[0] == 5 && mod) || buffer.bits[0] > 5) {
      plusBit(result, 0);
    }
    res = 1;
  }
  return res;
}

bool mul_without_check_scale(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result) {
  bool res = 0;
  s21_decimal buffer = {0};
  if (result) {
    int index = 0;
    res = 1;
    if (!(is_zero(value_1) || is_zero(value_2))) {
      for (int i = 0; i < 96; i++) {
        if (get_bit(&value_2, i)) {
          if (!shift(&value_1, i - index)) {
            res = 0;
          } else {
            index = i;
            if (!add_without_check_scale(buffer, value_1, &buffer)) {
              res = 0;
            }
          }
          if (!res) {
            break;
          }
        }
      }
      if (res && (getSign(&value_1) != getSign(&value_2))) {
        setSign(&buffer, 1);
        decimal_cpy(buffer, result);
      } else if (res) {
        setSign(&buffer, 0);
        decimal_cpy(buffer, result);
      }
    } else {
      decimal_init(result);
      res = 1;
    }
  }
  return res;
}

bool minusScale_truncate(s21_decimal *result) {
  bool res = 0;
  s21_decimal ten = {{10, 0, 0, 0}};
  int scale = getScale(*result);
  int sign = getSign(result);
  if (scale > 0) {
    if (div_without_dot(*result, ten, result, S21_NULL)) {
      setScale(result, scale - 1);
      setSign(result, sign);
      res = 1;
    }
  }
  return res;
}

// возвращает успех копирования структуры / 1 = ok, 0 != ok
bool decimal_cpy(s21_decimal value, s21_decimal *dst) {
  bool res = 0;
  if (dst) {
    dst->bits[0] = value.bits[0];
    dst->bits[1] = value.bits[1];
    dst->bits[2] = value.bits[2];
    dst->bits[3] = value.bits[3];
    res = 1;
  }
  return res;
}

// 0 = infinity, 1 = ok.
// result меняется только в случае успеха
bool add_without_check_scale(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result) {
  bool res = 0;
  if (result) {
    res = 1;
    for (int i = 0; i < 96; i++) {
      if (get_bit(&value_2, i)) {
        if (!plusBit(&value_1, i)) {
          res = 0;
          break;
        }
      }
    }
    if (res) {
      decimal_cpy(value_1, result);
    }
  }
  return res;
}

// 0 значит правое число больше левого, 1 = ok.
// result меняется только в случае успеха
bool sub_without_check_scale(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result) {
  bool res = 0;
  if (result) {
    res = 1;
    for (int i = 95; i > -1; i--) {
      if (get_bit(&value_2, i)) {
        if (!minusBit(&value_1, i)) {
          res = 0;
          break;
        }
      }
    }
    if (res) {
      decimal_cpy(value_1, result);
    }
  }
  return res;
}

bool div_without_dot(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result_div, s21_decimal *result_mod) {
  bool res = 0;
  int index = 0;
  if (result_div || result_mod) {
    if (!is_zero(value_2)) {
      res = 1;
      while (shift(&value_2, 1)) {
        index++;
      }
      s21_decimal mod = {0}, buff_res = {0};
      while (index > -1 && res) {
        if (!sub_without_check_scale(value_1, value_2, &mod)) {
        } else {
          decimal_cpy(mod, &value_1);
          plusBit(&buff_res, index);
        }
        if (index-- > 0) {
          res = shift(&value_2, -1);
        } else {
          shift(&value_2, -1);
        }
      }
      if (res) {
        if (result_div) {
          decimal_cpy(buff_res, result_div);
        }
        if (result_mod) {
          decimal_cpy(value_1, result_mod);
        }
      }
    }
  }
  return res;
}

// возвращает истину / 1 = is zero, 0 = have value
bool is_zero(s21_decimal value) {
  bool res = 0;
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) {
    res = 1;
  }
  return res;
}

// возвращает успех сдвига числа s21_decimal на индекс / 1 = ok, 0 =
// переполнение любую из сторон. index раз число умножится на 2, если index
// положителен. либо index раз число поделится на 2, если index отрицателен
bool shift(s21_decimal *value, int index) {
  bool res = 0;
  if (value && index != 0) {
    int bit_num;
    int index_curr;
    if (index > 0) {
      index_curr = 95;
      bit_num = index_curr - index;
      while (index_curr != bit_num) {
        if (get_bit(value, index_curr)) {
          return 0;
        }
        index_curr--;
      }
      index_curr = 95;
      while (bit_num != -1) {
        setBit(value, index_curr, get_bit(value, bit_num));
        index_curr--;
        bit_num--;
      }
      while (index_curr != -1) {
        setBit(value, index_curr, 0);
        index_curr--;
      }
      res = 1;
    } else {
      index_curr = 0;
      bit_num = index_curr - index;
      while (index_curr != bit_num) {
        if (get_bit(value, index_curr)) {
          return 0;
        }
        index_curr++;
      }
      index_curr = 0;
      while (bit_num != 96) {
        setBit(value, index_curr, get_bit(value, bit_num));
        index_curr++;
        bit_num++;
      }
      while (index_curr != 96) {
        setBit(value, index_curr, 0);
        index_curr++;
      }
      res = 1;
    }
  } else if (index == 0) {
    res = 1;
  }
  return res;
}

// возвращает успех и ставит большее число в value_1 игнорируя знак.
// 1 = ok, 0 != ok
bool switch_to_high_without_sign(s21_decimal *value_1, s21_decimal *value_2) {
  bool res = 0;
  if (value_1 && value_2) {
    int index = 0;
    if ((index = find_not_equal_bit(*value_1, *value_2)) != -1) {
      if (get_bit(value_2, index) & 1) {
        s21_decimal buff = {0};
        decimal_cpy(*value_1, &buff);
        decimal_cpy(*value_2, value_1);
        decimal_cpy(buff, value_2);
      }
    }
    res = 1;
  }
  return res;
}

// возвращает index несовпадающего бита / -1 если нет такого
int find_not_equal_bit(s21_decimal value_1, s21_decimal value_2) {
  int index = 95;
  if (getScale(value_1) == getScale(value_2)) {
    while (get_bit(&value_1, index) == get_bit(&value_2, index) &&
           index != -1) {
      index--;
    }
  }
  return index;
}

void setSign(s21_decimal *src, int sign) {
  if (sign == 1) {
    src->bits[3] |= (1 << 31);
  } else
    src->bits[3] &= ~(1 << 31);
}

bool minusBit(s21_decimal *dst, int index) {
  bool res = 0;
  if (dst && index > -1 && index < 96) {
    res = 1;
    unsigned char index_curr = index % 32;
    unsigned char bit_curr = index / 32;
    if (!((dst->bits[bit_curr] >> index_curr) & 1)) {
      if (!minusBit(dst, index + 1)) {
        res = 0;
      }
    }
    if (res) {
      dst->bits[bit_curr] ^= (1 << index_curr);
    }
  }
  return res;
}

bool plusBit(s21_decimal *dst, int index) {
  bool res = 0;
  if (index > -1 && index < 96) {
    res = 1;
    unsigned char index_curr = index % 32;
    unsigned char bit_curr = index / 32;
    if ((dst->bits[bit_curr] >> index_curr) & 1) {
      if (!plusBit(dst, index + 1)) {
        res = 0;
      }
    }
    if (res) {
      dst->bits[bit_curr] ^= (1 << index_curr);
    }
  }
  return res;
}

int getSign(s21_decimal *src) {
  int sign = 0;
  if ((src->bits[3] >> 31)) {
    sign = 1;
  }
  return sign;
}

int get_bit(s21_decimal *dst, int number_bit) {
  int index_int_in_decimal = get_row(number_bit);
  int index_bit_in_int_decimal = get_col(number_bit);
  return ((dst->bits[index_int_in_decimal]) & (1 << index_bit_in_int_decimal))
             ? 1
             : 0;
}

// int get_bit_float_and_int(long int src, int number_bit) {
//   return (src & (1 << number_bit)) ? 1 : 0;
// }

bool setBit(s21_decimal *dst, int index, int value) {
  bool res = 0;
  if (dst && index > -1 && index < 128) {
    int bit = get_bit(dst, index);
    unsigned char index_curr = index % 32;
    unsigned char bit_curr = index / 32;
    if (bit ^ value) {
      dst->bits[bit_curr] ^= (1 << index_curr);
    }
    res = 1;
  }
  return res;
}

void set_bit(s21_decimal *dst, int number_bit) {
  int index_int_in_decimal = get_row(number_bit);
  int index_bit_in_int_decimal = get_col(number_bit);
  dst->bits[index_int_in_decimal] |= (1 << index_bit_in_int_decimal);
}

// возвращает индекс в колонке, то индекс инта в нашем децимале.
int get_row(int bit) { return (int)bit >> 5; }

// возвращает индекс в строке
int get_col(int bit) { return bit % 32; }

// void print_decimal(s21_decimal *dst) {
//   int n = 127;
//   while (n >= 0) {
//     printf("%d", get_bit(dst, n));
//     if (n % 32 == 0 || n == 127 || n == 120 || n == 112) {
//       printf(" | ");
//     }
//     n--;
//   }
//   printf("\n");
// }
//
// void print_float_in_binary(float src) {
//   value val;
//   val.floatValue = src;
//   for (int n = 31; n >= 0; n--) {
//     printf("%d", get_bit_float_and_int(val.intValue, n));
//   }
//   printf("\n");
// }

void decimal_init(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

// возвращает успех / 0 != ok | 1 = ok
bool minusScale_round(s21_decimal *result) {
  bool res = 0;
  s21_decimal mod = {0}, ten = {{10, 0, 0, 0}};
  int scale = getScale(*result);
  if (getScale(*result) > 0 && div_without_dot(*result, ten, S21_NULL, &mod)) {
    if (div_without_dot(*result, ten, result, S21_NULL)) {
      if (mod.bits[0] > 4) {
        plusBit(result, 0);
      }
      setScale(result, scale - 1);
      res = 1;
    }
  }
  return res;
}

int getScale(s21_decimal dst) {
  int shift = 16;
  int scale = 0, i = 0;
  while (shift <= 23) {
    int bit = ((dst.bits[3] & (1 << shift)) != 0);
    scale += bit * pow(2, i);
    shift++;
    i++;
  }
  return scale;
}

void setScale(s21_decimal *dst, int scale) {
  int shift = 16;
  while (shift <= 23) {
    if (scale > 0 && scale % 2 == 1) {
      dst->bits[3] |= (1 << shift);
    } else {
      dst->bits[3] &= ~(1 << shift);
    }
    scale /= 2;
    shift++;
  }
}

int get_binary_exp(float src) {
  value val;
  val.floatValue = fabsf(src);
  int new = (val.intValue >> 23) - 127;
  return new;
}

int getHighestBit(s21_decimal dec) {
  int i = 95;
  while (i) {
    if (get_bit(&dec, i)) break;
    i--;
  }
  return i;
}

int shiftLeft(s21_decimal *dst, int shift) {
  int out = OKAY;
  int lastbit = getHighestBit(*dst);
  if (lastbit + shift > 95) {
    out = INF;
  } else {
    for (int i = 0; i < shift; i++) {
      int value31bit = get_bit(dst, 31);
      int value63bit = get_bit(dst, 63);
      dst->bits[0] <<= 1;
      dst->bits[1] <<= 1;
      dst->bits[2] <<= 1;
      if (value31bit) setBit(dst, 32, 1);
      if (value63bit) setBit(dst, 64, 1);
    }
  }
  return out;
}
