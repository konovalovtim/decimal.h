#include "unit_tests.h"

START_TEST(test_s21_mod) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -4;
  int src2 = 2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_mod(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_mod2) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = 4;
  int src2 = 0;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_mod(dec, dec2, &dec3), 3);
}

END_TEST

START_TEST(test_s21_mod3) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  float src = 123.5678;
  float src2 = 123.1234;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  s21_from_float_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_mod(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_mod4) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = 4;
  int src2 = -2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_mod(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_mod5) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -4;
  int src2 = -2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_mod(dec, dec2, &dec3), 0);
}

END_TEST

Suite *make_mod_suite(void) {
  Suite *s = suite_create("mod");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_mod);
  tcase_add_test(tc_decimal, test_s21_mod2);
  tcase_add_test(tc_decimal, test_s21_mod3);
  tcase_add_test(tc_decimal, test_s21_mod4);
  tcase_add_test(tc_decimal, test_s21_mod5);
  return s;
}