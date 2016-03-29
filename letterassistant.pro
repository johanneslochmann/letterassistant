# (c) 2016  Johannes Lochmann
# Email:    jolo@johanneslochmann.net
# Website:  http://www.johanneslochmann.net/letterassistant
#
# This file is part of LetterAssistant.
#
# LetterAssistant is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# LetterAssistant is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with LetterAssistant.  If not, see <http://www.gnu.org/licenses/>.

QT += core gui widgets xml

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
    dateedittemplateelementwidget.cxx \
    templateelementvalue.cxx \
    texttemplateelement.cxx \
    datetemplateelement.cxx \
    optionstemplateelement.cxx \
    templateelementoption.cxx \
    optionswithtexttemplateelement.cxx \
    radiobuttonwithtexttemplateelementwidget.cxx \
    checkboxwithtexttemplateelementwidget.cxx \
    xmltemplate.cxx \
    workbench.cxx \
    xmltemplateeditor.cxx

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
    dateedittemplateelementwidget.hxx \
    templateelementvalue.hxx \
    texttemplateelement.hxx \
    datetemplateelement.hxx \
    optionstemplateelement.hxx \
    templateelementoption.hxx \
    optionswithtexttemplateelement.hxx \
    radiobuttonwithtexttemplateelementwidget.hxx \
    checkboxwithtexttemplateelementwidget.hxx \
    xmltemplate.hxx \
    workbench.hxx \
    xmltemplateeditor.hxx

FORMS += \
    aboutprogramdialog.ui

DISTFILES += \
    LICENSE \
    README.md \
    data/template.txt
