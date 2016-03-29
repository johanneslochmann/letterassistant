#pragma once

#include <QMdiArea>

class Workbench : public QMdiArea
{
    Q_OBJECT
public:
    Workbench(QWidget* p);
    virtual ~Workbench();

protected:
    void connectToApplicationSignals();
};
