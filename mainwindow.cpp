
#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionFile_triggered() {
  QString fileDialog = QFileDialog::getOpenFileName(
      this, QDir::homePath(), tr("Object Files (*.obj);;All Files (*)"),
      tr("Object Files (*.obj)"));
  if (fileDialog != "") ui->label_10->setText(QFileInfo(fileDialog).fileName());
  ui->openGLWidget->parcer(fileDialog);
  ui->label_13->setText(QString::number(ui->openGLWidget->size_v / 3));
  ui->label_14->setText(QString::number(ui->openGLWidget->size_f / 2));
}

void MainWindow::on_pushButton_clicked() {
  ui->openGLWidget->centerFigure();
  ui->doubleSpinBox->setValue(0.0);
  ui->doubleSpinBox_2->setValue(0.0);
  ui->doubleSpinBox_3->setValue(0.0);
  ui->doubleSpinBox_4->setValue(0.0);
  ui->doubleSpinBox_5->setValue(0.0);
  ui->doubleSpinBox_6->setValue(0.0);
  ui->doubleSpinBox_7->setValue(0.0);
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1) {
  ui->openGLWidget->move(ui->doubleSpinBox->value(),
                         ui->doubleSpinBox_2->value(),
                         ui->doubleSpinBox_3->value());
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1) {
  ui->openGLWidget->move(ui->doubleSpinBox->value(),
                         ui->doubleSpinBox_2->value(),
                         ui->doubleSpinBox_3->value());
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1) {
  ui->openGLWidget->move(ui->doubleSpinBox->value(),
                         ui->doubleSpinBox_2->value(),
                         ui->doubleSpinBox_3->value());
}

void MainWindow::on_doubleSpinBox_4_valueChanged(double arg1) {
  ui->openGLWidget->rotateOx(ui->doubleSpinBox_4->value());
}

void MainWindow::on_doubleSpinBox_5_valueChanged(double arg1) {
  ui->openGLWidget->rotateOy(ui->doubleSpinBox_5->value());
}

void MainWindow::on_doubleSpinBox_6_valueChanged(double arg1) {
  ui->openGLWidget->rotateOz(ui->doubleSpinBox_6->value());
}

void MainWindow::on_doubleSpinBox_7_valueChanged(double arg1) {
  ui->openGLWidget->scaleXYZ(ui->doubleSpinBox_7->value());
}

void MainWindow::on_radioButton_toggled(bool checked) {
  if (checked) {
    ui->radioButton_2->setChecked(0);
    ui->openGLWidget->projection(1);
  }
}

void MainWindow::on_radioButton_2_toggled(bool checked) {
  if (checked) {
    ui->radioButton->setChecked(0);
    ui->openGLWidget->projection(0);
  }
}

void MainWindow::on_radioButton_3_clicked() {
  if (ui->radioButton_3->isChecked()) {
    ui->radioButton_4->setChecked(0);
    ui->radioButton_5->setChecked(0);
    ui->openGLWidget->line_type(0);
  }
}

void MainWindow::on_radioButton_4_clicked() {
  if (ui->radioButton_4->isChecked()) {
    ui->radioButton_3->setChecked(0);
    ui->radioButton_5->setChecked(0);
    ui->openGLWidget->line_type(1);
  }
}

void MainWindow::on_radioButton_5_clicked() {
  if (ui->radioButton_5->isChecked()) {
    ui->radioButton_3->setChecked(0);
    ui->radioButton_4->setChecked(0);
    ui->openGLWidget->line_type(2);
  }
}

void MainWindow::on_pushButton_2_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorLine(color);
}

void MainWindow::on_doubleSpinBox_8_valueChanged(double arg1) {
  ui->openGLWidget->line_width(arg1);
}

void MainWindow::on_doubleSpinBox_9_valueChanged(double arg1) {
  ui->openGLWidget->point_size(arg1);
}

void MainWindow::on_radioButton_6_clicked() {
  if (ui->radioButton_6->isChecked()) {
    ui->radioButton_7->setChecked(0);
    ui->radioButton_8->setChecked(0);
    ui->openGLWidget->point_type(0);
  }
}

void MainWindow::on_radioButton_7_clicked() {
  if (ui->radioButton_7->isChecked()) {
    ui->radioButton_6->setChecked(0);
    ui->radioButton_8->setChecked(0);
    ui->openGLWidget->point_type(1);
  }
}

void MainWindow::on_radioButton_8_clicked() {
  if (ui->radioButton_8->isChecked()) {
    ui->radioButton_6->setChecked(0);
    ui->radioButton_7->setChecked(0);
    ui->openGLWidget->point_type(2);
  }
}

void MainWindow::on_pushButton_3_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorPoint(color);
}

void MainWindow::on_pushButton_4_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) ui->openGLWidget->colorBackground(color);
}

void MainWindow::on_pushButton_6_clicked() { ui->openGLWidget->saveSetting(); }

void MainWindow::on_pushButton_7_clicked() {
  ui->openGLWidget->loadSetting();
  ui->doubleSpinBox_8->setValue(ui->openGLWidget->size_line);
  ui->doubleSpinBox_9->setValue(ui->openGLWidget->size_point);
  if (!ui->openGLWidget->radio) {
    ui->radioButton->setChecked(0);
    ui->radioButton_2->setChecked(1);
  } else if (ui->openGLWidget->radio) {
    ui->radioButton->setChecked(1);
    ui->radioButton_2->setChecked(0);
  }

  if (ui->openGLWidget->stipple == 0) {
    ui->radioButton_3->setChecked(1);
    ui->radioButton_4->setChecked(0);
    ui->radioButton_5->setChecked(0);
  } else if (ui->openGLWidget->stipple == 1) {
    ui->radioButton_3->setChecked(0);
    ui->radioButton_4->setChecked(1);
    ui->radioButton_5->setChecked(0);
  } else if (ui->openGLWidget->stipple == 2) {
    ui->radioButton_3->setChecked(0);
    ui->radioButton_4->setChecked(0);
    ui->radioButton_5->setChecked(1);
  }

  if (ui->openGLWidget->square == 0) {
    ui->radioButton_6->setChecked(1);
    ui->radioButton_7->setChecked(0);
    ui->radioButton_8->setChecked(0);
  } else if (ui->openGLWidget->square == 1) {
    ui->radioButton_6->setChecked(0);
    ui->radioButton_7->setChecked(1);
    ui->radioButton_8->setChecked(0);
  } else if (ui->openGLWidget->square == 2) {
    ui->radioButton_6->setChecked(0);
    ui->radioButton_7->setChecked(0);
    ui->radioButton_8->setChecked(1);
  }
}

void MainWindow::on_screenshot_clicked() {
  QString exePath = QCoreApplication::applicationDirPath();
  QDir dir(exePath);
  QString screenshotName = "../../../screen/screenshot";
  screenshotName +=
      QDateTime::currentDateTime().toString("dd.MM.yyyy_HH:mm:ss");
  if (ui->radioButton_bmp->isChecked()) {
    screenshotName += ".bmp";
  } else if (ui->radioButton_jpeg->isChecked()) {
    screenshotName += ".jpeg";
  }
  ui->openGLWidget->grab().save(dir.filePath(screenshotName));
}

void MainWindow::on_gif_screencast_clicked() {
  std::thread cast_gif(&MyGLWidget::gifScreencast, ui->openGLWidget);
  cast_gif.detach();
}

void MainWindow::on_radioButton_bmp_clicked() {
  if (ui->radioButton_bmp->isChecked()) ui->radioButton_jpeg->setChecked(0);
}

void MainWindow::on_radioButton_jpeg_clicked() {
  if (ui->radioButton_jpeg->isChecked()) ui->radioButton_bmp->setChecked(0);
}
