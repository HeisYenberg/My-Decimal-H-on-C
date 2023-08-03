#include "my_decimal.h"

my_decimal my_decimal_shift_left(my_decimal value, int step) {
  unsigned int carry = 0;
  for (int j = 0; j < step; j++) {
    for (int i = 0; i < 3; i++) {
      unsigned int to_carry = (value.bits[i] & (1u << 31)) ? 1 : 0;
      value.bits[i] <<= 1;
      value.bits[i] |= carry;
      carry = to_carry;
    }
    if (carry) value.error = (get_sign(value)) ? TOO_SMALL : TOO_LARGE;
  }
  return value;
}

my_decimal my_decimal_shift_right(my_decimal value, int step) {
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

my_decimal my_decimal_or(my_decimal value_1, my_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    value_1.bits[i] |= value_2.bits[i];
  }
  return value_1;
}

my_decimal my_decimal_xor(my_decimal value_1, my_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    value_1.bits[i] ^= value_2.bits[i];
  }
  return value_1;
}

my_decimal my_decimal_and(my_decimal value_1, my_decimal value_2) {
  for (int i = 0; i < 3; i++) {
    value_1.bits[i] &= value_2.bits[i];
  }
  return value_1;
}

my_decimal my_decimal_not(my_decimal value) {
  for (int i = 0; i < 3; i++) {
    value.bits[i] = ~value.bits[i];
  }
  return value;
}