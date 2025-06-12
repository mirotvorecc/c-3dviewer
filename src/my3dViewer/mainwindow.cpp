#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->radioButton_parallel->setChecked(true);
  // ui->radioButton_solid->setChecked(true);
  // ui->doubleSpinBox_vertexSize->setEnabled(false);
  // NEW
  QSettings settings("School_21", "my3dViewerCFG");

  ui->doubleSpinBox_scale->setValue(
      (settings.value("doubleSpinBox_scale", 1).toDouble()));
  ui->doubleSpinBox_xTrans->setValue(
      (settings.value("doubleSpinBox_xTrans", 0).toDouble()));
  ui->doubleSpinBox_yTrans->setValue(
      (settings.value("doubleSpinBox_yTrans", 0).toDouble()));
  ui->doubleSpinBox_zTrans->setValue(
      (settings.value("doubleSpinBox_zTrans", 0).toDouble()));
  ui->doubleSpinBox_xDegree->setValue(
      (settings.value("doubleSpinBox_xDegree", 0).toDouble()));
  ui->doubleSpinBox_yDegree->setValue(
      (settings.value("doubleSpinBox_yDegree", 0).toDouble()));
  ui->doubleSpinBox_zDegree->setValue(
      (settings.value("doubleSpinBox_zDegree", 0).toDouble()));

  // ui->horizontalSlider_scale->setValue(ui->widget_qlView->scale);
  ui->comboBox_vertexMapping->setCurrentIndex(
      settings.value("vertex_mapping_index", 0).toDouble());
  ui->widget_qlView->axis_translated.scale =
      settings.value("axis_translated_scale", 1).toDouble();
  ui->doubleSpinBox_scale->setValue(ui->widget_qlView->axis_translated.scale);
  ui->widget_qlView->axis_translated.x =
      settings.value("axis_translated_x", 0).toDouble();
  ui->doubleSpinBox_xTrans->setValue(ui->widget_qlView->axis_translated.x);
  ui->widget_qlView->axis_translated.y =
      settings.value("axis_translated_y", 0).toDouble();
  ui->doubleSpinBox_yTrans->setValue(ui->widget_qlView->axis_translated.y);
  ui->widget_qlView->axis_translated.z =
      settings.value("axis_translated_z", 0).toDouble();
  ui->doubleSpinBox_zTrans->setValue(ui->widget_qlView->axis_translated.z);
  ui->widget_qlView->xRot_mo =
      settings.value("xRot_mo", 0)
          .toDouble();  // можнно не сохранять ui так как это параметр для мышки

  ui->widget_qlView->yRot_mo =
      settings.value("yRot_mo", 0)
          .toDouble();  // можнно не сохранять ui так как это параметр для мышки

  ui->widget_qlView->vertex_color =
      settings.value("vertex_color", QColor(Qt::white)).value<QColor>();

  ui->widget_qlView->edge_color =
      settings.value("edge_color", QColor(Qt::red)).value<QColor>();

  ui->widget_qlView->background_color =
      settings.value("background_color", QColor(Qt::black)).value<QColor>();

  ui->widget_qlView->lineType = settings.value("lineType", 1).toInt();
  if (ui->widget_qlView->lineType == 1)
    ui->radioButton_solid->setChecked(true);
  else
    ui->radioButton_dotted->setChecked(true);
  ui->widget_qlView->vertex_type =
      settings.value("vertex_type", GL_POINT).toInt();
  if (ui->widget_qlView->vertex_type == 0)
    ui->doubleSpinBox_vertexSize->setEnabled(false);

  ui->widget_qlView->lineWidth = settings.value("lineWidth", 1).toFloat();
  ui->doubleSpinBox_lineWidth->setValue(ui->widget_qlView->lineWidth);
  ui->widget_qlView->vertexSize = settings.value("vertexSize", 1).toFloat();
  ui->doubleSpinBox_vertexSize->setValue(ui->widget_qlView->vertexSize);

  ui->radioButton_central->setChecked(
      settings.value("radioButton_central", 0).toBool());
  ui->radioButton_parallel->setChecked(
      settings.value("radioButton_parallel", 0).toBool());
  QString modelFilePath = settings.value("modelFilePath").toString();
  if (!modelFilePath.isEmpty()) {
    qDebug() << "Зашел сюда с путем: " << modelFilePath;
    loadModel(modelFilePath);  // функция для загрузки модели из файла
  }

  // END
}

MainWindow::~MainWindow() {
  // NEW
  QSettings settings("School_21", "my3dViewerCFG");
  QFile file(settings.fileName());
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Cannot write to settings file: " << file.errorString();
  }
  // settings.setValue("scale", ui->widget_qlView->scale);
  settings.setValue("axis_translated_scale",
                    ui->widget_qlView->axis_translated.scale);
  settings.setValue("axis_translated_x", ui->widget_qlView->axis_translated.x);
  settings.setValue("axis_translated_y", ui->widget_qlView->axis_translated.y);
  settings.setValue("axis_translated_z", ui->widget_qlView->axis_translated.z);

  settings.setValue("doubleSpinBox_scale", ui->doubleSpinBox_scale->value());
  settings.setValue("doubleSpinBox_xTrans", ui->doubleSpinBox_xTrans->value());
  settings.setValue("doubleSpinBox_yTrans", ui->doubleSpinBox_yTrans->value());
  settings.setValue("doubleSpinBox_zTrans", ui->doubleSpinBox_zTrans->value());
  settings.setValue("doubleSpinBox_xDegree",
                    ui->doubleSpinBox_xDegree->value());
  settings.setValue("doubleSpinBox_yDegree",
                    ui->doubleSpinBox_yDegree->value());
  settings.setValue("doubleSpinBox_zDegree",
                    ui->doubleSpinBox_zDegree->value());

  settings.setValue("radioButton_central",
                    ui->radioButton_central->isChecked());
  settings.setValue("radioButton_parallel",
                    ui->radioButton_parallel->isChecked());
  settings.setValue("xRot_mo", ui->widget_qlView->xRot_mo);
  settings.setValue("yRot_mo", ui->widget_qlView->yRot_mo);
  settings.setValue("vertex_color", ui->widget_qlView->vertex_color);
  settings.setValue("edge_color", ui->widget_qlView->edge_color);
  settings.setValue("background_color", ui->widget_qlView->background_color);
  settings.setValue("lineType", ui->widget_qlView->lineType);
  settings.setValue("vertex_type", ui->widget_qlView->vertex_type);
  settings.setValue("lineWidth", ui->widget_qlView->lineWidth);
  settings.setValue("vertexSize", ui->widget_qlView->vertexSize);
  settings.setValue("modelFilePath", modelFilePath);
  settings.setValue("vertex_mapping_index",
                    ui->comboBox_vertexMapping->currentIndex());
  qDebug() << "Settings are stored at: " << settings.fileName();

  // END
  delete ui;
}

void MainWindow::on_pushButton_choose_file_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, tr("Выберите объектный файл"), "", "*.obj", nullptr,
      QFileDialog::DontUseNativeDialog);
  ui->widget_qlView->isPaint = true;
  if (!filePath.isEmpty()) {
    if (!modelFilePath.isEmpty()) SetDefaultSettings();
    // SetDefaultSettings();
    loadModel(filePath);
  }
}

void MainWindow::SetDefaultSettings() {
  ui->widget_qlView->glFlush();
  ui->doubleSpinBox_scale->setValue(1.0);
  ui->doubleSpinBox_xTrans->setValue(0.0);
  ui->doubleSpinBox_yTrans->setValue(0.0);
  ui->doubleSpinBox_zTrans->setValue(0.0);
  ui->doubleSpinBox_xDegree->setValue(0.0);
  ui->doubleSpinBox_yDegree->setValue(0.0);
  ui->doubleSpinBox_zDegree->setValue(0.0);
  ui->doubleSpinBox_lineWidth->setValue(1.0);

  ui->widget_qlView->axis_translated.scale = 1.0;
  ui->widget_qlView->axis_translated.x = 0.0;
  ui->widget_qlView->axis_translated.y = 0.0;
  ui->widget_qlView->axis_translated.z = 0.0;

  // ui->widget_qlView->xRot_mo = 0.0;
  // ui->widget_qlView->yRot_mo = 0.0;
  ui->widget_qlView->vertex_color = QColor(Qt::white);
  ui->widget_qlView->edge_color = QColor(Qt::white);
  ui->widget_qlView->background_color = QColor(Qt::black);
  ui->widget_qlView->lineType = 1;
  ui->widget_qlView->vertex_type = 1;
  ui->comboBox_vertexMapping->setCurrentIndex(0);
  ui->widget_qlView->lineWidth = 1;
  ui->widget_qlView->vertexSize = 1;
  ui->radioButton_parallel->setChecked(true);
  ui->radioButton_solid->setChecked(true);
  ui->doubleSpinBox_vertexSize->setEnabled(false);
  // ui->widget_qlView->update();
  ui->widget_qlView->repaint();
}

void MainWindow::loadModel(const QString &filePath) {
  ui->widget_qlView->isPaint = true;
  if (!filePath.isEmpty()) {
    if (needFree) {
      free_surface(&ui->widget_qlView->surface);
      free_mesh(&ui->widget_qlView->mesh);
    }
    ui->widget_qlView->projection = ui->radioButton_parallel->isChecked();
    ui->widget_qlView->lineType = ui->radioButton_solid->isChecked();
    needFree = true;
    QByteArray byteArray = filePath.toUtf8();
    const char *path = byteArray.constData();
    ui->widget_qlView->surface.amount_of_points = 0;
    ui->widget_qlView->mesh.amount_of_faces = 0;
    int status_flag = parse_obj_file(path, &ui->widget_qlView->surface,
                                     &ui->widget_qlView->mesh);
    if (status_flag == NOT_ERROR) {
      QString info = "INFO\nName of file: ";
      QFileInfo fileInfo(filePath);
      modelFilePath = filePath;
      QString fileName = fileInfo.fileName();
      info += fileName;
      info += "\nAmount of vertex: ";
      info += QString::number(ui->widget_qlView->surface.amount_of_points);
      info += "\nAmount of edges: ";
      info += QString::number(ui->widget_qlView->mesh.amount_of_faces);
      ui->label_Info->setText(info);
      ui->widget_qlView->update();
    } else if (status_flag == PARSER_ERROR) {
      // crashedFilePath = filePath;
      needFree = false;
      ui->widget_qlView->isPaint = false;
      QMessageBox::information(nullptr, "Ошибка",
                               "Разбор файла: Некорректный файл obj");

      if (!modelFilePath.isEmpty()) {
        loadModel(modelFilePath);
      } else {
        on_pushButton_choose_file_clicked();
      }
    } else if (status_flag == MEMORY_ERROR) {
      QMessageBox::information(nullptr, "Ошибка",
                               "Разбор файла: Выделение памяти");
      needFree = false;
    } else if (status_flag == OPEN_FILE_ERROR) {
      // QMessageBox::information(nullptr, "Ошибка", "Разбор файла: Чтение
      // файла");
      needFree = false;
    }
  }
}

void MainWindow::on_pushButton_vertex_color_clicked() {
  ui->widget_qlView->vertex_color =
      QColorDialog::getColor(Qt::black, this, tr("Select Color"));
}

void MainWindow::on_pushButton_background_color_clicked() {
  ui->widget_qlView->background_color =
      QColorDialog::getColor(Qt::black, this, tr("Select Color"));
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double scale) {
  if (scale <= 0.0) {
    scale = 0.0001;
  }
  ui->widget_qlView->axis_translated.scale = scale;
  ui->widget_qlView->update();
}

void MainWindow::on_doubleSpinBox_xTrans_valueChanged(double delta_x) {
  ui->widget_qlView->axis_translated.x = delta_x;
  ui->widget_qlView->update();
}

void MainWindow::on_doubleSpinBox_yTrans_valueChanged(double delta_y) {
  ui->widget_qlView->axis_translated.y = delta_y;
  ui->widget_qlView->update();
}

void MainWindow::on_doubleSpinBox_zTrans_valueChanged(double delta_z) {
  ui->widget_qlView->axis_translated.z = delta_z;
  ui->widget_qlView->update();
}

void MainWindow::on_doubleSpinBox_xDegree_valueChanged(double rot_delta_x) {
  ui->widget_qlView->axis_rotated.x = rot_delta_x * (M_PI / 180.0f);
  ui->widget_qlView->update();
}

void MainWindow::on_doubleSpinBox_yDegree_valueChanged(double rot_delta_y) {
  ui->widget_qlView->axis_rotated.y = rot_delta_y * (M_PI / 180.0f);
  ui->widget_qlView->update();
}

void MainWindow::on_doubleSpinBox_zDegree_valueChanged(double rot_delta_z) {
  ui->widget_qlView->axis_rotated.z = rot_delta_z * (M_PI / 180.0f);
  ui->widget_qlView->update();
}

void MainWindow::on_pushButton_makeGIF_clicked() {
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(captureFrame()));
  timer->start(100);  // Устанавливаем интервал таймера (в миллисекундах) для
                      // захвата кадров
  //            elapsedTimer.start();
  gif.clear();

  currentFrameIndex = 0;
}

void MainWindow::captureFrame() {
  // Если прошло менее 5 секунд, продолжаем создавать кадры и сохранять их
  if (gif.length() < 50) {
    QPixmap pixmap = centralWidget()->grab();
    // readyGif.addFrame(pixmap.toImage(), 100);

    gif.append(pixmap.toImage());
    std::cout << currentFrameIndex << std::endl;
    currentFrameIndex++;
  } else {
    timer->stop();
    // disconnect(timer);
    for (int i = 0; i < 50; readyGif.addFrame(gif[i++], 100)) {
    }
    QString filePath =
        QFileDialog::getSaveFileName(0, "Сохранить файл как", "", "*.gif");

    if (filePath != nullptr) {
      readyGif.save(filePath);
      std::cout << "GIF Image was saved" << std::endl;
    } else {
      std::cout << "Pathh wwasn not choosen" << std::endl;
    }
  }
}

void MainWindow::on_radioButton_parallel_clicked() {
  ui->widget_qlView->projection = ui->radioButton_parallel->isChecked();
  ui->widget_qlView->update();
}

void MainWindow::on_radioButton_central_clicked() {
  ui->widget_qlView->projection = ui->radioButton_parallel->isChecked();
  ui->widget_qlView->update();
}

void MainWindow::on_radioButton_solid_clicked() {
  ui->widget_qlView->lineType = ui->radioButton_solid->isChecked();
  ui->widget_qlView->update();
}

void MainWindow::on_radioButton_dotted_clicked() {
  ui->widget_qlView->lineType = ui->radioButton_solid->isChecked();
  ui->widget_qlView->update();
  // ui->widget_qlView->repaint();
}

void MainWindow::on_doubleSpinBox_vertexSize_valueChanged(double arg1) {
  ui->widget_qlView->vertexSize = arg1;
  ui->widget_qlView->update();
}

void MainWindow::on_doubleSpinBox_lineWidth_valueChanged(double arg1) {
  ui->widget_qlView->lineWidth = arg1;
  ui->widget_qlView->update();
}

void MainWindow::on_pushButton_edge_color_clicked() {
  ui->widget_qlView->edge_color =
      QColorDialog::getColor(Qt::black, this, tr("Select Color"));
}

void MainWindow::on_comboBox_vertexMapping_currentIndexChanged(int index) {
  switch (index) {
    case 0:
      ui->widget_qlView->vertex_type = 0;
      ui->doubleSpinBox_vertexSize->setEnabled(false);
      break;
    case 1:
      ui->widget_qlView->vertex_type = GL_POINT;
      ui->doubleSpinBox_vertexSize->setEnabled(true);
      break;
    case 2:
      ui->widget_qlView->vertex_type = GL_POINT_SMOOTH;
      ui->doubleSpinBox_vertexSize->setEnabled(true);
      break;
  }
  ui->widget_qlView->update();
}

void MainWindow::on_pushButton_saveImage_clicked() {
  QPixmap imageToSave = centralWidget()->grab();
  QImage image = imageToSave.toImage();

  QString imagePath = QFileDialog::getSaveFileName(
      this, tr("Save Image"), "", tr("JPEG (*.jpg *.jpeg);;BMP (*.bmp)"));

  if (imagePath.isEmpty()) return;

  qDebug() << "Путь к файлу сохранения изображения:" << imagePath;

  QString format = QFileInfo(imagePath).suffix().toLower();
  qDebug() << "Формат изображения:" << format;

  if (format != "jpg" && format != "jpeg" && format != "bmp") {
    qDebug() << "Неверный формат изображения";
    QMessageBox::information(
        nullptr, "Ошибка",
        "Можно сохранить изображение только в форматах JPEG и BMP");
    return;
  }

  QImageWriter writer(imagePath);
  if (!format.isEmpty()) writer.setFormat(format.toLatin1());

  if (!writer.canWrite()) {
    qDebug() << "Не удалось записать изображение";
    QMessageBox::information(nullptr, "Ошибка",
                             "Не удалось сохранить изображение\nПопробуйте "
                             "добавить в название файла его разрешение");
    return;
  }

  if (!writer.write(image)) {
    qDebug() << "Не удалось сохранить изображение";
    return;
  }

  QMessageBox::information(nullptr, "Успех", "Изображение успешно сохранено");
  qDebug() << "Изображение успешно сохранено";
}
