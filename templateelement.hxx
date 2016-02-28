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

#include <memory>
#include <vector>

#include <QString>
#include <QStringList>

#include "templateelementvalue.hxx"

class TemplateElement;
class TextTemplate;

using TemplateElementSPtr = std::shared_ptr<TemplateElement>;
using TemplateElementSPtrVector = std::vector<TemplateElementSPtr>;

class TemplateElement
{
public:
    TemplateElement(TextTemplate* t, const QString& name, const QString& typeName, const QStringList& options);
    virtual ~TemplateElement();

    TextTemplate* textTemplate() const { return m_textTemplate; }

    const QString& name() const { return m_name; }
    const QString& typeName() const { return m_typeName; }
    const QStringList& options() const { return m_options; }

    void setElementValue(const QString& name, const QString& value={});
    void clearElementValues();
    const TemplateElementValueSPtrVector elementValues() const;

    QString toString() const { return implToString(); }

protected:
    virtual QString implToString() const = 0;

private:
    TextTemplate* m_textTemplate;

    QString m_name;
    QString m_typeName;
    QStringList m_options;

    TemplateElementValueSPtrVector m_elementValues;
};
