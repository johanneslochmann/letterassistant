#pragma once

#include <QMdiSubWindow>

class XMLTemplate;
class XMLEditor;

class XMLTemplateEditor : public QMdiSubWindow
{
    Q_OBJECT
public:
    XMLTemplateEditor(QWidget* p);
    virtual ~XMLTemplateEditor();

    bool hasTemplate() const { return (nullptr != m_t); }

public slots:
    void setTemplate(XMLTemplate* t);
    void save();

private:
    XMLTemplate* m_t { nullptr };
    XMLEditor* m_edit;
};
