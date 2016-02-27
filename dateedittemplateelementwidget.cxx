#include "dateedittemplateelementwidget.hxx"

#include <QDateEdit>
#include <QLayout>

#include "texttemplate.hxx"

DateEditTemplateElementWidget::DateEditTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    setLayout(new QVBoxLayout(this));

    m_w = new QDateEdit(this);
    layout()->addWidget(m_w);

    connect(m_w, &QDateEdit::dateChanged, this, &DateEditTemplateElementWidget::onDateChanged);

    m_w->setDate(QDate::currentDate());
    onDateChanged(m_w->date());
}

void DateEditTemplateElementWidget::onDateChanged(const QDate &d)
{
    element()->setSingleValue(d.toString(element()->textTemplate()->dateFormat()));
}
