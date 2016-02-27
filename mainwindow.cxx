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

#include "letterassistant.hxx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenuBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenuBar()
{
    m_file = new QMenu(tr("&File"), menuBar());
    m_file->addAction(LetterAssistant::get()->createLetterAction());
    m_file->addSeparator();
    m_file->addAction(LetterAssistant::get()->quitAction());

    m_help = new QMenu(tr("&Help"), menuBar());
    m_help->addAction(LetterAssistant::get()->aboutProgramAction());
    m_help->addSeparator();
    m_help->addAction(LetterAssistant::get()->aboutQtAction());

    menuBar()->addMenu(m_file);
    menuBar()->addSeparator();
    menuBar()->addMenu(m_help);
}
