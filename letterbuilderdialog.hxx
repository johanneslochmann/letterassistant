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

#include <QDialog>

class QDialogButtonBox;
class QScrollArea;

class TextTemplate;
class TextTemplateElementsWidget;

class LetterBuilderDialog : public QDialog
{
    Q_OBJECT
public:
    LetterBuilderDialog(QWidget* p, const QString& templateText);

public slots:
    void accept() override;
    void save();
    void reject() override;

protected:
    bool doSave();

private:
    TextTemplate* m_template;

    QDialogButtonBox* m_buttons;
    QScrollArea* m_scrollArea;
    TextTemplateElementsWidget* m_elementsW;
};
