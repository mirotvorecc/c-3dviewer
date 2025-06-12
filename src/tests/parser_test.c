#include "main.h"

START_TEST(test_open_file) {
  FILE *file;
  int status;

  status = open_file("non_existent_file.obj", &file);
  ck_assert_int_eq(status, OPEN_FILE_ERROR);

  status = open_file("./tests/cube1.obj", &file);
  ck_assert_int_eq(status, NOT_ERROR);
  fclose(file);
}
END_TEST

START_TEST(test_allocate_memory) {
  Surface surface;
  Mesh mesh;
  int status;

  status = allocate_memory(&surface, &mesh);
  ck_assert_int_eq(status, NOT_ERROR);
  ck_assert_ptr_nonnull(surface.one_point);
  ck_assert_ptr_nonnull(mesh.one_face);

  free(surface.one_point);
  free(mesh.one_face);
}
END_TEST

START_TEST(test_uncorrect_file) {
  Surface surface[200] = {0};
  Mesh mesh[200] = {0};
  int status_flag;

  status_flag = parse_obj_file("./tests/cube3.obj", surface, mesh);
  // status_flag = parse_obj_file("./tests/crashed_cube.obj", surface, mesh);
  ck_assert_int_eq(status_flag, PARSER_ERROR);
}
END_TEST

START_TEST(test_parse_obj_file) {
  Surface surface[200] = {0};
  Mesh mesh[200] = {0};
  int status_flag;

  status_flag = parse_obj_file("non_existent_file.obj", surface, mesh);
  ck_assert_int_eq(status_flag, OPEN_FILE_ERROR);

  status_flag = parse_obj_file("./tests/cube1.obj", surface, mesh);
  ck_assert_int_eq(status_flag, NOT_ERROR);
  free_surface(surface);
  free_mesh(mesh);
}
END_TEST

Suite *parser_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45m Parser tests \033[0m");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_open_file);
  tcase_add_test(tc_core, test_allocate_memory);

  tcase_add_test(tc_core, test_uncorrect_file);
  tcase_add_test(tc_core, test_parse_obj_file);

  suite_add_tcase(s, tc_core);

  return s;
}
