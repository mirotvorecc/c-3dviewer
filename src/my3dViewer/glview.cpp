#include "glview.h"

#include "affine.h"
#include "iostream"

glView::glView(QWidget *parent) : QOpenGLWidget(parent) {}

void glView::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0 / 255.f, 0 / 255.f, 0 / 255.f, 1);
  glEnable(GL_DEPTH_TEST);
}
void glView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}
void glView::paintGL() {  // функцию надо будет исправлять чтобы отрисовывать
                          // объекные фигуры
  if (isPaint) {
    glClearColor(static_cast<GLfloat>(background_color.redF()),
                 static_cast<GLfloat>(background_color.greenF()),
                 static_cast<GLfloat>(background_color.blueF()), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (projection) {
      glOrtho(-1, 1, -1, 1, 1, 1000);
      glTranslatef(0, 0, -2.5);
    } else {
      glFrustum(-1, 1, -1, 1, 1, 1000);
      glTranslatef(0, 0, -2.5);
    }
    translation(&surface, axis_translated, &axis_prev);
    rotation(&surface, axis_rotated, &axis_rotated_prev);
    // glRotated(xRot_mo, 1, 0, 0);
    // glRotated(yRot_mo, 0, 1, 0);
    glPointSize(static_cast<GLfloat>(vertexSize));
    if (vertex_type) vertexDraw();
    linesDraw();
  }
}

// void glView::mousePressEvent(QMouseEvent *mo) { mousePosition = mo->pos(); }

// void glView::mouseMoveEvent(QMouseEvent *mo) {
//   xRot_mo = 1 / M_PI * (mo->pos().y() - mousePosition.y());
//   yRot_mo = 1 / M_PI * (mo->pos().x() - mousePosition.x());
//   update();
// }

void glView::vertexDraw() {
  glEnable(static_cast<GLenum>(vertex_type));
  glBegin(GL_POINTS);
  glColor3f(static_cast<GLfloat>(vertex_color.redF()),
            static_cast<GLfloat>(vertex_color.greenF()),
            static_cast<GLfloat>(vertex_color.blueF()));
  for (int i = 0; i < surface.amount_of_points; i++) {
    glVertex3d(surface.one_point[i]->x, surface.one_point[i]->y,
               surface.one_point[i]->z);
  }
  glEnd();
}
void glView::linesDraw() {
  if (lineType == 0) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0);
  }
  glLineWidth(static_cast<GLfloat>(lineWidth));
  glBegin(GL_LINES);
  glColor3f(static_cast<GLfloat>(edge_color.redF()),
            static_cast<GLfloat>(edge_color.greenF()),
            static_cast<GLfloat>(edge_color.blueF()));
  for (int i = 0; i < mesh.amount_of_faces; i++) {
    for (int j = 0; j < 3; j++) {
      int v1 = mesh.one_face[i]->v[j] - 1;  // Номер первой вершины
      int v2 = mesh.one_face[i]->v[(j + 1) % 3] - 1;  // Номер второй вершины
      glVertex3d(surface.one_point[v1]->x, surface.one_point[v1]->y,
                 surface.one_point[v1]->z);
      glVertex3d(surface.one_point[v2]->x, surface.one_point[v2]->y,
                 surface.one_point[v2]->z);
    }
  }

  glEnd();
  if (lineType == 0) {
    glDisable(GL_LINE_STIPPLE);
  }
}
