#-------------------------------------------------
#
# Project created by QtCreator 2021-07-14T17:07:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Login
TEMPLATE = app


SOURCES += main.cpp\
    databasedata.cpp \
    mainwindow.cpp \
    toregister.cpp \
    info.cpp \
    carregister.cpp \
    appointment.cpp \
    appinfo.cpp \
    accepted.cpp \
    oncar.cpp \
    instantcall.cpp \
    pay.cpp \
    evaluation.cpp

HEADERS  += \
    telecheck.h \
    carcheck.h \
    databasedata.h \
    carcheck.h \
    mainwindow.h \
    toregister.h \
    info.h \
    carregister.h \
    appointment.h \
    appinfo.h \
    accepted.h \
    oncar.h \
    instantcall.h \
    pay.h \
    evaluation.h

FORMS    += \
    mainwindow.ui \
    toregister.ui \
    info.ui \
    carregister.ui \
    appointment.ui \
    appinfo.ui \
    accepted.ui \
    oncar.ui \
    instantcall.ui \
    pay.ui \
    evaluation.ui

RESOURCES += \
    images.qrc \
    place.qrc
