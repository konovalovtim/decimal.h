#include "unit_tests.h"

START_TEST(test_s21_from_decimal_to_int) {
  s21_decimal dec = {0};
  int src = -2;
  s21_from_int_to_decimal(src, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &src), 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int2) {
  s21_decimal dec = {{4294967295u, 4294967295u, 4294967295u, 0}};
  int src = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &src), 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int3) {
  s21_decimal dec = {0};
  int src = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &src), 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int4) {
  s21_decimal dec = {0};
  int src = (int)2147483648;
  s21_from_int_to_decimal(src, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &src), 0);
}
END_TEST

Suite *make_from_decimal_to_int_suite(void) {
  Suite *s = suite_create("from_decimal_to_int");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_from_decimal_to_int);
  tcase_add_test(tc_decimal, test_s21_from_decimal_to_int2);
  tcase_add_test(tc_decimal, test_s21_from_decimal_to_int3);
  tcase_add_test(tc_decimal, test_s21_from_decimal_to_int4);
  return s;
}