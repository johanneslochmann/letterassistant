#include "workbench.hxx"

#include <letterassistant.hxx>

Workbench::Workbench(QWidget *p)
    : QMdiArea(p)
{    
    connectToApplicationSignals();
}

Workbench::~Workbench()
{
}

void Workbench::connectToApplicationSignals()
{
    auto app = LetterAssistant::get();

    connect(app, &LetterAssistant::activateNextSubWindow, this, &Workbench::activateNextSubWindow);
    connect(app, &LetterAssistant::activatePreviousSubWindow, this, &Workbench::activatePreviousSubWindow);
    connect(app, &LetterAssistant::cascadeSubWindows, this, &Workbench::cascadeSubWindows);
    connect(app, &LetterAssistant::closeActiveSubWindow, this, &Workbench::closeActiveSubWindow);
    connect(app, &LetterAssistant::closeAllSubWindows, this, &Workbench::closeAllSubWindows);
    connect(app, &LetterAssistant::tileSubWindows, this, &Workbench::tileSubWindows);
}
