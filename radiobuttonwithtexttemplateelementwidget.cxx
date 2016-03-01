/*
 * (c) 2016  Johannes Lochmann
 * Email:    jolo@johanneslochmann.net
 * Website:  http://www.johanneslochmann.net/letterassistant
 *
 * This file is part of LetterAssistant.
 *
 * LetterAssistant is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LetterAssistant is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LetterAssistant.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "radiobuttonwithtexttemplateelementwidget.hxx"

#include <cassert>

#include <QLayout>
#include <QRadioButton>
#include <QLineEdit>

#include "texttemplate.hxx"
#include "templateelement.hxx"

RadioButtonWithTextTemplateElementWidget::RadioButtonWithTextTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    auto l = new QGridLayout(this);
    setLayout(l);

    int maxCols = e->textTemplate()->columnsInRadioButtonGroups();
    int row = 0;
    int col = 0;

    for (auto& option : e->elementOptions()) {
        auto b = new QRadioButton(option->name(), this);

        if (option->hasHint()) {
            b->setToolTip(option->hint());
        }

        auto e = new QLineEdit(this);
        e->setEnabled(false);

        m_buttons.push_back(b);
        m_edits.push_back(e);

        l->addWidget(b, row, col++);
        l->addWidget(e, row, col++);

        if (col >= maxCols) {
            row++;
            col = 0;
        }

        connect(b, &QRadioButton::toggled, this, &RadioButtonWithTextTemplateElementWidget::onToggled);
        connect(e, &QLineEdit::textChanged, this, &RadioButtonWithTextTemplateElementWidget::onTextChanged);
    }
}

void RadioButtonWithTextTemplateElementWidget::onToggled(bool checked)
{
    (void) checked;
    updateData();
}

void RadioButtonWithTextTemplateElementWidget::onTextChanged()
{
    updateData();
}

void RadioButtonWithTextTemplateElementWidget::updateData()
{
    assert(m_edits.size() == m_buttons.size());

    for (std::size_t i = 0; i != m_edits.size(); ++i) {
        auto checkBox = m_buttons.at(i);
        auto lineEdit = m_edits.at(i);

        Q_CHECK_PTR(checkBox);
        Q_CHECK_PTR(lineEdit);

        if (!checkBox->isChecked()) {
            element()->removeElementOption(checkBox->text());
            lineEdit->setEnabled(false);
        } else {
            element()->setElementValue(checkBox->text(), lineEdit->text());

            if (!lineEdit->isEnabled()) {
                lineEdit->setEnabled(true);
            }
        }
    }
}
