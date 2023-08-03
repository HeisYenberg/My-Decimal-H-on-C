#include "my_decimal.h"

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status = 1;
  if (result && !value_1.error && !value_2.error) {
    int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
    normalize(&value_1, &value_2);
    if (sign_1 == sign_2) {
      *result = decimal_add(value_1, value_2);
    } else {
      if (sign_1) swap_sign(&value_1);
      if (sign_2) swap_sign(&value_2);
      if (my_is_greater_or_equal(value_1, value_2)) {
        *result = decimal_sub(value_1, value_2);
        if (sign_1) swap_sign(result);
      } else {
        *result = decimal_sub(value_2, value_1);
        if (sign_2) swap_sign(result);
      }
    }
    status = result->error;
  }
  return status;
}

int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status = 1;
  if (result && !value_1.error && !value_2.error) {
    int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
    normalize(&value_1, &value_2);
    if (sign_1 == sign_2) {
      if (sign_1) {
        if (my_is_less_or_equal(value_1, value_2)) {
          *result = decimal_sub(value_1, value_2);
        } else {
          *result = decimal_sub(value_2, value_1);
          swap_sign(result);
        }
      } else {
        if (my_is_greater_or_equal(value_1, value_2))
          *result = decimal_sub(value_1, value_2);
        else {
          *result = decimal_sub(value_2, value_1);
          swap_sign(result);
        }
      }
    } else {
      if (sign_1)
        *result = decimal_add(value_1, value_2);
      else
        *result = decimal_add(value_1, value_2);
    }
    status = result->error;
  }
  return status;
}

int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status = !OK;
  if (result && !value_1.error && !value_2.error) {
    int overflow = OK;
    my_decimal temp = {{0, 0, 0, 0}, 0};
    *result = temp;
    int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
    while (!my_is_decimal_zero(value_2) && !overflow) {
      if (value_2.bits[0] & 1) *result = decimal_add(*result, value_1);
      value_1 = my_decimal_shift_left(value_1, 1);
      value_2 = my_decimal_shift_right(value_2, 1);
      overflow = result->error;
    }
    int scale = get_scale(value_1) + get_scale(value_2);
    if (scale > 28) {
      for (; scale > 28; scale--) {
        my_decimal ten = {{10, 0, 0, 0}, 0};
        my_div(*result, ten, result);
      }
    }
    set_scale(result, scale);
    if (sign_1 ^ sign_2) swap_sign(result);
    status = result->error;
  }
  return status;
}

int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status = 1;
  if (result && !value_1.error && !value_2.error) {
    if (my_is_decimal_zero(value_2)) {
      result->error = DIVISION_BY_ZERO;
    } else {
      int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
      int result_int_3 = value_1.bits[3];
      if (sign_1) swap_sign(&value_1);
      if (sign_2) swap_sign(&value_2);
      *result = decimal_div(value_1, value_2);
      result->bits[3] = result_int_3;
      if (sign_1 && sign_2)
        swap_sign(result);
      else if (sign_1 ^ sign_2) {
        if (!get_sign(*result)) swap_sign(result);
      }
      int scale = get_scale(value_1) - get_scale(value_2);
      set_scale(result, (scale > 0) ? scale : 0);
    }
    status = result->error;
  }
  return status;
}

my_decimal decimal_add(my_decimal value_1, my_decimal value_2) {
  while (!my_is_decimal_zero(value_2)) {
    my_decimal temp = my_decimal_and(value_1, value_2);
    value_1 = my_decimal_xor(value_1, value_2);
    value_2 = my_decimal_shift_left(temp, 1);
  }
  value_1.error = value_2.error;
  return value_1;
}

my_decimal decimal_sub(my_decimal value_1, my_decimal value_2) {
  while (!my_is_decimal_zero(value_2)) {
    my_decimal temp = my_decimal_and(my_decimal_not(value_1), value_2);
    value_1 = my_decimal_xor(value_1, value_2);
    value_2 = my_decimal_shift_left(temp, 1);
  }
  value_1.error = value_2.error;
  return value_1;
}

my_decimal decimal_div(my_decimal value_1, my_decimal value_2) {
  my_decimal result = {0};
  my_decimal remainder = {0};
  for (int i = 95; i >= 0; i--) {
    my_decimal one = {{1, 0, 0, 0}, 0};
    remainder = my_decimal_shift_left(remainder, 1);
    remainder = my_decimal_or(
        remainder, my_decimal_and(my_decimal_shift_right(value_1, i), one));
    if (for_div(remainder, value_2)) {
      result = my_decimal_or(result, my_decimal_shift_left(one, i));
      remainder = decimal_sub(remainder, value_2);
    }
  }
  return result;
}

int for_div(my_decimal value_1, my_decimal value_2) {
  int status = TRUE;
  int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
  normalize(&value_1, &value_2);
  if (my_is_equal(value_1, value_2)) {
    status = TRUE;
  } else if (sign_1 && !sign_2) {
    status = FALSE;
  } else if (!sign_1 && sign_2) {
    status = TRUE;
  } else if (sign_1 && sign_2) {
    for (int i = 2; i >= 0 && status; i--) {
      if (value_1.bits[i] > value_2.bits[i]) status = FALSE;
    }
  } else {
    for (int i = 2; i >= 0 && status; i--) {
      if (value_1.bits[i] < value_2.bits[i]) status = FALSE;
    }
  }
  return status;
}