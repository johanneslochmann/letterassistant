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

#pragma once

#include "templateelementwidget.hxx"

#include <vector>

class QRadioButton;
class QLineEdit;

using RadioButtonVector = std::vector<QRadioButton*>;
using LineEditVector = std::vector<QLineEdit*>;

class RadioButtonWithTextTemplateElementWidget : public TemplateElementWidget
{
public:
    RadioButtonWithTextTemplateElementWidget(QWidget* p, TemplateElementSPtr e);

public:
    void onToggled(bool checked);
    void onTextChanged();

protected:
    void updateData();

private:
    RadioButtonVector m_buttons;
    LineEditVector m_edits;
};
