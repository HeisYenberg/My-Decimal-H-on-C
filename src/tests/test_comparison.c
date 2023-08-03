#include "tests.h"

static my_decimal value_x[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}, 0},  // 0
    {{0x00000000, 0x00000000, 0x00000001, 0x00000000},
     0},  // 18446744073709551616
    {{0x00000001, 0x00000000, 0x00000000, 0x00020000}, 0},  // 0.01
    {{0b00000001, 0x00000000, 0x00000000, 0x00000000}, 0},  // 1
    {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000}, 0},  // 4294967295
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0},  // 79228162514264337593543950335
    {{0x00000000, 0x00000003, 0x00000007, 0x00020000},
     0},  // 1291272085288517632
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0},  // 79228162514264337593543950335
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0}};  // 79228162514264337593543950334

static my_decimal value_y[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}, 0},  // 0
    {{0x00000000, 0x00000001, 0x00000000, 0x00000000}, 0},  // 4294967296
    {{0x00000001, 0x00000000, 0x00000000, 0x00020000}, 0},  // 0.01
    {{0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000},
     0},  // 18446744069414584320
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0},  // 79228162514264337593543950335
    {{0x000000F4, 0x00000000, 0x00000000, 0x00030000}, 0},  // 0.244
    {{0x00000000, 0x00000003, 0x00000007, 0x00020000},
     0},  // 1291272085288517632
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0},  // 79228162514264337593543950334
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000},
     0}};  // 79228162514264337593543950335

static int result1[] = {1, 1, 1, 0, 0, 1, 1, 1, 1};
static int result2[] = {0, 1, 0, 0, 0, 1, 0, 1, 1};
static int result3[] = {1, 0, 1, 1, 1, 0, 1, 0, 0};
static int result4[] = {0, 0, 0, 1, 1, 0, 0, 0, 0};
static int result5[] = {1, 0, 1, 0, 0, 0, 1, 0, 0};
static int result6[] = {0, 1, 0, 1, 1, 1, 0, 1, 1};

START_TEST(test1) {
  int ret = my_is_greater_or_equal(value_x[_i], value_y[_i]);
  ck_assert_int_eq(ret, result1[_i]);
}
END_TEST

START_TEST(test2) {
  int ret = my_is_greater(value_x[_i], value_y[_i]);
  ck_assert_int_eq(ret, result2[_i]);
}
END_TEST

START_TEST(test3) {
  int ret = my_is_less_or_equal(value_x[_i], value_y[_i]);
  ck_assert_int_eq(ret, result3[_i]);
}
END_TEST

START_TEST(test4) {
  int ret = my_is_less(value_x[_i], value_y[_i]);
  ck_assert_int_eq(ret, result4[_i]);
}
END_TEST

START_TEST(test5) {
  int ret = my_is_equal(value_x[_i], value_y[_i]);
  ck_assert_int_eq(ret, result5[_i]);
}
END_TEST

START_TEST(test6) {
  int ret = my_is_not_equal(value_x[_i], value_y[_i]);
  ck_assert_int_eq(ret, result6[_i]);
}
END_TEST

Suite *test_comparison() {
  int tests = sizeof(value_x) / sizeof(my_decimal);
  Suite *s = suite_create("\033[42m-=S21_DECIMAL_COMPARISON=-\033[0m");
  TCase *tc = tcase_create("S21_DECIMAL_COMPARISON");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, test1, 0, tests);
  tcase_add_loop_test(tc, test2, 0, tests);
  tcase_add_loop_test(tc, test3, 0, tests);
  tcase_add_loop_test(tc, test4, 0, tests);
  tcase_add_loop_test(tc, test5, 0, tests);
  tcase_add_loop_test(tc, test6, 0, tests);
  return s;
}