#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

// #include <GL/gl.h>
// #include <GL/glu.h>

#include <QApplication>
#include <QColorDialog>
#include <QDebug>
#include <QDockWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QWidget>
#include <QtOpenGL>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

extern "C" {
#include "FilesOnC/parser.h"
}

typedef struct autosave {
  bool radio;
  int stipple, square, size_line, size_point;
  float rL, gL, bL;
  float rP, gP, bP;
  float rB, gB, bB;
} autosave;

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit MyGLWidget(QWidget *parent = nullptr);
  ~MyGLWidget();

  int size_v, size_f;
  bool isClicking, radio;
  int stipple, square;
  float size_line, size_point;
  autosave save;

  void parcer(QString fileName);
  void move(float num_x, float num_y, float num_z);
  void rotateOx(float num);
  void rotateOy(float num);
  void rotateOz(float num);
  void projection(bool checked);
  void scaleXYZ(float num);
  void centerFigure();
  void reduction();
  void line_type(int check_line);
  void projectionParallel();
  void projectionCenter();
  void line_width(double size);
  void point_type(int check_point);
  void point_size(double size);
  void colorLine(QColor color);
  void colorPoint(QColor color);
  void colorBackground(QColor color);
  void saveSetting();
  void loadSetting();
  void gifScreencast();
  void AutosaveWriting(autosave save);
  void AutoSaveReading(autosave *save);

 private slots:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void paintFigure();
  void style();

 private:
  GLfloat *v;
  GLuint *f;
  float xRot, yRot, zRot;
  const char *name_file;
  float num_last_x_move, num_last_y_move, num_last_z_move;
  float num_last_x_rot, num_last_y_rot, num_last_z_rot;
  float num_last_scale;
  float max_x, min_x, max_y, min_y, max_z, min_z;
  GLfloat rL, gL, bL;
  GLfloat rP, gP, bP;
  GLfloat rB, gB, bB;
  QPoint mPos, mDelta;
  int glwidth, glheight, err;
  uint8_t image[800 * 800 * 4];
};

#endif  // MYGLWIDGET_H
