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

#include <QObject>
#include <QList>

#include <templateelement.hxx>

class TextTemplate : public QObject
{
    Q_OBJECT
public:
    explicit TextTemplate(QObject *parent, const QString& txt);

    const TemplateElementSPtrVector& elements() const { return m_elements; }

    QString replaceKeywordsWithValues();
    QString dateFormat() const { return m_dateFormat; }
    int columnsInRadioButtonGroups() const { return m_columnsInRadioButtonGroups; }
    int columnsInCheckBoxButtonGroups() const { return m_columnsInCheckBoxButtonGroups; }

signals:

public slots:

protected:
    void parseText();

    void parseRow(const QString& row);
    void parseConfigurationRow(const QString &row, const QStringList& rowData);
    void parseOptionRow(const QString& row, const QStringList& rowData);

    QStringList trimFields(const QStringList& data);

private:
    QString m_txt;
    QStringList m_txtWithoutPlaceholders;

    QString m_dateFormat { QString::fromUtf8("dd/mm/yyyy") };
    int m_columnsInRadioButtonGroups { 3 };
    int m_columnsInCheckBoxButtonGroups { 1 };
    int m_columnsInRadioButtonGroupsWithText { 1 };
    int m_columnsInCheckBoxButtonGroupsWithText { 1 };

    TemplateElementSPtrVector m_elements;
};
