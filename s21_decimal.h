#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdlib.h>

enum comparision { FALSE, TRUE };

enum convertation { CONVERTATION_OK, CONVERTATION_ERROR };

enum rounding { CALCULATION_OK, CALCULATION_ERROR };

typedef enum arithmetic {
  OK,
  TOO_LARGE,
  TOO_SMALL,
  DIVISION_BY_ZERO
} value_type;

typedef struct {
  unsigned int bits[4];
  value_type error;
} s21_decimal;

s21_decimal s21_decimal_shift_left(s21_decimal value, int step);
s21_decimal s21_decimal_shift_right(s21_decimal value, int step);
s21_decimal s21_decimal_or(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_decimal_xor(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_decimal_and(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_decimal_not(s21_decimal value);

int s21_get_sign(s21_decimal value);
void s21_swap_sign(s21_decimal *value);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal s21_decimal_add(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_decimal_sub(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_decimal_div(s21_decimal value_1, s21_decimal value_2);
int s21_for_div(s21_decimal value_1, s21_decimal value_2);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_decimal_zero(s21_decimal value);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int get_exp_of_float(float src);

void s21_normalize(s21_decimal *value_1, s21_decimal *value_2);
int mul_or_div_ten(s21_decimal *value_1, s21_decimal *value_2, int difference);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif