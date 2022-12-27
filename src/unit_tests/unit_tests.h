#ifndef SRC_UNIT_TESTS_UNIT_TESTS_H
#define SRC_UNIT_TESTS_UNIT_TESTS_H

#include <check.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Auxiliary/s21_secondary_funcs.h"
#include "../s21_decimal.h"

Suite *make_add_suite(void);
Suite *make_sub_suite(void);
Suite *make_div_suite(void);
Suite *make_mul_suite(void);
Suite *make_mod_suite(void);
Suite *make_is_less_or_equal_suite(void);
Suite *make_is_not_equal_suite(void);
Suite *make_from_decimal_to_int_suite(void);
Suite *make_from_decimal_to_float_suite(void);
Suite *make_floor_suite(void);
Suite *make_negate_suite(void);
Suite *make_round_suite(void);

#endif // SRC_UNIT_TESTS_UNIT_TESTS_H
