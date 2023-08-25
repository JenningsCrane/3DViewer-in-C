#include "myglwidget.h"

#include <chrono>
#include <cstdint>
#include <thread>

#include "gif.hpp"

MyGLWidget::MyGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  v = nullptr, f = nullptr;
  num_last_x_move = 0.0, num_last_y_move = 0.0, num_last_z_move = 0.0;
  num_last_x_rot = 0.0, num_last_y_rot = 0.0, num_last_z_rot = 0.0;
  num_last_scale = 0.0;
  max_x = 1.0, min_x = -1.0, max_y = 1.0, min_y = -1.0, max_z = 1.0,
  min_z = -1.0;
  radio = 1;
  stipple = 0, square = 0;
  size_line = 1.0, size_point = 0.0;
  rL = 1, gL = 1, bL = 1;
  rP = 1, gP = 1, bP = 1;
  rB = 0, gB = 0, bB = 0;
  xRot = 0;
  yRot = 0;
  zRot = 0;
  err = 0;
  save = {0};
  setMouseTracking(true);
}

MyGLWidget::~MyGLWidget() {
  if (v) free(v);
  if (f) free(f);
}

void MyGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void MyGLWidget::resizeGL(int w, int h) {
  glwidth = w;
  glheight = h;
  glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(rB, gB, bB, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (radio)
    projectionCenter();
  else
    projectionParallel();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(xRot, 1.0, 0.0, 0.0);
  glRotatef(yRot, 0.0, 1.0, 0.0);
  glRotatef(zRot, 0.0, 0.0, 1.0);
  paintFigure();
  glReadPixels(glwidth / 2, glheight / 2, glwidth, glheight, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
}

void MyGLWidget::gifScreencast() {
  QString exePath = QCoreApplication::applicationDirPath();
  QDir dir(exePath);
  auto fileName = "../../../screen/gif_image.gif";
  int delay = 100;
  GifWriter g;
  GifBegin(&g, dir.filePath(fileName).toStdString().c_str(), glwidth, glheight,
           delay);
  for (int timer = 0; timer <= 5000; timer += delay) {
    GifWriteFrame(&g, image, glwidth, glheight, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
  GifEnd(&g);
}

void MyGLWidget::paintFigure() {
  if (v && f) {
    style();
    glVertexPointer(3, GL_FLOAT, 0, v);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(rL, gL, bL);
    if (stipple != 2) glDrawElements(GL_LINES, size_f, GL_UNSIGNED_INT, f);
    glColor3f(rP, gP, bP);
    if (square != 2) glDrawArrays(GL_POINTS, 0, size_v / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void MyGLWidget::parcer(QString fileName) {
  QByteArray arr = fileName.toUtf8();
  arr.append('\0');
  err = open_file(arr.data(), &v, &f, &size_v, &size_f);
  if ((!v || !f) && fileName != "")
    QMessageBox::critical(this, tr("Ошибка"),
                          tr("Не удалось открыть файл").arg(fileName));
}

void MyGLWidget::mousePressEvent(QMouseEvent* mo) { isClicking = true; }

void MyGLWidget::mouseReleaseEvent(QMouseEvent* mo) { isClicking = false; }

void MyGLWidget::mouseMoveEvent(QMouseEvent* mo) {
  mDelta = mo->pos() - mPos;
  mPos = mo->pos();
  if (isClicking) {
    xRot += 1 / M_PI * mDelta.y();
    yRot += 1 / M_PI * mDelta.x();
  }
  update();
  mDelta = QPoint();
}

/*--- Аффинные преобразования ---*/

/* Перемещение */
void MyGLWidget::move(float num_x, float num_y, float num_z) {
  if (v && f)
    translate(num_x, &num_last_x_move, num_y, &num_last_y_move, num_z,
              &num_last_z_move, size_v, v);
  update();
}

/* Вращение по X */
void MyGLWidget::rotateOx(float num) {
  if (v && f) rotationOx(num, &num_last_x_rot, size_v, v);
  update();
}

/* Вращение по Y */
void MyGLWidget::rotateOy(float num) {
  if (v && f) rotationOy(num, &num_last_y_rot, size_v, v);
  update();
}

/* Вращение по Z */
void MyGLWidget::rotateOz(float num) {
  if (v && f) rotationOz(num, &num_last_z_rot, size_v, v);
  update();
}

/* Скейл */
void MyGLWidget::scaleXYZ(float num) {
  if (v && f) scale(num, &num_last_scale, size_v, v);
  update();
}

/* Центрирование фигуры*/
void MyGLWidget::centerFigure() {
  if (v && f) {
    center(size_v, v, &max_x, &min_x, &max_y, &min_y, &max_z, &min_z);
    reduction();
  }
  update();
}

/* Уменьшение фигуры */
void MyGLWidget::reduction() {
  if (v && f)
    objectReduct(size_v, v, &max_x, &min_x, &max_y, &min_y, &max_z, &min_z);
}

/*--- Проекция ---*/

/* Центральная проекция */
void MyGLWidget::projectionCenter() {
  if (v && f) {
    float fov = 30.0 * M_PI / 180;
    float heapHeight = max_y / (2 * tan(fov / 2));
    glFrustum(min_x, max_x, min_y, max_y, heapHeight, max_z * 100);
    glTranslatef(0, 0, -heapHeight * 3);
  }
  update();
}

/* Параллельная проекция */
void MyGLWidget::projectionParallel() {
  if (v && f) {
    glOrtho(min_x * 1.5f, max_x * 1.5f, min_y * 1.5f, max_y * 1.5f,
            min_z * 3.5f, max_z * 3.5f);
    glTranslatef(0, 0, -0.5);
  }
  update();
}

/* Значения кнопок */
void MyGLWidget::projection(bool checked) { radio = checked; }

void MyGLWidget::line_type(int check_line) { stipple = check_line; }

void MyGLWidget::line_width(double size) { size_line = size; }

void MyGLWidget::point_type(int check_point) { square = check_point; }

void MyGLWidget::point_size(double size) { size_point = size; }

void MyGLWidget::colorLine(QColor color) {
  rL = color.redF();
  gL = color.greenF();
  bL = color.blueF();
  update();
}

void MyGLWidget::colorPoint(QColor color) {
  rP = color.redF();
  gP = color.greenF();
  bP = color.blueF();
  update();
}

void MyGLWidget::colorBackground(QColor color) {
  rB = color.redF();
  gB = color.greenF();
  bB = color.blueF();
  update();
}

/*--- Cтили ---*/
void MyGLWidget::style() {
  if (stipple == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 10);
  } else if (!stipple)
    glDisable(GL_LINE_STIPPLE);

  if (square == 1)
    glEnable(GL_POINT_SMOOTH);
  else if (!square)
    glDisable(GL_POINT_SMOOTH);

  glLineWidth(size_line);
  glPointSize(size_point);
}

void MyGLWidget::saveSetting() {
  save.rB = rB;
  save.gB = gB;
  save.bB = bB;
  save.rL = rL;
  save.gL = gL;
  save.bL = bL;
  save.rP = rP;
  save.gP = gP;
  save.bP = bP;
  save.radio = radio;
  save.size_line = size_line;
  save.size_point = size_point;
  save.square = square;
  save.stipple = stipple;
  AutosaveWriting(save);
}

void MyGLWidget::loadSetting() {
  AutoSaveReading(&save);
  rB = save.rB;
  gB = save.gB;
  bB = save.bB;
  rL = save.rL;
  gL = save.gL;
  bL = save.bL;
  rP = save.rP;
  gP = save.gP;
  bP = save.bP;
  radio = save.radio;
  size_line = save.size_line;
  size_point = save.size_point;
  square = save.square;
  stipple = save.stipple;
}
