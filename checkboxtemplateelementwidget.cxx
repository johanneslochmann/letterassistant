#include "checkboxtemplateelementwidget.hxx"

#include <QCheckBox>
#include <QLayout>

#include "texttemplate.hxx"

CheckBoxTemplateElementWidget::CheckBoxTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    auto l = new QGridLayout(this);
    setLayout(l);

    int maxCols = e->textTemplate()->columnsInCheckBoxButtonGroups();
    int row = 0;
    int col = 0;

    for (auto& option : e->options()) {
        auto b = new QCheckBox(option, this);
        m_buttons.push_back(b);
        l->addWidget(b, row, col++);

        if (col >= maxCols) {
            row++;
            col = 0;
        }

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
