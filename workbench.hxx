#pragma once

#include <QMdiArea>

class XMLTemplate;

class Workbench : public QMdiArea
{
    Q_OBJECT
public:
    Workbench(QWidget* p);
    virtual ~Workbench();

public slots:
    void onXMLTemplateLoaded(XMLTemplate* t);

protected:
    void connectToApplicationSignals();
};
