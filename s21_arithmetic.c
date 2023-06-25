#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 1;
  if (result && !value_1.error && !value_2.error) {
    int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
    s21_normalize(&value_1, &value_2);
    if (sign_1 == sign_2) {
      *result = s21_decimal_add(value_1, value_2);
    } else {
      if (sign_1) s21_swap_sign(&value_1);
      if (sign_2) s21_swap_sign(&value_2);
      if (s21_is_greater_or_equal(value_1, value_2)) {
        *result = s21_decimal_sub(value_1, value_2);
        if (sign_1) s21_swap_sign(result);
      } else {
        *result = s21_decimal_sub(value_2, value_1);
        if (sign_2) s21_swap_sign(result);
      }
    }
    status = result->error;
  }
  return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 1;
  if (result && !value_1.error && !value_2.error) {
    int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
    s21_normalize(&value_1, &value_2);
    if (sign_1 == sign_2) {
      if (sign_1) {
        if (s21_is_less_or_equal(value_1, value_2)) {
          *result = s21_decimal_sub(value_1, value_2);
        } else {
          *result = s21_decimal_sub(value_2, value_1);
          s21_swap_sign(result);
        }
      } else {
        if (s21_is_greater_or_equal(value_1, value_2))
          *result = s21_decimal_sub(value_1, value_2);
        else {
          *result = s21_decimal_sub(value_2, value_1);
          s21_swap_sign(result);
        }
      }
    } else {
      if (sign_1)
        *result = s21_decimal_add(value_1, value_2);
      else
        *result = s21_decimal_add(value_1, value_2);
    }
    status = result->error;
  }
  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 1;
  if (result && !value_1.error && !value_2.error) {
    int overflow = 0;
    s21_decimal temp = {{0, 0, 0, 0}, 0};
    *result = temp;
    int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
    while (!s21_is_decimal_zero(value_2) && !overflow) {
      if (value_2.bits[0] & 1) *result = s21_decimal_add(*result, value_1);
      value_1 = s21_decimal_shift_left(value_1, 1);
      value_2 = s21_decimal_shift_right(value_2, 1);
      overflow = result->error;
    }
    int scale = get_scale(value_1) + get_scale(value_2);
    if (scale > 28) {
      for (; scale > 28; scale--) {
        s21_decimal ten = {{10, 0, 0, 0}, 0};
        s21_div(*result, ten, result);
      }
    }
    set_scale(result, scale);
    if (sign_1 ^ sign_2) s21_swap_sign(result);
    status = result->error;
  }
  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 1;
  if (result && !value_1.error && !value_2.error) {
    if (s21_is_decimal_zero(value_2)) {
      result->error = DIVISION_BY_ZERO;
    } else {
      int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
      int result_int_3 = value_1.bits[3];
      if (sign_1) s21_swap_sign(&value_1);
      if (sign_2) s21_swap_sign(&value_2);
      *result = s21_decimal_div(value_1, value_2);
      result->bits[3] = result_int_3;
      if (sign_1 && sign_2)
        s21_swap_sign(result);
      else if (sign_1 ^ sign_2) {
        if (!s21_get_sign(*result)) s21_swap_sign(result);
      }
      int scale = get_scale(value_1) - get_scale(value_2);
      set_scale(result, (scale > 0) ? scale : 0);
    }
    status = result->error;
  }
  return status;
}

s21_decimal s21_decimal_add(s21_decimal value_1, s21_decimal value_2) {
  while (!s21_is_decimal_zero(value_2)) {
    s21_decimal temp = s21_decimal_and(value_1, value_2);
    value_1 = s21_decimal_xor(value_1, value_2);
    value_2 = s21_decimal_shift_left(temp, 1);
  }
  value_1.error = value_2.error;
  return value_1;
}

s21_decimal s21_decimal_sub(s21_decimal value_1, s21_decimal value_2) {
  while (!s21_is_decimal_zero(value_2)) {
    s21_decimal temp = s21_decimal_and(s21_decimal_not(value_1), value_2);
    value_1 = s21_decimal_xor(value_1, value_2);
    value_2 = s21_decimal_shift_left(temp, 1);
  }
  value_1.error = value_2.error;
  return value_1;
}

s21_decimal s21_decimal_div(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = {0};
  s21_decimal remainder = {0};
  for (int i = 95; i >= 0; i--) {
    s21_decimal one = {{1, 0, 0, 0}, 0};
    remainder = s21_decimal_shift_left(remainder, 1);
    remainder = s21_decimal_or(
        remainder, s21_decimal_and(s21_decimal_shift_right(value_1, i), one));
    if (s21_for_div(remainder, value_2)) {
      result = s21_decimal_or(result, s21_decimal_shift_left(one, i));
      remainder = s21_decimal_sub(remainder, value_2);
    }
  }
  return result;
}

int s21_for_div(s21_decimal value_1, s21_decimal value_2) {
  int status = TRUE;
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  s21_normalize(&value_1, &value_2);
  if (s21_is_equal(value_1, value_2)) {
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