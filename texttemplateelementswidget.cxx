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

#include "texttemplateelementswidget.hxx"

#include <QLayout>
#include <QGroupBox>

#include "texttemplate.hxx"
#include "templateelement.hxx"
#include "templateelementwidget.hxx"
#include "lineedittemplateelementwidget.hxx"
#include "textedittemplateelementwidget.hxx"
#include "radiobuttontemplateelementwidget.hxx"
#include "checkboxtemplateelementwidget.hxx"
#include "dateedittemplateelementwidget.hxx"

TextTemplateElementsWidget::TextTemplateElementsWidget(QWidget *parent, TextTemplate *textTemplate)
    : QWidget(parent), m_tmpl(textTemplate)
{
    setLayout(new QVBoxLayout(this));

    createWidgets();
}

void TextTemplateElementsWidget::createWidgets()
{
    for (const auto& e : m_tmpl->elements()) {
        if (e->typeName() == "ShortText") {
            layout()->addWidget(new LineEditTemplateElementWidget(this, e));
        } else if (e->typeName() == "LongText") {
            layout()->addWidget(new TextEditTemplateElementWidget(this, e));
        } else if (e->typeName() == "OneOf") {
            layout()->addWidget(new RadioButtonTemplateElementWidget(this, e));
        } else if (e->typeName() == "AnyOf") {
            layout()->addWidget(new CheckBoxTemplateElementWidget(this, e));
        } else if (e->typeName() == "DateEdit") {
            layout()->addWidget(new DateEditTemplateElementWidget(this, e));
        }
    }
}
