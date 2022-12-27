#include "unit_tests.h"

START_TEST(test_s21_div) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = 4;
  int src2 = 2;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_div2) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = 4;
  int src2 = 0;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  s21_from_int_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 3);
}

END_TEST

START_TEST(test_s21_div3) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  float src = 123.5678;
  float src2 = 123.1234;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  s21_from_float_to_decimal(src2, &dec3);
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_div4) {
  s21_decimal dec = {{1, 0, 0, 0}};
  setScale(&dec, 28);
  s21_decimal dec2 = {{1324, 0, 0, 0}};
  s21_decimal dec3 = {0};
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_div5) {
  s21_decimal dec = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  setScale(&dec2, 28);
  s21_decimal dec3 = {0};
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_div6) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  int src = -89124724;
  float src2 = 15.75;
  s21_from_int_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 0);
}

END_TEST

START_TEST(test_s21_div7) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  float src = pow(2, 95);
  float src2 = 0.0001;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 1);
}

END_TEST

START_TEST(test_s21_div8) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  s21_decimal dec3 = {0};
  float src = pow(2, 95);
  float src2 = -0.0001;
  s21_from_float_to_decimal(src, &dec);
  s21_from_float_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_div(dec, dec2, &dec3), 2);
}

END_TEST


Suite *make_div_suite(void) {
  Suite *s = suite_create("div");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_div);
  tcase_add_test(tc_decimal, test_s21_div2);
  tcase_add_test(tc_decimal, test_s21_div3);
  tcase_add_test(tc_decimal, test_s21_div4);
  tcase_add_test(tc_decimal, test_s21_div5);
  tcase_add_test(tc_decimal, test_s21_div6);
  tcase_add_test(tc_decimal, test_s21_div7);
  tcase_add_test(tc_decimal, test_s21_div8);
  return s;
}