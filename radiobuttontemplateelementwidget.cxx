#include "radiobuttontemplateelementwidget.hxx"

#include <QLayout>
#include <QRadioButton>

#include "texttemplate.hxx"

RadioButtonTemplateElementWidget::RadioButtonTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    auto l = new QGridLayout(this);
    setLayout(l);

    int maxCols = e->textTemplate()->columnsInRadioButtonGroups();
    int row = 0;
    int col = 0;

    for (auto& option : e->options()) {
        auto b = new QRadioButton(option, this);
        m_buttons.push_back(b);
        l->addWidget(b, row, col++);

        if (col >= maxCols) {
            row++;
            col = 0;
        }

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
