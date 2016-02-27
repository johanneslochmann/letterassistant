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
