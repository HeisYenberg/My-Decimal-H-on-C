#include "tests.h"

static int test_ints[] = {0, 1, -1, -21, 23132, 99999, 2147483647, -2147483647};

static s21_decimal test_int_dec[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}, 0},   // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}, 0},   // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}, 0},   // -1
    {{0x00000015, 0x00000000, 0x00000000, 0x80000000}, 0},   // -21
    {{0x00005A5C, 0x00000000, 0x00000000, 0x00000000}, 0},   // 23132
    {{0x0001869F, 0x00000000, 0x00000000, 0x00000000}, 0},   // 99999
    {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}, 0},   // 2147483647
    {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x80000000}, 0}};  //-2147483647

static float test_floats[] = {0.9,      0.21,     1.0,     -1.0,
                              0.123456, 123.4567, 21.2121, 9.999};

static s21_decimal test_float_dec[] = {
    {{0x00895440, 0x00000000, 0x00000000, 0x00070000}, 0},   // 0.9
    {{0x00200B20, 0x00000000, 0x00000000, 0x00070000}, 0},   // 0.21
    {{0x000F4240, 0x00000000, 0x00000000, 0x00060000}, 0},   // 1
    {{0x000F4240, 0x00000000, 0x00000000, 0x80060000}, 0},   // -1
    {{0x0012D680, 0x00000000, 0x00000000, 0x00070000}, 0},   // 0.123456
    {{0x0012D687, 0x00000000, 0x00000000, 0x00040000}, 0},   // 123.4567
    {{0x00205DFA, 0x00000000, 0x00000000, 0x00050000}, 0},   // 21.2121
    {{0x00989298, 0x00000000, 0x00000000, 0x00060000}, 0}};  // 9.999

START_TEST(test_int_to_decimal) {
  s21_decimal tmp = {0};
  int ret = s21_from_int_to_decimal(test_ints[_i], &tmp);
  ck_assert_int_eq(tmp.bits[0], test_int_dec[_i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], test_int_dec[_i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], test_int_dec[_i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], test_int_dec[_i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_decimal_to_int) {
  int tmp = 0;
  int ret = s21_from_decimal_to_int(test_int_dec[_i], &tmp);
  ck_assert_int_eq(tmp, test_ints[_i]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_float_to_decimal) {
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(test_floats[_i], &tmp);
  ck_assert_int_eq(tmp.bits[0], test_float_dec[_i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], test_float_dec[_i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], test_float_dec[_i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], test_float_dec[_i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(test_decimal_to_float) {
  float tmp = 0;
  int ret = s21_from_decimal_to_float(test_float_dec[_i], &tmp);
  ck_assert_float_eq(tmp, test_floats[_i]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

Suite *test_convertation() {
  int tests = sizeof(test_int_dec) / sizeof(s21_decimal);
  Suite *s = suite_create("\033[42m-=S21_DECIMAL_CONVERTATION=-\033[0m");
  TCase *tc = tcase_create("S21_DECIMAL_CONVERTATION");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, test_int_to_decimal, 0, tests);
  tcase_add_loop_test(tc, test_decimal_to_int, 0, tests);
  tcase_add_loop_test(tc, test_float_to_decimal, 0, tests);
  tcase_add_loop_test(tc, test_decimal_to_float, 0, tests);
  return s;
}