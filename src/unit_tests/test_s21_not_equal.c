#include "unit_tests.h"

START_TEST(test_s21_is_not_equal) {
  s21_decimal dec = {0};
  s21_decimal dec2 = {0};
  int src = 2;
  int src2 = 4;
  s21_from_int_to_decimal(src, &dec);
  s21_from_int_to_decimal(src2, &dec2);
  ck_assert_int_eq(s21_is_not_equal(dec, dec2), 1);
}

END_TEST

Suite *make_is_not_equal_suite(void) {
  Suite *s = suite_create("is_not_equal");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_is_not_equal);
  return s;
}