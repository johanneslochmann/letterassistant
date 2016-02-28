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

#include <QString>

#include <memory>
#include <vector>

class TemplateElementValue;
using TemplateElementValueSPtr = std::shared_ptr<TemplateElementValue>;
using TemplateElementValueSPtrVector = std::vector<TemplateElementValueSPtr>;

class TemplateElementValue
{
public:
    TemplateElementValue();
    TemplateElementValue(const QString& name, const QString& value);

    const QString toString() const;

    const QString& value() const;
    const QString& name() const;

    void setValue(const QString &value);

private:
    QString m_name;
    QString m_value;
};
