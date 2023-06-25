#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int greater = FALSE;
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  s21_normalize(&value_1, &value_2);
  if (s21_is_equal(value_1, value_2)) {
    greater = FALSE;
  } else if (!sign_1 && sign_2) {
    greater = TRUE;
  } else if (sign_1 == sign_2) {
    int i = 2;
    while (value_1.bits[i] == value_2.bits[i] && i > -1) i--;
    if (i > -1) greater = value_1.bits[i] > value_2.bits[i];
    if (i > -1 && sign_1) greater = !greater;
  }
  return greater;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int equal = TRUE;
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  s21_normalize(&value_1, &value_2);
  if (s21_is_decimal_zero(value_1) && s21_is_decimal_zero(value_2))
    equal = TRUE;
  else if (sign_1 ^ sign_2)
    equal = FALSE;
  else {
    for (int i = 2; i >= 0 && equal; i--) {
      if (value_1.bits[i] != value_2.bits[i]) equal = 0;
    }
  }
  return equal;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int less_or_equal =
      (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2)) ? TRUE
                                                                        : FALSE;
  return less_or_equal;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int greater_or_equal =
      (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2))
          ? TRUE
          : FALSE;
  return greater_or_equal;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int less = FALSE;
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  s21_normalize(&value_1, &value_2);
  if (s21_is_equal(value_1, value_2)) {
    less = FALSE;
  } else if (sign_1 && !sign_2) {
    less = TRUE;
  } else if (sign_1 == sign_2) {
    int i = 2;
    while (value_1.bits[i] == value_2.bits[i] && i > -1) i--;
    if (i > -1) less = value_1.bits[i] < value_2.bits[i];
    if (i > -1 && sign_1) less = !less;
  }
  return less;
}

int s21_is_decimal_zero(s21_decimal value) {
  int zero = FALSE;
  if (!value.bits[0] && !value.bits[1] && !value.bits[2]) zero = TRUE;
  return zero;
}