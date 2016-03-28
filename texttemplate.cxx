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

#include "texttemplate.hxx"

#include <QDebug>
#include <QMessageBox>
#include <QApplication>

#include "texttemplateelement.hxx"
#include "datetemplateelement.hxx"
#include "optionstemplateelement.hxx"
#include "optionswithtexttemplateelement.hxx"

TextTemplate::TextTemplate(QObject *parent, const QString &txt)
    : QObject(parent), m_txt(txt)
{
    parseText();
}

QString TextTemplate::replaceKeywordsWithValues()
{
    QString buf = m_txtWithoutPlaceholders.join("\n");

    for (auto& e : elements()) {
        buf.replace(QString::fromUtf8("!%1!").arg(e->name()), e->toString());
    }

    return buf;
}

void TextTemplate::parseText()
{
    QStringList rows = m_txt.split("\n");

    for (auto& row : rows) {
        parseRow(row);
    }
}

void TextTemplate::parseConfigurationRow(const QString &row, const QStringList& rowData)
{
    auto keyword = rowData.at(0);

    if (QString::fromUtf8("DateFormat") == keyword) {
        m_dateFormat = rowData.at(1);
    } else if (QString::fromUtf8("ColumnsInRadioButtonGroups") == keyword) {
        m_columnsInRadioButtonGroups = rowData.at(1).toInt();
    } else if (QString::fromUtf8("ColumnsInCheckBoxButtonGroups") == keyword) {
        m_columnsInCheckBoxButtonGroups = rowData.at(1).toInt();
    } else if (QString::fromUtf8("ColumnsInRadioButtonGroupWithText") == keyword) {
        m_columnsInRadioButtonGroupsWithText = rowData.at(1).toInt();
    } else if (QString::fromUtf8("ColumnsInCheckBoxButtonGroupWithText") == keyword) {
        m_columnsInCheckBoxButtonGroupsWithText = rowData.at(1).toInt();
    } else {
        QMessageBox::warning(qApp->activeWindow(),
                             trUtf8("Warning"),
                             trUtf8("Unknown configuration row: %1").arg(row));
    }
}

void TextTemplate::parseOptionRow(const QString &row, const QStringList &rowData)
{
    auto optionName = rowData.at(0);
    auto typeName = rowData.at(1);
    auto options = rowData.at(2);
    auto optionList = options.split("|");

    if ((QString::fromUtf8("ShortText") == typeName)
            || (QString::fromUtf8("LongText") == typeName)) {
        auto e = std::make_shared<TextTemplateElement>(this, optionName, typeName, optionList);
        m_elements.push_back(e);
    } else if (QString::fromUtf8("DateEdit") == typeName) {
        auto e = std::make_shared<DateTemplateElement>(this, optionName, typeName, optionList);
        m_elements.push_back(e);
    } else if ((QString::fromUtf8("OneOf") == typeName)
               || (QString::fromUtf8("AnyOf") == typeName)) {
        auto e = std::make_shared<OptionsTemplateElement>(this, optionName, typeName, optionList);
        m_elements.push_back(e);
    } else if ((QString::fromUtf8("OneOfWithText") == typeName)
               || (QString::fromUtf8("AnyOfWithText") == typeName)) {
        auto e = std::make_shared<OptionsWithTextTemplateElement>(this, optionName, typeName, optionList);
        m_elements.push_back(e);
    } else {
        QMessageBox::warning(qApp->activeWindow(),
                             trUtf8("Failed to parse row"),
                             trUtf8("Unknown Option Type <%1> in row:\n%2").arg(typeName).arg(row));
    }
}

void TextTemplate::parseRow(const QString &row)
{
    if (row.startsWith(QString::fromUtf8("%%%"))) {
        QStringList rowData = trimFields(QString(row).replace(QString::fromUtf8("%%%"), "").split(':'));

        if (rowData.size() != 3) {
            parseConfigurationRow(row, rowData);
        } else {
            parseOptionRow(row, rowData);
        }
    } else {
        m_txtWithoutPlaceholders.append(row);
    }
}

QStringList TextTemplate::trimFields(const QStringList &data)
{
    QStringList r;

    for (const auto& d : data) {
        r.append(d.trimmed());
    }

    return r;
}
