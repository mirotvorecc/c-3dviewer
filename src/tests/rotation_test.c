#include "main.h"

START_TEST(rotation_1) {
  const char filename[] = "./tests/cube2.obj";
  Surface surface[200] = {0};
  Mesh mesh[200] = {0};

  int status = parse_obj_file(filename, surface, mesh);

  ck_assert_int_eq(status, 0);

  Point axis_rotated_prev = {0.0, 0.0, 0.0, 1.0};
  Point axis_rotated = {0.1, 0.4, 0.0, 1.0};

  rotation(surface, axis_rotated, &axis_rotated_prev);

  ck_assert_double_eq_tol(surface->one_point[0]->x, 0.494711, 0.00001);
  ck_assert_double_eq_tol(surface->one_point[0]->y, -0.895171, 0.00001);
  ck_assert_double_eq_tol(surface->one_point[0]->z, -1.39783, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[1]->x, 1.26966, 0.0001);
  ck_assert_float_eq_tol(surface->one_point[1]->y, -1.09484, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[1]->z, 0.435089, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[2]->x, -0.572465, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[2]->y, -1.09484, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[2]->z, 1.21393, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[3]->x, -1.34741, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[3]->y, -0.895171, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[3]->z, -0.618994, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[4]->x, 0.572465, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[4]->y, 1.09484, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[4]->z, -1.21393, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[5]->x, 1.34741, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[5]->y, 0.895171, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[5]->z, 0.618994, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[6]->x, -0.494711, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[6]->y, 0.895171, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[6]->z, 1.39783, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[7]->x, -1.26966, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[7]->y, 1.09484, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[7]->z, -0.435089, 0.00001);

  free_surface(surface);
  free_mesh(mesh);
}
END_TEST;

START_TEST(rotation_2) {
  const char filename[] = "./tests/cube2.obj";
  Surface surface[200] = {0};
  Mesh mesh[200] = {0};

  int status = parse_obj_file(filename, surface, mesh);

  ck_assert_int_eq(status, 0);

  Point axis_rotated_prev = {0.0, 0.0, 0.0, 1.0};
  Point axis_rotated = {0.1, 0.4, 9.39, 1.0};

  rotation(surface, axis_rotated, &axis_rotated_prev);

  ck_assert_double_eq_tol(surface->one_point[0]->x, -0.463286, 0.00001);
  ck_assert_double_eq_tol(surface->one_point[0]->y, 0.911831, 0.00001);
  ck_assert_double_eq_tol(surface->one_point[0]->z, -1.39783, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[1]->x, -1.23082, 0.0001);
  ck_assert_float_eq_tol(surface->one_point[1]->y, 1.13832, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[1]->z, 0.435089, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[2]->x, 0.610187, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[2]->y, 1.07427, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[2]->z, 1.21393, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[3]->x, 1.37772, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[3]->y, 0.847779, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[3]->z, -0.618994, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[4]->x, -0.610187, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[4]->y, -1.07427, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[4]->z, -1.21393, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[5]->x, -1.37772, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[5]->y, -0.847779, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[5]->z, 0.618994, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[6]->x, 0.463286, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[6]->y, -0.911831, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[6]->z, 1.39783, 0.00001);

  ck_assert_float_eq_tol(surface->one_point[7]->x, 1.23082, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[7]->y, -1.13832, 0.00001);
  ck_assert_float_eq_tol(surface->one_point[7]->z, -0.435089, 0.00001);

  free_surface(surface);
  free_mesh(mesh);
}
END_TEST;

Suite *rotation_test(void) {
  Suite *s = suite_create("\033[45m Rotation test \033[0m");
  TCase *tc = tcase_create("rotaion_test");

  tcase_add_test(tc, rotation_1);
  tcase_add_test(tc, rotation_2);

  suite_add_tcase(s, tc);
  return s;
}
