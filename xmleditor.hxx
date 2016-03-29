#pragma once

#include <QTextEdit>

class XMLTemplate;

class XMLEditor : public QTextEdit
{
    Q_OBJECT
public:
    XMLEditor(QWidget* p);
    virtual ~XMLEditor();

public slots:
    void setXMLTemplate(XMLTemplate* t);

private:
    XMLTemplate* m_t { nullptr };
};
