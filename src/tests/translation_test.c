#include "main.h"

START_TEST(translation_1) {
  const char filename[] = "./tests/cube2.obj";
  Surface surface[200] = {0};
  Mesh mesh[200] = {0};

  int status = parse_obj_file(filename, surface, mesh);

  ck_assert_int_eq(status, 0);

  Point axis_prev = {0, 0, 0, 1.0};
  Point axis_translated = {2.0, 0, 0, 1.0};

  translation(surface, axis_translated, &axis_prev);

  ck_assert_double_eq(surface->one_point[0]->x, 3.0);
  ck_assert_double_eq(surface->one_point[1]->x, 3.0);
  ck_assert_double_eq(surface->one_point[2]->x, 1.0);
  ck_assert_double_eq(surface->one_point[3]->x, 1.0);
  ck_assert_double_eq(surface->one_point[4]->x, 3.0);
  ck_assert_double_eq(surface->one_point[5]->x, 3.0);
  ck_assert_double_eq(surface->one_point[6]->x, 1.0);
  ck_assert_double_eq(surface->one_point[7]->x, 1.0);

  free_surface(surface);
  free_mesh(mesh);
}
END_TEST;

START_TEST(translation_2) {
  const char filename[] = "./tests/cube2.obj";
  Surface surface[200] = {0};
  Mesh mesh[200] = {0};

  int status = parse_obj_file(filename, surface, mesh);

  ck_assert_int_eq(status, 0);

  Point axis_prev = {0, 0, 0, 1.0};
  Point axis_translated = {0.0, 17.91, 0, 1.0};

  translation(surface, axis_translated, &axis_prev);

  ck_assert_double_eq_tol(surface->one_point[0]->y, 16.91, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[1]->y, 16.91, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[2]->y, 16.91, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[3]->y, 16.91, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[4]->y, 18.91, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[5]->y, 18.91, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[6]->y, 18.91, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[7]->y, 18.91, 0.000001);

  free_surface(surface);
  free_mesh(mesh);
}
END_TEST;

START_TEST(translation_3) {
  const char filename[] = "./tests/cube2.obj";
  Surface surface[200] = {0};
  Mesh mesh[200] = {0};

  int status = parse_obj_file(filename, surface, mesh);

  ck_assert_int_eq(status, 0);

  Point axis_prev = {0, 0, 0, 1.0};
  Point axis_translated = {13.75, 4.16, 30.12, 0.1};

  translation(surface, axis_translated, &axis_prev);

  ck_assert_double_eq_tol(surface->one_point[0]->x, 1.475, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[1]->x, 1.475, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[2]->x, 1.275, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[3]->x, 1.275, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[4]->x, 1.475, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[5]->x, 1.475, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[6]->x, 1.275, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[7]->x, 1.275, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[0]->y, 0.316, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[1]->y, 0.316, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[2]->y, 0.316, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[3]->y, 0.316, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[4]->y, 0.516, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[5]->y, 0.516, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[6]->y, 0.516, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[7]->y, 0.516, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[0]->z, 2.912, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[1]->z, 3.112, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[2]->z, 3.112, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[3]->z, 2.912, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[4]->z, 2.912, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[5]->z, 3.112, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[6]->z, 3.112, 0.000001);
  ck_assert_double_eq_tol(surface->one_point[7]->z, 2.912, 0.000001);

  free_surface(surface);
  free_mesh(mesh);
}
END_TEST;

Suite *translation_test(void) {
  Suite *s = suite_create("\033[45m Translation test \033[0m");
  TCase *tc = tcase_create("translation_test");

  tcase_add_test(tc, translation_1);
  tcase_add_test(tc, translation_2);
  tcase_add_test(tc, translation_3);

  suite_add_tcase(s, tc);
  return s;
}
