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
    texttemplateelementswidget.cxx \
    templateelementwidget.cxx \
    lineedittemplateelementwidget.cxx \
    textedittemplateelementwidget.cxx \
    radiobuttontemplateelementwidget.cxx \
    checkboxtemplateelementwidget.cxx \
    dateedittemplateelementwidget.cxx

HEADERS  += \
    mainwindow.hxx \
    letterassistant.hxx \
    aboutprogramdialog.hxx \
    config.hxx \
    letterbuilderdialog.hxx \
    texttemplate.hxx \
    templateelement.hxx \
    texttemplateelementswidget.hxx \
    templateelementwidget.hxx \
    lineedittemplateelementwidget.hxx \
    textedittemplateelementwidget.hxx \
    radiobuttontemplateelementwidget.hxx \
    checkboxtemplateelementwidget.hxx \
    dateedittemplateelementwidget.hxx

FORMS += \
    aboutprogramdialog.ui
