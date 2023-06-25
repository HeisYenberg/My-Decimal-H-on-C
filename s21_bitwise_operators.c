#include "s21_decimal.h"

s21_decimal s21_decimal_shift_left(s21_decimal value, int step) {
  unsigned int carry = 0;
  for (int j = 0; j < step; j++) {
    for (int i = 0; i < 3; i++) {
      unsigned int to_carry = (value.bits[i] & (1u << 31)) ? 1 : 0;
      value.bits[i] <<= 1;
      value.bits[i] |= carry;
      carry = to_carry;
    }
    if (carry) value.error = (s21_get_sign(value)) ? TOO_SMALL : TOO_LARGE;
  }
  return value;
}

s21_decimal s21_decimal_shift_right(s21_decimal value, int step) {
  unsigned int carry = 0;
  for (int j = 0; j < step; j++) {
    for (int i = 2; i >= 0; i--) {
      unsigned int to_carry = (value.bits[i] & 1) ? (1u << 31) : 0;
      value.bits[i] >>= 1;
      value.bits[i] |= carry;
      carry = to_carry;
    }
  }
  return value;
}

s21_decimal s21_decimal_or(s21_decimal value_1, s21_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    value_1.bits[i] |= value_2.bits[i];
  }
  return value_1;
}

s21_decimal s21_decimal_xor(s21_decimal value_1, s21_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    value_1.bits[i] ^= value_2.bits[i];
  }
  return value_1;
}

s21_decimal s21_decimal_and(s21_decimal value_1, s21_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    value_1.bits[i] &= value_2.bits[i];
  }
  return value_1;
}

s21_decimal s21_decimal_not(s21_decimal value) {
  for (int i = 0; i < 3; i++) {
    value.bits[i] = ~value.bits[i];
  }
  return value;
}