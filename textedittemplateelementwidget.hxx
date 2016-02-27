#pragma once

#include "templateelementwidget.hxx"

#include <QTextEdit>

class TextEditTemplateElementWidget : public TemplateElementWidget
{
public:
    TextEditTemplateElementWidget(QWidget* p, TemplateElementSPtr e);

public slots:
    void onTextChanged();

private:
    QTextEdit* m_w;
};
