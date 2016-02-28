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

#include "textedittemplateelementwidget.hxx"

#include <QLayout>

TextEditTemplateElementWidget::TextEditTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    setLayout(new QVBoxLayout(this));
    m_w = new QTextEdit(this);
    m_w->setAcceptRichText(false);
    m_w->setPlainText(e->options().join(""));

    layout()->addWidget(m_w);

    connect(m_w, &QTextEdit::textChanged, this, &TextEditTemplateElementWidget::onTextChanged);
}

void TextEditTemplateElementWidget::onTextChanged()
{
    element()->clearElementValues();
    element()->setElementValue(element()->name(), m_w->toPlainText());
}
