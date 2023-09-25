QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core_ft60x_axi/sw/ftdi_axi_driver.cpp \
    core_ft60x_axi/sw/ftdi_ft60x.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    core_ft60x_axi/sw/d3xx-osx.1.0.14/ftd3xx.h \
    core_ft60x_axi/sw/ftdi_axi_driver.h \
    core_ft60x_axi/sw/ftdi_driver_api.h \
    core_ft60x_axi/sw/ftdi_ft60x.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    camera_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx: LIBS += -L$$PWD/core_ft60x_axi/sw/d3xx-osx.1.0.14/ -lftd3xx.1.0.14

INCLUDEPATH += $$PWD/core_ft60x_axi/sw/
INCLUDEPATH += $$PWD/core_ft60x_axi/sw/d3xx-osx.1.0.14
DEPENDPATH += $$PWD/core_ft60x_axi/sw/d3xx-osx.1.0.14
