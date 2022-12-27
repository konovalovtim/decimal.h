#include "unit_tests.h"

START_TEST(test_s21_negate) {
  s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
  setSign(&value_1, 1);
  s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_s21_negate2) {
  s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
  setSign(&value_1, 0);
  s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

Suite *make_negate_suite(void) {
  Suite *s = suite_create("negate");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_negate);
  tcase_add_test(tc_decimal, test_s21_negate2);
  return s;
}