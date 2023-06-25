#include "tests.h"

static s21_decimal arr[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0X00000001, 0X00000000, 0X00000000, 0X80000000}, 0},  // -1
    {{0X7FFFFFFF, 0X00000000, 0X00000000, 0X80030000}, 0},  // -2147483.647
    {{0X7FFFFFFF, 0X7FFFFFFF, 0X7FFFFFFF, 0X80060000},
     0},  // -39614081247908796757769.715711
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000},
     0},  // 79228162514264337593543950335
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000},
     0},  // -79228162514264337593543950335
    {{0X075BCD15, 0X00000000, 0X00000000, 0X001B0000},
     0}};  // 0,000000000000000000123456789

static s21_decimal result_round[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0X00000001, 0X00000000, 0X00000000, 0X80000000}, 0},  // -1
    {{0X0020C49C, 0X00000000, 0X00000000, 0X00000000}, 0},  // 2147484
    {{0X4ACAF70A, 0X7BD05293, 0X00000863, 0X00000000},
     0},  // 39614081247908796757770
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000},
     0},  // 79228162514264337593543950335
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000},
     0},  // -79228162514264337593543950335
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
};

static int return_round[] = {0, 0, 0, 0, 0, 0, 0, 0};

static s21_decimal result_truncate[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0X00000001, 0X00000000, 0X00000000, 0X80000000}, 0},  // -1
    {{0X0020C49B, 0X00000000, 0X00000000, 0X80000000}, 0},  // 2147483
    {{0X4ACAF709, 0X7BD05293, 0X00000863, 0X80000000},
     0},  // 39614081247908796757769
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000},
     0},  // 79228162514264337593543950335
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000},
     0},  // -79228162514264337593543950335
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
};

static int return_truncate[] = {0, 0, 0, 0, 0, 0, 0, 0};

static s21_decimal result_floor[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0X00000001, 0X00000000, 0X00000000, 0X80000000}, 0},  // -1
    {{0X0020C49C, 0X00000000, 0X00000000, 0X80000000}, 0},  // 2147484
    {{0X4ACAF70A, 0X7BD05293, 0X00000863, 0X80000000},
     0},  // 39614081247908796757770
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000},
     0},  // 79228162514264337593543950335
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000},
     0},  // -79228162514264337593543950335
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
};

static int return_floor[] = {0, 0, 0, 0, 0, 0, 0, 0};

static s21_decimal result_negate[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X80000000}, 0},  // -0
    {{0X00000001, 0X00000000, 0X00000000, 0X80000000}, 0},  // -1
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0X7FFFFFFF, 0X00000000, 0X00000000, 0X00030000}, 0},  // 2147483.647
    {{0X7FFFFFFF, 0X7FFFFFFF, 0X7FFFFFFF, 0X00060000},
     0},  // 39614081247908796757769.715711
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000},
     0},  // -79228162514264337593543950335
    {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000},
     0},  // 79228162514264337593543950335
    {{0X075BCD15, 0X00000000, 0X00000000, 0X801B0000},
     0}};  // -0,000000000000000000123456789

static int return_negate[] = {0, 0, 0, 0, 0, 0, 0, 0};

START_TEST(test_round) {
  s21_decimal tmp;
  int ret = s21_round(arr[_i], &tmp);
  ck_assert_int_eq(tmp.bits[0], result_round[_i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_round[_i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_round[_i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_round[_i].bits[3]);
  ck_assert_int_eq(ret, return_round[_i]);
}
END_TEST

START_TEST(test_truncate) {
  s21_decimal tmp;
  int ret = s21_truncate(arr[_i], &tmp);
  ck_assert_int_eq(tmp.bits[0], result_truncate[_i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_truncate[_i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_truncate[_i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_truncate[_i].bits[3]);
  ck_assert_int_eq(ret, return_truncate[_i]);
}
END_TEST

START_TEST(test_floor) {
  s21_decimal tmp;
  int ret = s21_floor(arr[_i], &tmp);
  ck_assert_int_eq(tmp.bits[0], result_floor[_i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_floor[_i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_floor[_i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_floor[_i].bits[3]);
  ck_assert_int_eq(ret, return_floor[_i]);
}
END_TEST

START_TEST(test_negate) {
  s21_decimal tmp;
  int ret = s21_negate(arr[_i], &tmp);
  ck_assert_int_eq(tmp.bits[0], result_negate[_i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_negate[_i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_negate[_i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_negate[_i].bits[3]);
  ck_assert_int_eq(ret, return_negate[_i]);
}
END_TEST

Suite *test_rounding() {
  int tests = sizeof(arr) / sizeof(s21_decimal);
  Suite *s = suite_create("\033[42m-=S21_DECIMAL_ROUNDING=-\033[0m");
  TCase *tc = tcase_create("S21_DECIMAL_ROUNDING");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, test_round, 0, tests);
  tcase_add_loop_test(tc, test_truncate, 0, tests);
  tcase_add_loop_test(tc, test_floor, 0, tests);
  tcase_add_loop_test(tc, test_negate, 0, tests);
  return s;
}