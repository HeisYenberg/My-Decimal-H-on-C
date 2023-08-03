#include "my_decimal.h"

int get_sign(my_decimal value) { return value.bits[3] >> 31; }

void swap_sign(my_decimal *value) { value->bits[3] ^= 1u << 31; }

int get_scale(my_decimal value) {
  if (get_sign(value)) swap_sign(&value);
  return value.bits[3] >> 16;
}

void set_scale(my_decimal *value, int scale) {
  int sign = get_sign(*value);
  if (sign) swap_sign(value);
  value->bits[3] = scale << 16;
  if (sign) swap_sign(value);
}

void normalize(my_decimal *value_1, my_decimal *value_2) {
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

int mul_or_div_ten(my_decimal *value_1, my_decimal *value_2, int difference) {
  int overflow = 0, i = 0;
  my_decimal ten = {{10, 0, 0, 0}, 0};
  for (; i < difference && !overflow; i++) {
    my_decimal temp = {0};
    overflow = my_mul(*value_2, ten, &temp);
    if (!overflow)
      *value_2 = temp;
    else
      i--;
  }
  if (difference > i) {
    my_decimal one = {{1, 0, 0, 0}, 0};
    for (int j = 0; j < (difference - i); j++) {
      int remainder = value_1->bits[0] % 10;
      my_div(*value_1, ten, value_1);
      if (remainder > 5 || (remainder == 5 && value_1->bits[0] & 1)) {
        *value_1 = decimal_add(*value_1, one);
      }
    }
  }
  return i;
}

int my_round(my_decimal value, my_decimal *result) {
  int status = CALCULATION_ERROR;
  int scale = get_scale(value);
  if (result && !value.error) {
    *result = value;
    if (scale) {
      my_decimal ten = {{10, 0, 0, 0}, 0};
      for (int i = scale; i > 1; i--) {
        *result = decimal_div(*result, ten);
      }
      int remainder = result->bits[0] % 10;
      my_div(*result, ten, result);
      if (remainder >= 5) {
        my_decimal one = {{1, 0, 0, 0}, 0};
        *result = decimal_add(*result, one);
      }
      set_scale(result, 0);
    }
    status = CALCULATION_OK;
  }
  return status;
}

int my_floor(my_decimal value, my_decimal *result) {
  int scale = get_scale(value);
  int status = CALCULATION_ERROR;
  if (result && !value.error) {
    *result = value;
    if (scale) {
      my_decimal ten = {{10, 0, 0, 0}, 0};
      int remainder = 0;
      for (int i = scale; i > 1; i--) {
        if (result->bits[0] % 10) remainder = 1;
        my_div(*result, ten, result);
      }
      my_div(*result, ten, result);
      if (get_sign(value) && remainder != 0) {
        my_decimal one = {{1, 0, 0, 0}, 0};
        //      my_add(*result, one, result);
        *result = decimal_add(*result, one);
      }
      set_scale(result, 0);
    }
    status = CALCULATION_OK;
  }
  return status;
}

int my_truncate(my_decimal value, my_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result && !value.error) {
    int scale = get_scale(value);
    *result = value;
    my_decimal ten = {{10, 0, 0, 0}, 0};
    for (int i = scale; i > 0; i--) {
      my_div(*result, ten, result);
    }
    set_scale(result, 0);
    status = CALCULATION_OK;
  }
  return status;
}

int my_negate(my_decimal value, my_decimal *result) {
  int status = CALCULATION_ERROR;
  if (result && !value.error) {
    *result = value;
    swap_sign(result);
    status = CALCULATION_OK;
  }
  return status;
}