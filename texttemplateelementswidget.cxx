#include "texttemplateelementswidget.hxx"

#include <QLayout>
#include <QGroupBox>

#include "texttemplate.hxx"
#include "templateelement.hxx"

TextTemplateElementsWidget::TextTemplateElementsWidget(QWidget *parent, TextTemplate *textTemplate) : QWidget(parent)
  , m_tmpl(textTemplate)
{
    setLayout(new QVBoxLayout(this));

    createWidgets();
}

void TextTemplateElementsWidget::createWidgets()
{
    for (const auto& e : m_tmpl->elements()) {
        QGroupBox* b = new QGroupBox(e->name(), this);
        layout()->addWidget(b);
    }
}
