#include "unit_tests.h"

START_TEST(test_s21_sub) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = 2;
  int src2 = 3;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_sub(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_sub2) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -3;
  int src2 = -2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, S21_NULL);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_sub(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_sub3) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -6;
  int src2 = -2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_sub(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_sub4) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  float src = -pow(2, 95);
  float src2 = pow(2.0, 95);
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_sub(dec, dec2, &dec3), 2);
}

END_TEST

START_TEST(test_s21_sub5) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  float src = pow(2.0, 95);
  float src2 = -pow(2.0, 95);
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_sub(dec, dec2, &dec3), 1);
}

END_TEST

Suite *make_sub_suite(void) {
  Suite *s = suite_create("sub");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_sub);
  tcase_add_test(tc_decimal, test_s21_sub2);
  tcase_add_test(tc_decimal, test_s21_sub3);
  tcase_add_test(tc_decimal, test_s21_sub4);
  tcase_add_test(tc_decimal, test_s21_sub5);
  return s;
}