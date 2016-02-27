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

TextTemplate::TextTemplate(QObject *parent, const QString &txt)
    : QObject(parent), m_txt(txt)
{
    parseText();
}

QString TextTemplate::replaceKeywordsWithValues()
{
    QString buf = m_txt;

    for (auto& e : elements()) {
        buf.replace(QString("!%1!").arg(e->name()), e->values().join(" "));
    }

    return buf;
}

void TextTemplate::parseText()
{
    QStringList rows = m_txt.split("\n");

    for (auto& row : rows) {
        if (row.startsWith("%%%")) {
            QStringList rowData = trimFields(row.replace("%%%", "").split(':'));

            if (rowData.size() != 3) {
                if (rowData.at(0) == "DateFormat") {
                    m_dateFormat = rowData.at(1);
                } else if (rowData.at(0) == "ColumnsInRadioButtonGroups") {
                    m_columnsInRadioButtonGroups = rowData.at(1).toInt();
                } else if (rowData.at(0) == "ColumnsInCheckBoxButtonGroups") {
                    m_columnsInCheckBoxButtonGroups = rowData.at(1).toInt();
                } else {
                    QMessageBox::warning(qApp->activeWindow(), tr("Warning"), tr("Unknown configuration row: %1").arg(row));
                }
            } else {
                auto options = rowData.at(2);

                if (options.contains("|")) {
                    auto e = std::make_shared<TemplateElement>(this, rowData.at(0), rowData.at(1), options.split("|"));
                    m_elements.push_back(e);
                } else {
                    auto e = std::make_shared<TemplateElement>(this, rowData.at(0), rowData.at(1), QStringList(options));
                    m_elements.push_back(e);
                }

            }
        }
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
