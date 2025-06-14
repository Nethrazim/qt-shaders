QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    shaderwidget.cpp

HEADERS += \
    mainwindow.h \
    shaderwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Shaders/rainbow_triangle_fragment_shader.shader \
    Shaders/rainbow_triangle_vertex_shader.shader

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug/
} else {
    DESTDIR = $$OUT_PWD/release/
}

SHADER_DIR = $$PWD/Shaders
QMAKE_POST_LINK += $$quote(xcopy /E /I /Y \""$$SHADER_DIR\"" \""$$DESTDIR\"")

