#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionFile_triggered();
  void on_pushButton_clicked();
  void on_doubleSpinBox_valueChanged(double arg1);
  void on_doubleSpinBox_2_valueChanged(double arg1);
  void on_doubleSpinBox_3_valueChanged(double arg1);
  void on_doubleSpinBox_4_valueChanged(double arg1);
  void on_doubleSpinBox_5_valueChanged(double arg1);
  void on_doubleSpinBox_6_valueChanged(double arg1);
  void on_doubleSpinBox_7_valueChanged(double arg1);
  void on_radioButton_toggled(bool checked);
  void on_radioButton_2_toggled(bool checked);
  void on_radioButton_3_clicked();
  void on_radioButton_4_clicked();
  void on_radioButton_5_clicked();
  void on_doubleSpinBox_8_valueChanged(double arg1);
  void on_doubleSpinBox_9_valueChanged(double arg1);
  void on_pushButton_2_clicked();
  void on_radioButton_6_clicked();
  void on_radioButton_7_clicked();
  void on_radioButton_8_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();

  void on_screenshot_clicked();

  void on_gif_screencast_clicked();

  void on_radioButton_bmp_clicked();

  void on_radioButton_jpeg_clicked();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
