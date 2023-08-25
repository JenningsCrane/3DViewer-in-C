#include "myglwidget.h"

void MyGLWidget::AutosaveWriting(autosave save) {
  QString exePath = QCoreApplication::applicationDirPath();
  QDir dir(exePath);
  QString fileName = dir.filePath("../../../settings.txt");
  std::ofstream inputfile(fileName.toStdString(), std::ios::out);
  inputfile.is_open();
  inputfile << "r " << save.radio << "\nst " << save.stipple << "\nsq "
            << save.square;
  inputfile << "\nSL " << save.size_line << "\nSP " << save.size_point << "\n";
  inputfile << "L " << save.rL << " " << save.gL << " " << save.bL << "\n";
  inputfile << "P " << save.rP << " " << save.gP << " " << save.bP << "\n";
  inputfile << "B " << save.rB << " " << save.gB << " " << save.bB << "\n";
  inputfile.close();
}

void MyGLWidget::AutoSaveReading(autosave *save) {
  QString exePath = QCoreApplication::applicationDirPath();
  QDir dir(exePath);
  QString fileName = dir.filePath("../../../settings.txt");
  std::ifstream outfile(fileName.toStdString());
  if (outfile.is_open()) {
    std::string line;
    while (getline(outfile, line)) {
      std::stringstream ss(line);
      ss >> line;
      if (line == "r ") {
        ss >> save->radio;
      } else if (line == "st") {
        ss >> save->stipple;
      } else if (line == "sq") {
        ss >> save->square;
      } else if (line == "SL") {
        ss >> save->size_line;
      } else if (line == "SP") {
        ss >> save->size_point;
      } else if (line == "L") {
        ss >> save->rL >> save->gL >> save->bL;
      } else if (line == "P") {
        ss >> save->rP >> save->gP >> save->bP;
      } else if (line == "B") {
        ss >> save->rB >> save->gB >> save->bB;
      }
    }
    outfile.close();
  }
}
