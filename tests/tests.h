#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

Suite *test_arithmetic();
Suite *test_comparision();
Suite *test_rounding();
Suite *test_convertation();

#endif