#include "s21_decimal.h"

int s21_get_sign(s21_decimal value) { return value.bits[3] >> 31; }

void s21_swap_sign(s21_decimal *value) { value->bits[3] ^= 1u << 31; }

int get_scale(s21_decimal value) {
  if (s21_get_sign(value)) s21_swap_sign(&value);
  return value.bits[3] >> 16;
}

void set_scale(s21_decimal *value, int scale) {
  int sign = s21_get_sign(*value);
  if (sign) s21_swap_sign(value);
  value->bits[3] = scale << 16;
  if (sign) s21_swap_sign(value);
}

void s21_normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = get_scale(*value_1), scale_2 = get_scale(*value_2);
  int difference = scale_1 - scale_2, i = 0;
  if (difference > 0) {
    i = mul_or_div_ten(value_1, value_2, difference);
  } else {
    i = mul_or_div_ten(value_2, value_1, -difference);
  }
  int scale_result =
      ((scale_1 > scale_2) ? scale_1 : scale_2) - (abs(difference) - i);
  set_scale(value_1, scale_result);
  set_scale(value_2, scale_result);
}

int mul_or_div_ten(s21_decimal *value_1, s21_decimal *value_2, int difference) {
  int overflow = 0, i = 0;
  s21_decimal ten = {{10, 0, 0, 0}, 0};
  for (; i < difference && !overflow; i++) {
    s21_decimal temp = {0};
    overflow = s21_mul(*value_2, ten, &temp);
    if (!overflow)
      *value_2 = temp;
    else
      i--;
  }
  if (difference > i) {
    s21_decimal one = {{1, 0, 0, 0}, 0};
    for (int j = 0; j < (difference - i); j++) {
      int remainder = value_1->bits[0] % 10;
      s21_div(*value_1, ten, value_1);
      if (remainder > 5 || (remainder == 5 && value_1->bits[0] & 1)) {
        *value_1 = s21_decimal_add(*value_1, one);
      }
    }
  }
  return i;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  int scale = get_scale(value);
  if (result && !value.error) {
    *result = value;
    if (scale) {
      s21_decimal ten = {{10, 0, 0, 0}, 0};
      for (int i = scale; i > 1; i--) {
        *result = s21_decimal_div(*result, ten);
      }
      int remainder = result->bits[0] % 10;
      s21_div(*result, ten, result);
      if (remainder >= 5) {
        s21_decimal one = {{1, 0, 0, 0}, 0};
        *result = s21_decimal_add(*result, one);
      }
      set_scale(result, 0);
    }
    status = CALCULATION_OK;
  }
  return status;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int scale = get_scale(value);
  int status = CALCULATION_ERROR;
  if (result && !value.error) {
    *result = value;
    if (scale) {
      s21_decimal ten = {{10, 0, 0, 0}, 0};
      int remainder = 0;
      for (int i = scale; i > 1; i--) {
        if (result->bits[0] % 10) remainder = 1;
        s21_div(*result, ten, result);
      }
      s21_div(*result, ten, result);
      if (s21_get_sign(value) && remainder != 0) {
        s21_decimal one = {{1, 0, 0, 0}, 0};
        //      s21_add(*result, one, result);
        *result = s21_decimal_add(*result, one);
      }
      set_scale(result, 0);
    }
    status = CALCULATION_OK;
  }
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result && !value.error) {
    int scale = get_scale(value);
    *result = value;
    s21_decimal ten = {{10, 0, 0, 0}, 0};
    for (int i = scale; i > 0; i--) {
      s21_div(*result, ten, result);
    }
    set_scale(result, 0);
    status = CALCULATION_OK;
  }
  return status;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result && !value.error) {
    *result = value;
    s21_swap_sign(result);
    status = CALCULATION_OK;
  }
  return status;
}