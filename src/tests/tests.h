#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdio.h>

#include "../my_decimal/my_decimal.h"

Suite *test_arithmetic();
Suite *test_comparison();
Suite *test_rounding();
Suite *test_convertation();

#endif