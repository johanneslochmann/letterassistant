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

    for (auto& option : e->elementOptions()) {
        auto b = new QRadioButton(option->name(), this);

        if (option->hasHint()) {
            b->setToolTip(option->hint());
        }

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
    element()->clearElementValues();

    for (auto b : m_buttons) {
        if (b->isChecked()) {
            element()->setElementValue(b->text());
            return;
        }
    }
}
