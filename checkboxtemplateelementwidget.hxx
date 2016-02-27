#pragma once

#include "templateelementwidget.hxx"

#include <vector>

class QCheckBox;

using CheckBoxVector = std::vector<QCheckBox*>;

class CheckBoxTemplateElementWidget : public TemplateElementWidget
{
    Q_OBJECT
public:
    CheckBoxTemplateElementWidget(QWidget* p, TemplateElementSPtr e);

public slots:
    void onToggled(bool isChecked);

private:
    CheckBoxVector m_buttons;
};
