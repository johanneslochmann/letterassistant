#pragma once

#include "templateelementwidget.hxx"

class QCalendarWidget;

class DateEditTemplateElementWidget : public TemplateElementWidget
{
    Q_OBJECT
public:
    DateEditTemplateElementWidget(QWidget* p, TemplateElementSPtr e);

public slots:
    void onDateChanged(const QDate& d);

private:
    QCalendarWidget* m_w;
};
