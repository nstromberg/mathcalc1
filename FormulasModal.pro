QT += sql
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
//Qt += sql
QT += printsupport
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    VehicleLookUp.cpp \
    centerofmasssolutions.cpp \
    databaseconnection.cpp \
    formulaLayout.cpp \
    main.cpp \
    formulas.cpp \
    minimumSpeed.cpp \
    unittests.cpp \
    vehicleweights.cpp

HEADERS += \
    VehicleLookUp.h \
    centerofmasssolutions.h \
    databaseconnection.h \
    formulaLayout.h \
    formulas.h \
    main.h \
    minimumSpeed.h \
    unittests.h \
    vehicleweights.h

FORMS += \
    VehicleLookUp.ui \
    centerOfMassSolutions.ui \
    formulaLayout.ui \
    formulas.ui \
    minimumSpeed.ui \
    vehicleweights.ui

# Specify build directory
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
