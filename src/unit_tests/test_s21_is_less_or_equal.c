#include "unit_tests.h"

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  float src = -1.1;
  float src2 = 15.1;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_less(dec, dec2), 1);
}

END_TEST

START_TEST(test_s21_is_less_or_equal2) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  float src = -15.1;
  float src2 = 15.1;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_less(dec, dec2), 1);
}

END_TEST

START_TEST(test_s21_is_less_or_equal3) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  int src = 2;
  int src2 = 1;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_equal(dec, dec2), 0);
}

END_TEST

START_TEST(test_s21_is_less_or_equal4) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  int src = 1;
  int src2 = 1;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_equal(dec, dec2), 1);
}

END_TEST

START_TEST(test_s21_is_less_or_equal5) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  float src = -15.1;
  float src2 = 1.1;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_less(dec, dec2), 1);
}

END_TEST

START_TEST(test_s21_is_less_or_equal6) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  float src = -1.1;
  float src2 = 2.2;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_less(dec, dec2), 1);
}

END_TEST

START_TEST(test_s21_is_less_or_equal7) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  float src = 2.2;
  float src2 = -1.1;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_less(dec, dec2), 0);
}

END_TEST

Suite *make_is_less_or_equal_suite(void) {
  Suite *s = suite_create("is_less_or_equal");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_is_less_or_equal);
  tcase_add_test(tc_decimal, test_s21_is_less_or_equal2);
  tcase_add_test(tc_decimal, test_s21_is_less_or_equal3);
  tcase_add_test(tc_decimal, test_s21_is_less_or_equal4);
  tcase_add_test(tc_decimal, test_s21_is_less_or_equal5);
  tcase_add_test(tc_decimal, test_s21_is_less_or_equal6);
  tcase_add_test(tc_decimal, test_s21_is_less_or_equal7);
  return s;
}