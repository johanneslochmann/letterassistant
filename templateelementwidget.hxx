#pragma once

#include <QGroupBox>

#include "templateelement.hxx"

class TemplateElementWidget : public QGroupBox
{
public:
    TemplateElementWidget(QWidget* p, TemplateElementSPtr element);

private:
    TemplateElementSPtr m_element;
};
