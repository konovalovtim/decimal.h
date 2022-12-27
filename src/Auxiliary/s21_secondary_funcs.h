#ifndef SRC_AUXILIARY_SECONDARY_FUNCS_H
#define SRC_AUXILIARY_SECONDARY_FUNCS_H

#include "../s21_decimal.h"

#define S21_NULL (void *)0

typedef union {
  float floatValue;
  int intValue;
} value;

typedef enum { OK, ERROR } convertation;
typedef enum { FALSE, TRUE } comparison;
typedef enum { OKAY, INF, NEGATIVE_INF, DIVISION_BY_ZERO } returns;

// Нормализация и инициализация децималов

void decimal_init(s21_decimal *dst);

bool normalization(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result_1, s21_decimal *result_2);
bool equalScale(s21_decimal value_1, s21_decimal *result_1, s21_decimal value_2,
                s21_decimal *result_2);
bool mul_on_ten(s21_decimal value, s21_decimal *result);
bool mul_without_check_scale(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result);
bool minusScale_bank_round_without_check(s21_decimal *result);

// Работа с битами в децимале

int get_bit(s21_decimal *dst, int number_bit);
void set_bit(s21_decimal *dst, int index);
bool setBit(s21_decimal *dst, int index, int value);
int get_row(int bit);
int get_col(int bit);
int getHighestBit(s21_decimal dec);
int shiftLeft(s21_decimal *dst, int shift);
bool minusScale_truncate(s21_decimal *result);

int getScale(s21_decimal dst);
void setScale(s21_decimal *dst, int scale);
void setSign(s21_decimal *src, int sign);
int getSign(s21_decimal *src);

bool minusBit(s21_decimal *dst, int index);
bool plusBit(s21_decimal *dst, int index);
int find_not_equal_bit(s21_decimal value_1, s21_decimal value_2);
bool decimal_cpy(s21_decimal value, s21_decimal *dst);
bool switch_to_high_without_sign(s21_decimal *value_1, s21_decimal *value_2);
bool add_without_check_scale(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result);
bool sub_without_check_scale(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result);
bool minusScale_bank_round(s21_decimal *result);
bool div_without_dot(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result_div, s21_decimal *result_mod);
bool shift(s21_decimal *value, int index);
bool is_zero(s21_decimal value);
bool minusScale_round(s21_decimal *result);

// Работа с битами в интах

int get_binary_exp(float src);

// функции вывода для дебагинга //

// void print_float_in_binary(float src);
// void print_decimal(s21_decimal *dst);
// int get_bit_float_and_int(long int src, int number_bit);

#endif //  SRC_AUXILIARY_SECONDARY_FUNCS_H