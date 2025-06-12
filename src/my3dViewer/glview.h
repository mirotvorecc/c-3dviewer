#ifndef GLVIEW_H
#define GLVIEW_H
#define GL_SILENCE_DEPRECATION
#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "iostream"

extern "C" {
#include "parser.h"
}
class glView : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  int vertex_type = GL_POINT;
  double lineWidth = 1.0;
  double vertexSize = 1.0;
  int lineType = 1;    //(1 - сплошная 0 - пунктирная)
  int projection = 1;  // тип проекции (1 - параллельная 0 центральная)
  Point axis_prev = {0, 0, 0, 1.0};
  Point axis_translated = {0, 0, 0, 1.0};
  Point axis_rotated_prev = {0, 0, 0, 1.0};
  Point axis_rotated = {0, 0, 0, 1.0};
  double xRot_mo = 0, yRot_mo;
  double xRot = 0, yRot = 0, zRot = 0;
  QPoint mousePosition;
  Surface surface;
  Mesh mesh;
  QColor background_color = QColor(Qt::black);
  QColor vertex_color = QColor(Qt::white);
  QColor edge_color = QColor(Qt::white);
  bool isPaint =
      false;  // переменная, которая отвечает за проверку необходимости отисовки
  glView(QWidget *parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  // void mousePressEvent(QMouseEvent *) override;
  // void mouseMoveEvent(QMouseEvent *) override;
  void linesDraw();
  void vertexDraw();
};

#endif  // GLVIEW_H
