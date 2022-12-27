#ifndef SRC_S21_DECIMAL_H
#define SRC_S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define S21_DECIMAL_MAX_INDEX pow(2, 95)
#define S21_DECIMAL_OVER_MAX pow(2, 96)

typedef struct {
  int bits[4];
} s21_decimal;

// Арифметические операторы //
// Сложение
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вычитание
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Деление
int s21_div(s21_decimal dasdsad, s21_decimal value_2, s21_decimal *result);
// Остаток от деления
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/*
Функции возвращают код ошибки:
- 0 - OK
- 1 - число слишком велико или равно бесконечности
- 2 - число слишком мало или равно отрицательной бесконечности
- 3 - деление на 0
*/

// Операторы сравнение //
//| Меньше  | < |
int s21_is_less(s21_decimal, s21_decimal);
// | Меньше или равно | <=
int s21_is_less_or_equal(s21_decimal, s21_decimal);
// | Больше | \> |
int s21_is_greater(s21_decimal, s21_decimal);
// | Больше или равно | \>= |
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
// | Равно | == |
int s21_is_equal(s21_decimal, s21_decimal);
// | Не равно | != |
int s21_is_not_equal(s21_decimal, s21_decimal);
/*
Возвращаемое значение:
- 0 - FALSE
- 1 - TRUE
*/

// Преобразователи //

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
/*
Возвращаемое значение - код ошибки:
 - 0 - OK
 - 1 - ошибка конвертации
*/

// Другие функции //

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности. |
int s21_floor(s21_decimal value, s21_decimal *result);
// Округляет Decimal до ближайшего целого числа.|
int s21_round(s21_decimal value, s21_decimal *result);
// Возвращает целые цифры указанного Decimal числа любые дробные цифры
// отбрасываются, включая конечные нули.|
int s21_truncate(s21_decimal value, s21_decimal *result);
// Возвращает результат умножения указанного Decimal на - 1. |
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  //  SRC_S21_DECIMAL_H
