#include "checkboxtemplateelementwidget.hxx"

#include <QCheckBox>
#include <QLayout>

CheckBoxTemplateElementWidget::CheckBoxTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    setLayout(new QVBoxLayout(this));

    for (auto& option : e->options()) {
        auto b = new QCheckBox(option, this);
        m_buttons.push_back(b);
        layout()->addWidget(b);

        connect(b, &QCheckBox::toggled, this, &CheckBoxTemplateElementWidget::onToggled);
    }
}

void CheckBoxTemplateElementWidget::onToggled(bool isChecked)
{
    (void) isChecked;

    element()->clearValues();

    QStringList checkedOptions;

    for (auto& b : m_buttons) {
        if (b->isChecked()) {
            checkedOptions.push_back(b->text());
        }
    }

    element()->setValues(checkedOptions);
}
