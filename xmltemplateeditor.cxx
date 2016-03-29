#include "xmltemplateeditor.hxx"

#include <xmltemplate.hxx>
#include <xmleditor.hxx>

XMLTemplateEditor::XMLTemplateEditor(QWidget *p)
    : QMdiSubWindow(p)
{
    setWindowTitle(trUtf8("Template"));
    m_edit = new XMLEditor(this);
    setWidget(m_edit);
}

XMLTemplateEditor::~XMLTemplateEditor()
{
}

void XMLTemplateEditor::setTemplate(XMLTemplate *t)
{
    m_t = t;

    m_edit->setXMLTemplate(m_t);

    if (hasTemplate()) {
        setWindowTitle(trUtf8("Template: %1").arg(t->fileName()));
    }
}
