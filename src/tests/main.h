#ifndef SRC_TESTS_S21_TEST_H_
#define SRC_TESTS_S21_TEST_H_

#include "affine.h"
#include "check.h"
#include "parser.h"

Suite *translation_test(void);
Suite *rotation_test(void);
Suite *parser_suite(void);

#endif  // SRC_TESTS_S21_TEST_H_
