#include "unit_tests.h"

START_TEST(test_s21_mul) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -4;
  int src2 = 2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_mul2) {
  s21_decimal dec = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = 2;
  s21_from_int_to_decimal(src, &dec2);
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 1);
}

END_TEST

START_TEST(test_s21_mul3) {
  s21_decimal dec = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -2;
  s21_from_int_to_decimal(src, &dec2);
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 2);
}

START_TEST(test_s21_mul4) {
  s21_decimal dec = {{2, 0, 0, 0}};
  s21_decimal dec2 = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal dec3 = {0};
  ck_assert_int_eq(s21_mul(dec, dec2, &dec3), 1);
}

END_TEST

Suite *make_mul_suite(void) {
  Suite *s = suite_create("mul");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_mul);
  tcase_add_test(tc_decimal, test_s21_mul2);
  tcase_add_test(tc_decimal, test_s21_mul3);
  tcase_add_test(tc_decimal, test_s21_mul4);
  return s;
}