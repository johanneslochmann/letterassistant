#pragma once

#include "templateelementwidget.hxx"

#include <QLineEdit>

class LineEditTemplateElementWidget : public TemplateElementWidget
{
    Q_OBJECT
public:
    LineEditTemplateElementWidget(QWidget* p, TemplateElementSPtr e);

public slots:
    void onValueChanged(const QString& v);

private:
    QLineEdit* m_w;
};
