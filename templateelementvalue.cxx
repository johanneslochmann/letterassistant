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

#include <QString>

#include "templateelementvalue.hxx"

TemplateElementValue::TemplateElementValue()
{
}

TemplateElementValue::TemplateElementValue(const QString &name, const QString &value)
    : m_name(name), m_value(value)
{
}

const QString TemplateElementValue::toString() const
{
    if (value().isEmpty()) {
        return name();
    }

    return QString::fromUtf8("%1 (%2)").arg(name(), value());
}

const QString &TemplateElementValue::value() const
{
    return m_value;
}

const QString &TemplateElementValue::name() const
{
    return m_name;
}

void TemplateElementValue::setValue(const QString &value)
{
    m_value = value;
}
