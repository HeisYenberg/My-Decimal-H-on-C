#include "tests.h"

int main() {
  int failed = 0;
  Suite *test_decimal[] = {test_arithmetic(), test_comparision(),
                           test_rounding(), test_convertation(), NULL};
  for (int i = 0; test_decimal[i]; i++) {
    SRunner *sr = srunner_create(test_decimal[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("Failed %d", failed);
  return 0;
}