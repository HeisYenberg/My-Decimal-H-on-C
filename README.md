# S21-Decimal

## My version of the decimal.h library in the C programming language.

## Usage :

- To build a library run `make s21_decimal.a`
- To see tests run `make test`, might need to install `check`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`

### Overview of "s21_decimal.h" functions

| No. | Function                                                                    | Description                       |
|-----|-----------------------------------------------------------------------------|-----------------------------------|
| 1   | int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); | Addition of decimals              |
| 2   | int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); | Substraction of decimals          |
| 3   | int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); | Multiplication of decimals        |
| 4   | int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); | Division of decimals              |
| 5   | int s21_is_less(s21_decimal, s21_decimal);                                  | Less than operator                |
| 6   | int s21_is_less_or_equal(s21_decimal, s21_decimal);                         | Less than or equal to orperator   |
| 7   | int s21_is_greater(s21_decimal, s21_decimal);                               | Greater than operator             |
| 8   | int s21_is_greater_or_equal(s21_decimal, s21_decimal);                      | Greater than or equal to operator |
| 9   | int s21_is_equal(s21_decimal, s21_decimal);                                 | Equal to operator                 |
| 10  | int s21_is_not_equal(s21_decimal, s21_decimal);                             | Not equal to operator             |
| 11  | int s21_from_int_to_decimal(int src, s21_decimal *dst);                     | From int to decimal converter     |
| 12  | int s21_from_float_to_decimal(float src, s21_decimal *dst);                 | From float to decimal converter   |
| 13  | int s21_from_decimal_to_int(s21_decimal src, int *dst);                     | From decimal to int converter     |
| 14  | int s21_from_decimal_to_float(s21_decimal src, float *dst);                 | From decimal to float converter   |
| 15  | int s21_floor(s21_decimal value, s21_decimal *result);                      | Decimal floor                     |
| 16  | int s21_round(s21_decimal value, s21_decimal *result);                      | Decimal round                     |
| 17  | int s21_truncate(s21_decimal value, s21_decimal *result);                   | Decimal truncate                  |
| 18  | int s21_negate(s21_decimal value, s21_decimal *result);                     | Decimal negate                    |