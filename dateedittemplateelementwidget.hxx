#pragma once

#include "templateelementwidget.hxx"

class QDateEdit;

class DateEditTemplateElementWidget : public TemplateElementWidget
{
    Q_OBJECT
public:
    DateEditTemplateElementWidget(QWidget* p, TemplateElementSPtr e);

public slots:
    void onDateChanged(const QDate& d);

private:
    QDateEdit* m_w;
};
