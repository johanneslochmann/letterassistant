#include "xmltemplateeditor.hxx"

#include <xmltemplate.hxx>

XMLTemplateEditor::XMLTemplateEditor(QWidget *p)
    : QMdiSubWindow(p)
{
    setWindowTitle(trUtf8("Template"));
}

XMLTemplateEditor::~XMLTemplateEditor()
{
}

void XMLTemplateEditor::setTemplate(XMLTemplate *t)
{
    m_t = t;

    if (hasTemplate()) {
        setWindowTitle(trUtf8("Template: %1").arg(t->fileName()));
    }
}
