#pragma once

#include "templateelementwidget.hxx"

#include <QRadioButton>

#include <vector>

using RadioButtonVector = std::vector<QRadioButton*>;

class RadioButtonTemplateElementWidget : public TemplateElementWidget
{
    Q_OBJECT
public:
    RadioButtonTemplateElementWidget(QWidget* p, TemplateElementSPtr e);

public:
    void onToggled(bool checked);

private:
    RadioButtonVector m_buttons;
};
