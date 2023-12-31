#include "my_decimal.h"

int from_int_to_decimal(int src, my_decimal *dst) {
  int status = CONVERTATION_ERROR;
  if (dst) {
    my_decimal temp = {{abs(src), 0, 0, 0}, 0};
    *dst = temp;
    if (src < 0) swap_sign(dst);
    status = CONVERTATION_OK;
  }
  return status;
}

int from_float_to_decimal(float src, my_decimal *dst) {
  int status = CONVERTATION_ERROR;
  if (dst && !isinf(src) && !isnan(src)) {
    int exp = get_exp_of_float(src);
    my_decimal temp = {{0, 0, 0, 0}, 0};
    *dst = temp;
    if (!src) {
      dst->bits[0] = (int)src;
      status = CONVERTATION_OK;
    } else if (exp > -94 && exp < 95) {
      int scale = 0;
      int sign = 0;
      if (src < 0) {
        sign = 1;
        src = -src;
      }
      for (; !((int)src); src *= 10, scale++)
        ;
      for (int i = 0; i < 7 && scale < 28 && src < 999999; i++, scale++)
        src *= 10;
      dst->bits[0] = (int)src;
      set_scale(dst, scale);
      if (sign) swap_sign(dst);
      status = CONVERTATION_OK;
    }
  }
  return status;
}

int from_decimal_to_int(my_decimal src, int *dst) {
  my_truncate(src, &src);
  int status = CONVERTATION_ERROR;
  if (dst && !src.bits[2] && !src.bits[1] && !(src.bits[0] & (1u << 31))) {
    *dst = src.bits[0];
    if (get_sign(src)) *dst = -(*dst);
    status = CONVERTATION_OK;
  }
  return status;
}

int from_decimal_to_float(my_decimal src, float *dst) {
  int status = CONVERTATION_ERROR;
  if (dst && !src.bits[2] && !src.bits[1] && !(src.bits[0] & (1u << 31))) {
    *dst = src.bits[0];
    int scale = get_scale(src);
    *dst /= pow(10, scale);
    if (get_sign(src)) *dst = -(*dst);
    status = CONVERTATION_OK;
  }
  return status;
}

int get_exp_of_float(float src) {
  unsigned int fbits = *((unsigned int *)&src);
  int i = 0;
  int exp = 0;
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    if (i > 0 && i < 9 && !!(fbits & mask)) exp += pow(2, 8 - i);
    i++;
  }
  return exp - 127;
}