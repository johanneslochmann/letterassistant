#include "textedittemplateelementwidget.hxx"

#include <QLayout>

TextEditTemplateElementWidget::TextEditTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    setLayout(new QVBoxLayout(this));
    m_w = new QTextEdit(this);
    m_w->setAcceptRichText(false);
    m_w->setPlainText(e->options().join(""));

    layout()->addWidget(m_w);

    connect(m_w, &QTextEdit::textChanged, this, &TextEditTemplateElementWidget::onTextChanged);
}

void TextEditTemplateElementWidget::onTextChanged()
{
    element()->setSingleValue(m_w->toPlainText());
}
