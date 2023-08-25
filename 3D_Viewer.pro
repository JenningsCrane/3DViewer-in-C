QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# LIBS += -lopengl32 -lglu32 -lgdi32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../src/


SOURCES += \
    ../src/FilesOnC/affine_trans.c \
    ../src/FilesOnC/parser.c \
    ../src/autosave.cpp \
    ../src/gif.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp \
    ../src/myglwidget.cpp

HEADERS += \
    ../src/FilesOnC/parser.h \
    ../src/gif.hpp \
    ../src/mainwindow.h \
    ../src/myglwidget.h

FORMS += \
    ../src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
