#pragma once

#include <QGroupBox>

#include "templateelement.hxx"

class TemplateElementWidget : public QGroupBox
{
public:
    TemplateElementWidget(QWidget* p, TemplateElementSPtr element);

    TemplateElementSPtr element() const { return m_element; }

private:
    TemplateElementSPtr m_element;
};
