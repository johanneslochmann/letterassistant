#include "templateelementwidget.hxx"

TemplateElementWidget::TemplateElementWidget(QWidget *p, TemplateElementSPtr element)
    : QGroupBox(element->name(), p)
{
}
