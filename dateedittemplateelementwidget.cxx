#include "dateedittemplateelementwidget.hxx"

#include <QCalendarWidget>
#include <QLayout>

DateEditTemplateElementWidget::DateEditTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    setLayout(new QVBoxLayout(this));

    m_w = new QCalendarWidget(this);
    layout()->addWidget(m_w);

    connect(m_w, &QCalendarWidget::activated, this, &DateEditTemplateElementWidget::onDateChanged);

    m_w->setSelectedDate(QDate::currentDate());
    onDateChanged(m_w->selectedDate());
}

void DateEditTemplateElementWidget::onDateChanged(const QDate &d)
{
    element()->setSingleValue(d.toString(Qt::ISODate));
}
