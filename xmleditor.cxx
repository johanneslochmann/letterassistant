#include "xmleditor.hxx"

#include <xmltemplate.hxx>

XMLEditor::XMLEditor(QWidget *p)
    : QTextEdit(p)
{
    setAcceptRichText(false);
}

XMLEditor::~XMLEditor()
{
}

void XMLEditor::setXMLTemplate(XMLTemplate *t)
{
    m_t = t;

    if (!m_t) {
        clear();
        return;
    }

    setPlainText(m_t->documentToString());
}
