#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdlib.h>

enum comparison { FALSE, TRUE };

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
} my_decimal;

my_decimal my_decimal_shift_left(my_decimal value, int step);
my_decimal my_decimal_shift_right(my_decimal value, int step);
my_decimal my_decimal_or(my_decimal value_1, my_decimal value_2);
my_decimal my_decimal_xor(my_decimal value_1, my_decimal value_2);
my_decimal my_decimal_and(my_decimal value_1, my_decimal value_2);
my_decimal my_decimal_not(my_decimal value);

int get_sign(my_decimal value);
void swap_sign(my_decimal *value);
int get_scale(my_decimal value);
void set_scale(my_decimal *value, int scale);

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);
my_decimal decimal_add(my_decimal value_1, my_decimal value_2);
my_decimal decimal_sub(my_decimal value_1, my_decimal value_2);
my_decimal decimal_div(my_decimal value_1, my_decimal value_2);
int for_div(my_decimal value_1, my_decimal value_2);

int my_is_less(my_decimal value_1, my_decimal value_2);
int my_is_less_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_greater(my_decimal value_1, my_decimal value_2);
int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_equal(my_decimal value_1, my_decimal value_2);
int my_is_not_equal(my_decimal value_1, my_decimal value_2);
int my_is_decimal_zero(my_decimal value);

int from_int_to_decimal(int src, my_decimal *dst);
int from_float_to_decimal(float src, my_decimal *dst);
int from_decimal_to_int(my_decimal src, int *dst);
int from_decimal_to_float(my_decimal src, float *dst);
int get_exp_of_float(float src);

void normalize(my_decimal *value_1, my_decimal *value_2);
int mul_or_div_ten(my_decimal *value_1, my_decimal *value_2, int difference);
int my_round(my_decimal value, my_decimal *result);
int my_floor(my_decimal value, my_decimal *result);
int my_truncate(my_decimal value, my_decimal *result);
int my_negate(my_decimal value, my_decimal *result);

#endif