QT += core gui widgets

QMAKE_CXX = clang++
CONFIG += c++11

TARGET = letterassistant
TEMPLATE = app

SOURCES += \
    main.cxx\
    mainwindow.cxx \
    letterassistant.cxx \
    aboutprogramdialog.cxx \
    letterbuilderdialog.cxx \
    texttemplate.cxx \
    templateelement.cxx \
    texttemplateelementswidget.cxx

HEADERS  += \
    mainwindow.hxx \
    letterassistant.hxx \
    aboutprogramdialog.hxx \
    config.hxx \
    letterbuilderdialog.hxx \
    texttemplate.hxx \
    templateelement.hxx \
    texttemplateelementswidget.hxx

FORMS += \
    aboutprogramdialog.ui
