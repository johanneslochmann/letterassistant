/*
 * (c) 2016  Johannes Lochmann
 * Email:    jolo@johanneslochmann.net
 * Website:  http://www.johanneslochmann.net/letterassistant
 *
 * This file is part of LetterAssistant.
 *
 * LetterAssistant is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LetterAssistant is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LetterAssistant.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.hxx"

#include <QMenuBar>
#include <QMenu>

#include "workbench.hxx"
#include "letterassistant.hxx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*m_wb = new Workbench(this);
    setCentralWidget(m_wb);
*/
    createMenuBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createFileMenu()
{
    m_file = new QMenu(trUtf8("&File"), menuBar());

    m_file->addAction(LetterAssistant::get()->quitAction());

    menuBar()->addMenu(m_file);
}

void MainWindow::createLetterMenu()
{
    m_letter = new QMenu(trUtf8("&Letter"), menuBar());

    m_letter->addAction(LetterAssistant::get()->createLetterAction());

    menuBar()->addMenu(m_letter);
}

void MainWindow::createTemplatesMenu()
{
    m_templates = new QMenu(trUtf8("&Templates"), menuBar());

    m_templates->addAction(LetterAssistant::get()->createTemplateAction());
    m_templates->addAction(LetterAssistant::get()->openTemplateAction());
    m_templates->addSeparator();
    m_templates->addAction(LetterAssistant::get()->saveTemplateAction());
    m_templates->addAction(LetterAssistant::get()->saveTemplateAsAction());
    m_templates->addSeparator();
    m_templates->addAction(LetterAssistant::get()->closeTemplateAction());

    menuBar()->addMenu(m_templates);
}

void MainWindow::createHelpMenu()
{
    m_help = new QMenu(trUtf8("&Help"), menuBar());

    m_help->addAction(LetterAssistant::get()->aboutProgramAction());
    m_help->addSeparator();
    m_help->addAction(LetterAssistant::get()->aboutQtAction());

    menuBar()->addSeparator();
    menuBar()->addMenu(m_help);
}

void MainWindow::createMenuBar()
{
    createFileMenu();
    createLetterMenu();
    createTemplatesMenu();
    createHelpMenu();
}
