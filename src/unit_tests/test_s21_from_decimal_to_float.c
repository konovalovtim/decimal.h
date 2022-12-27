#include "unit_tests.h"

START_TEST(test_s21_from_decimal_to_float) {
  s21_decimal dec = {0};
  float src = 2.0;
  s21_from_int_to_decimal(src, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &src), 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float2) {
  s21_decimal dec = {{4294967295u, 4294967295u, 4294967295u, 0}};
  setScale(&dec, 2);
  setSign(&dec, 1);
  float src = 0;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &src), 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float3) {
  s21_decimal dec = {0};
  float src = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &src), 0);
}
END_TEST

Suite *make_from_decimal_to_float_suite(void) {
  Suite *s = suite_create("from_decimal_to_float");
  TCase *tc_decimal = tcase_create("decimal");
  suite_add_tcase(s, tc_decimal);
  tcase_add_test(tc_decimal, test_s21_from_decimal_to_float);
  tcase_add_test(tc_decimal, test_s21_from_decimal_to_float2);
  tcase_add_test(tc_decimal, test_s21_from_decimal_to_float3);
  return s;
}