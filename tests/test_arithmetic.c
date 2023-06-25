#include "tests.h"

static s21_decimal value_1[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}, 0},  // 0
    {{0X00003038, 0X00000000, 0X00000000, 0X80000000},
     0},  // -18446744073709551616
    {{0X00003038, 0X00000000, 0X00000000, 0X80000000}, 0},  // 0.01
    {{0X00003038, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0X0000303D, 0X00000000, 0X00000000, 0X00000000}, 0},  // 4294967295
    {{0X0000303D, 0X00000000, 0X00000000, 0X80000000},
     0},  // 79228162514264337593543950335
    {{0x00000000, 0x00000003, 0x00000007, 0x00020000},
     0},  // 1291272085288517632
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0},  // 79228162514264337593543950335
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0}};  // 79228162514264337593543950334

static s21_decimal value_2[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}, 0},  // 0
    {{0X00003038, 0X00000000, 0X00000000, 0X80000000}, 0},  // 4294967296
    {{0X0000303A, 0X00000000, 0X00000000, 0X80000000}, 0},  // 0.01
    {{0X0000303A, 0X00000000, 0X00000000, 0X00000000},
     0},  // 18446744069414584320
    {{0X00000003, 0X00000000, 0X00000000, 0X00000000},
     0},  // 79228162514264337593543950335
    {{0X0000303A, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0.244
    {{0x00000000, 0x00000003, 0x00000007, 0x00020000},
     0},  // 1291272085288517632
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000},
     0},  // 79228162514264337593543950334
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000},
     0},  // 79228162514264337593543950335
    {{0X00003038, 0X00000000, 0X00000000, 0X80000000}, 0}};  // -12344

static s21_decimal result_add[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00006070, 0X00000000, 0X00000000, 0X80000000},
     0},  // 18446744078004518912
    {{0X00006072, 0X00000000, 0X00000000, 0X80000000}, 0},  // 0.02
    {{0X00006072, 0X00000000, 0X00000000, 0X00000000},
     0},  // 18446744069414584321
    {{0X00003040, 0X00000000, 0X00000000, 0X00000000}, 0},  // 4294967294
    {{0X00000003, 0X00000000, 0X00000000, 0X80000000},
     0},  // 79228162514264337593543950335
    {{0X00000000, 0X00000006, 0X0000000E, 0X00020000},
     0},  // 258254417057703526400
    {{0XFFFFFFFD, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000},
     0},  // 79228162514264337593543950333
    {{0X00000001, 0X00000000, 0X00000000, 0X80000000}, 0}};  // -1

static int return_add[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

static s21_decimal result_sub[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00000000, 0X00000000, 0X00000000, 0X80000000},
     0},  // -79228162495817593524129366016
    {{0X00000002, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00000002, 0X00000000, 0X00000000, 0X80000000},
     0},  // -18446744069414584319
    {{0X0000303A, 0X00000000, 0X00000000, 0X00000000},
     0},  // -79228162514264337589248983040
    {{0X00006077, 0X00000000, 0X00000000, 0X80000000},
     0},  // 79228162514264337593543950335
    {{0X00000000, 0X00000000, 0X00000000, 0X00020000}, 0},  // 0
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0XFFFFFFFD, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000},
     0}};  // 79228162514264337593543950333

static int return_sub[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

static s21_decimal result_mul[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X09150C40, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X09156CB0, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0.0001
    {{0X09156CB0, 0X00000000, 0X00000000, 0X00000000},
     0},  // 18446744069414584320
    {{0X000090B7, 0X00000000, 0X00000000, 0X00000000},
     0},  // 79228162514264337589248983041
    {{0X09165DD2, 0X00000000, 0X00000000, 0X80000000},
     0},  // 79228162514264337593543950092
    {{0X00000000, 0X00000000, 0X00000009, 0X00040000},
     0},  // 16602069666338596,4544
    {{0X00000002, 0X00000000, 0X00000000, 0X00000000}, 0},   // 2
    {{0X00000002, 0X00000000, 0X00000000, 0X80000000}, 0}};  // -2

static int return_mul[] = {0, 0, 0, 0, 0, 0, 1, 1, 1};

static s21_decimal result_div[] = {
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},  // 4294967296
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 1
    {{0X00000000, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0
    {{0X00001014, 0X00000000, 0X00000000, 0X00000000}, 0},  // 0,
    {{0X00000001, 0X00000000, 0X00000000, 0X80000000},
     0},  // 79228162514264337593543950335
    {{0X00000040, 0X00000000, 0X00000000, 0X00000000}, 0},   // 64
    {{0X00000001, 0X00000000, 0X00000000, 0X00000000}, 0},   // 1
    {{0X00000000, 0X00000000, 0X00000000, 0X80000000}, 0}};  // 0

static int return_div[] = {3, 0, 0, 0, 0, 0, 0, 0, 0};

START_TEST(test_add) {
  s21_decimal dec_recult = {0};
  int result = s21_add(value_1[_i], value_2[_i], &dec_recult);
  ck_assert_int_eq(dec_recult.bits[0], result_add[_i].bits[0]);
  ck_assert_int_eq(dec_recult.bits[1], result_add[_i].bits[1]);
  ck_assert_int_eq(dec_recult.bits[2], result_add[_i].bits[2]);
  ck_assert_int_eq(dec_recult.bits[3], result_add[_i].bits[3]);
  ck_assert_int_eq(result, return_add[_i]);
}
END_TEST

START_TEST(test_sub) {
  s21_decimal dec_recult = {0};
  int result = s21_sub(value_1[_i], value_2[_i], &dec_recult);
  ck_assert_int_eq(dec_recult.bits[0], result_sub[_i].bits[0]);
  ck_assert_int_eq(dec_recult.bits[1], result_sub[_i].bits[1]);
  ck_assert_int_eq(dec_recult.bits[2], result_sub[_i].bits[2]);
  ck_assert_int_eq(dec_recult.bits[3], result_sub[_i].bits[3]);
  ck_assert_int_eq(result, return_sub[_i]);
}
END_TEST

START_TEST(test_mul) {
  s21_decimal dec_recult = {0};
  int result = s21_mul(value_1[_i], value_2[_i], &dec_recult);
  ck_assert_int_eq(dec_recult.bits[0], result_mul[_i].bits[0]);
  ck_assert_int_eq(dec_recult.bits[1], result_mul[_i].bits[1]);
  ck_assert_int_eq(dec_recult.bits[2], result_mul[_i].bits[2]);
  ck_assert_int_eq(dec_recult.bits[3], result_mul[_i].bits[3]);
  ck_assert_int_eq(result, return_mul[_i]);
}
END_TEST

START_TEST(test_div) {
  s21_decimal dec_recult = {0};
  int result = s21_div(value_1[_i], value_2[_i], &dec_recult);
  ck_assert_int_eq(dec_recult.bits[0], result_div[_i].bits[0]);
  ck_assert_int_eq(dec_recult.bits[1], result_div[_i].bits[1]);
  ck_assert_int_eq(dec_recult.bits[2], result_div[_i].bits[2]);
  ck_assert_int_eq(dec_recult.bits[3], result_div[_i].bits[3]);
  ck_assert_int_eq(result, return_div[_i]);
}
END_TEST

Suite *test_arithmetic() {
  int tests = sizeof(value_1) / sizeof(s21_decimal);
  Suite *s = suite_create("\033[42m-=S21_DECIMAL_ARITHMETIC=-\033[0m");
  TCase *tc = tcase_create("S21_DECIMAL_ARITHMETIC");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, test_add, 0, tests);
  tcase_add_loop_test(tc, test_sub, 0, tests);
  tcase_add_loop_test(tc, test_mul, 0, tests);
  tcase_add_loop_test(tc, test_div, 0, tests);
  return s;
}