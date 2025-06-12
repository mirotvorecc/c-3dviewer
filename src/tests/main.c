#include "main.h"

int main() {
  int number_failed = 0;

  Suite *test[] = {parser_suite(), translation_test(), rotation_test(), NULL};

  for (int i = 0; test[i] != NULL; i++) {
    printf("\n");
    SRunner *sr = srunner_create(test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  return (number_failed == 0) ? 0 : 1;
}
