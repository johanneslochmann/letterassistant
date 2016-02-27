#include "radiobuttontemplateelementwidget.hxx"

#include <QLayout>
#include <QRadioButton>

RadioButtonTemplateElementWidget::RadioButtonTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    setLayout(new QVBoxLayout(this));

    for (auto& option : e->options()) {
        auto b = new QRadioButton(option, this);
        m_buttons.push_back(b);
        layout()->addWidget(b);

        connect(b, &QRadioButton::toggled, this, &RadioButtonTemplateElementWidget::onToggled);
    }
}

void RadioButtonTemplateElementWidget::onToggled(bool checked)
{
    (void) checked;
    element()->clearValues();

    for (auto b : m_buttons) {
        if (b->isChecked()) {
            element()->setSingleValue(b->text());
            return;
        }
    }
}
