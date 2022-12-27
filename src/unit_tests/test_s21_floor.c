#include "unit_tests.h"

START_TEST(test_s21_floor) {
  s21_decimal dec = {{2, 0, 0, 0}};
  setScale(&dec, 2);
  s21_decimal result = {0};
  ck_assert_int_eq(s21_floor(dec, &result), 0);
}

END_TEST

START_TEST(test_s21_floor2) {
  s21_decimal dec = {{2, 0, 0, 0}};
  setSign(&dec, 1);
  setScale(&dec, 2);
  s21_decimal result = {0};
  ck_assert_int_eq(s21_floor(dec, &result), 0);
}

END_TEST

Suite *make_floor_suite(void) {
  Suite *s = suite_create("floor");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_floor);
  tcase_add_test(tc_decimal, test_s21_floor2);
  return s;
}