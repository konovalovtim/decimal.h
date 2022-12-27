#include "unit_tests.h"

void runtest(Suite *make_suite, int *result);

int main(void) {
  int result = 0;
  runtest(make_add_suite(), &result);
  runtest(make_sub_suite(), &result);
  runtest(make_div_suite(), &result);
  runtest(make_mul_suite(), &result);
  runtest(make_mod_suite(), &result);
  runtest(make_is_less_or_equal_suite(), &result);
  runtest(make_is_not_equal_suite(), &result);
  runtest(make_from_decimal_to_int_suite(), &result);
  runtest(make_from_decimal_to_float_suite(), &result);
  runtest(make_floor_suite(), &result);
  runtest(make_negate_suite(), &result);
  runtest(make_round_suite(), &result);
  return 0;
}

void runtest(Suite *make_suite, int *result) {
  SRunner *sr = srunner_create(make_suite);
  srunner_run_all(sr, CK_NORMAL);
  int n = srunner_ntests_failed(sr);
  *result += n;
  srunner_free(sr);
}
