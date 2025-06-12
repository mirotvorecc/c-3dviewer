#include "affine.h"

void rotate_x(Surface *surface, double x_angle);
void rotate_y(Surface *surface, double y_angle);
void rotate_z(Surface *surface, double z_angle);

void translation(Surface *surface, Point axis_translated, Point *axis_prev) {
  double delta_x = axis_prev->x - axis_translated.x;
  double delta_y = axis_prev->y - axis_translated.y;
  double delta_z = axis_prev->z - axis_translated.z;

  double delta_scale = axis_translated.scale / axis_prev->scale;

  axis_prev->x = axis_translated.x;
  axis_prev->y = axis_translated.y;
  axis_prev->z = axis_translated.z;

  axis_prev->scale = axis_translated.scale;

  for (int i = 0; i < surface->amount_of_points; i++) {
    surface->one_point[i]->x -= delta_x;
    surface->one_point[i]->x *= delta_scale;
    surface->one_point[i]->y -= delta_y;
    surface->one_point[i]->y *= delta_scale;
    surface->one_point[i]->z -= delta_z;
    surface->one_point[i]->z *= delta_scale;
  }
}

void rotation(Surface *surface, Point axis_rotated, Point *axis_rotated_prev) {
  double x_angle = axis_rotated.x - axis_rotated_prev->x;
  double y_angle = axis_rotated.y - axis_rotated_prev->y;
  double z_angle = axis_rotated.z - axis_rotated_prev->z;

  axis_rotated_prev->x = axis_rotated.x;
  axis_rotated_prev->y = axis_rotated.y;
  axis_rotated_prev->z = axis_rotated.z;

  rotate_x(surface, x_angle);
  rotate_y(surface, y_angle);
  rotate_z(surface, z_angle);
}

void rotate_x(Surface *surface, double x_angle) {
  for (int i = 0; i < surface->amount_of_points; i++) {
    double y = 0.0, z = 0.0;
    y = surface->one_point[i]->y;
    z = surface->one_point[i]->z;
    surface->one_point[i]->y = y * cos(x_angle) - z * sin(x_angle);
    surface->one_point[i]->z = y * sin(x_angle) + z * cos(x_angle);
  }
}

void rotate_y(Surface *surface, double y_angle) {
  for (int i = 0; i < surface->amount_of_points; i++) {
    double x = 0.0, z = 0.0;
    x = surface->one_point[i]->x;
    z = surface->one_point[i]->z;
    surface->one_point[i]->x = x * cos(y_angle) + z * sin(y_angle);
    surface->one_point[i]->z = -x * sin(y_angle) + z * cos(y_angle);
  }
}

void rotate_z(Surface *surface, double z_angle) {
  for (int i = 0; i < surface->amount_of_points; i++) {
    double x = 0.0, y = 0.0;
    x = surface->one_point[i]->x;
    y = surface->one_point[i]->y;
    surface->one_point[i]->x = x * cos(z_angle) - y * sin(z_angle);
    surface->one_point[i]->y = x * sin(z_angle) + y * cos(z_angle);
  }
}
