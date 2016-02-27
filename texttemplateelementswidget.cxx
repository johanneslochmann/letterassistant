#include "texttemplateelementswidget.hxx"

#include <QLayout>
#include <QGroupBox>

#include "texttemplate.hxx"
#include "templateelement.hxx"
#include "templateelementwidget.hxx"
#include "lineedittemplateelementwidget.hxx"
#include "textedittemplateelementwidget.hxx"
#include "radiobuttontemplateelementwidget.hxx"
#include "checkboxtemplateelementwidget.hxx"
#include "dateedittemplateelementwidget.hxx"

TextTemplateElementsWidget::TextTemplateElementsWidget(QWidget *parent, TextTemplate *textTemplate)
    : QWidget(parent), m_tmpl(textTemplate)
{
    setLayout(new QVBoxLayout(this));

    createWidgets();
}

void TextTemplateElementsWidget::createWidgets()
{
    for (const auto& e : m_tmpl->elements()) {
        if (e->typeName() == "ShortText") {
            layout()->addWidget(new LineEditTemplateElementWidget(this, e));
        } else if (e->typeName() == "LongText") {
            layout()->addWidget(new TextEditTemplateElementWidget(this, e));
        } else if (e->typeName() == "OneOf") {
            layout()->addWidget(new RadioButtonTemplateElementWidget(this, e));
        } else if (e->typeName() == "AnyOf") {
            layout()->addWidget(new CheckBoxTemplateElementWidget(this, e));
        } else if (e->typeName() == "DateEdit") {
            layout()->addWidget(new DateEditTemplateElementWidget(this, e));
        }
    }
}
