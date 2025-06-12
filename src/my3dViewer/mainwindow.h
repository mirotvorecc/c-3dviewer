#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QBuffer>
#include <QCloseEvent>
#include <QElapsedTimer>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QSettings>
#include <QTimer>

#include "glview.h"
#include "ima/qgifimage_p.h"
#include "iostream"

extern "C" {
#include "parser.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  QString modelFilePath;
  // QString crashedFilePath;
  QGifImage readyGif;
  bool needFree = false;
  QTimer *timer;
  QList<QImage> frames;
  bool recording = false;

  QList<QImage> gif;
  QElapsedTimer elapsedTimer;
  int currentFrameIndex = 0;
  explicit MainWindow(QWidget *parent = nullptr);
  // // restoreState(const QByteArray &state, int version = 0)
  // saveState(int version = 0) const;
  // restoreState(const QByteArray &state, 0);
  ~MainWindow();
 private slots:
  void on_pushButton_choose_file_clicked();

  void on_pushButton_vertex_color_clicked();

  void on_pushButton_background_color_clicked();

  void on_doubleSpinBox_xTrans_valueChanged(double arg1);

  void on_doubleSpinBox_yTrans_valueChanged(double arg1);

  void on_doubleSpinBox_zTrans_valueChanged(double arg1);

  void on_doubleSpinBox_xDegree_valueChanged(double arg1);

  void on_doubleSpinBox_yDegree_valueChanged(double arg1);

  void on_doubleSpinBox_zDegree_valueChanged(double arg1);

  void on_pushButton_makeGIF_clicked();

  void captureFrame();

  void on_radioButton_parallel_clicked();

  void on_radioButton_central_clicked();

  void on_radioButton_solid_clicked();

  void on_radioButton_dotted_clicked();

  void on_doubleSpinBox_vertexSize_valueChanged(double arg1);

  void on_doubleSpinBox_lineWidth_valueChanged(double arg1);

  void on_pushButton_edge_color_clicked();

  void on_comboBox_vertexMapping_currentIndexChanged(int index);

  // void on_horizontalSlider_scale_valueChanged(int value);
  void on_doubleSpinBox_scale_valueChanged(double scale);

  void on_pushButton_saveImage_clicked();

 private:
  Ui::MainWindow *ui;

 protected:
  void loadModel(const QString &filePath);
  void SetDefaultSettings();
};

#endif  // MAINWINDOW_H
