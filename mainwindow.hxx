#pragma once

#include <QMainWindow>

class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createMenuBar();

    QMenu* m_file;
    QMenu* m_help;
};
