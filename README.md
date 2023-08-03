# My-Decimal-H-on-C

## My version of the decimal.h library in the C programming language.

## Usage :

- To build a library run `make my_decimal.a`
- To see tests run `make test`, might need to install `check`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`

### Overview of "my_decimal.h" functions

| No. | Function                                                             | Description                       |
|-----|----------------------------------------------------------------------|-----------------------------------|
| 1   | int add(my_decimal value_1, my_decimal value_2, my_decimal *result); | Addition of decimals              |
| 2   | int sub(my_decimal value_1, my_decimal value_2, my_decimal *result); | Substraction of decimals          |
| 3   | int mul(my_decimal value_1, my_decimal value_2, my_decimal *result); | Multiplication of decimals        |
| 4   | int div(my_decimal value_1, my_decimal value_2, my_decimal *result); | Division of decimals              |
| 5   | int is_less(my_decimal, my_decimal);                                 | Less than operator                |
| 6   | int is_less_or_equal(my_decimal, my_decimal);                        | Less than or equal to orperator   |
| 7   | int is_greater(my_decimal, my_decimal);                              | Greater than operator             |
| 8   | int is_greater_or_equal(my_decimal, my_decimal);                     | Greater than or equal to operator |
| 9   | int is_equal(my_decimal, my_decimal);                                | Equal to operator                 |
| 10  | int is_not_equal(my_decimal, my_decimal);                            | Not equal to operator             |
| 11  | int from_int_to_decimal(int src, my_decimal *dst);                   | From int to decimal converter     |
| 12  | int from_float_to_decimal(float src, my_decimal *dst);               | From float to decimal converter   |
| 13  | int from_decimal_to_int(my_decimal src, int *dst);                   | From decimal to int converter     |
| 14  | int from_decimal_to_float(my_decimal src, float *dst);               | From decimal to float converter   |
| 15  | int floor(my_decimal value, my_decimal *result);                     | Decimal floor                     |
| 16  | int round(my_decimal value, my_decimal *result);                     | Decimal round                     |
| 17  | int truncate(my_decimal value, my_decimal *result);                  | Decimal truncate                  |
| 18  | int negate(my_decimal value, my_decimal *result);                    | Decimal negate                    |