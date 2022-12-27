#include "unit_tests.h"

START_TEST(test_s21_round) {
  s21_decimal value_1 = {0};
  s21_decimal check1 = {0};
  s21_decimal result = {0};
  float src = -15.1;
  float check = -16;
  s21_from_float_to_decimal(src, &value_1);
  s21_from_float_to_decimal(check, &check1);
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check1), 0);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_s21_round2) {
  s21_decimal value_1 = {0};
  s21_decimal check1 = {0};
  s21_decimal result = {0};
  float src = 15.1;
  float check = 16;
  s21_from_float_to_decimal(src, &value_1);
  s21_from_float_to_decimal(check, &check1);
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check1), 0);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_s21_round3) {
  s21_decimal value_1 = {0};
  s21_decimal check1 = {0};
  s21_decimal result = {0};
  float src = 0.1;
  float check = 0;
  s21_from_float_to_decimal(src, &value_1);
  s21_from_float_to_decimal(check, &check1);
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check1), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *make_round_suite(void) {
  Suite *s = suite_create("round");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_round);
  tcase_add_test(tc_decimal, test_s21_round2);
  tcase_add_test(tc_decimal, test_s21_round3);
  return s;
}