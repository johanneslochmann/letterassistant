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

#include "templateelement.hxx"

#include <algorithm>

class TemplateElement;
using TemplateElementSPtr = std::shared_ptr<TemplateElement>;
using TemplateElementSPtrVector = std::vector<TemplateElementSPtr>;

TemplateElement::TemplateElement(TextTemplate* t, const QString &name, const QString &typeName, const QStringList &options)
    : m_textTemplate(t), m_name(name.trimmed()), m_typeName(typeName.trimmed())
{
    for (auto o : options) {
        if (o.contains("?")) {
            auto buf = o.split('?');
            addElementOption(buf.at(0), buf.at(1));
        } else {
            addElementOption(o);
        }
    }
}

TemplateElement::~TemplateElement()
{
}

QStringList TemplateElement::optionNames() const
{
    QStringList l;

    for (auto& i : m_elementDescriptions) {
        l.push_back(i->name());
    }

    return l;
}

void TemplateElement::setElementValue(const QString &name, const QString &value)
{
    for (auto& i : m_elementValues) {
        if (i->name() == name) {
            i->setValue(value);
            return;
        }
    }

    auto v = std::make_shared<TemplateElementValue>(name, value);
    m_elementValues.push_back(v);
}

void TemplateElement::clearElementValues()
{
    m_elementValues.clear();
}

const TemplateElementValueSPtrVector TemplateElement::elementValues() const
{
    return m_elementValues;
}

void TemplateElement::addElementOption(const QString &name, const QString &hint)
{
    auto d = std::make_shared<TemplateElementOption>(name, hint);
    m_elementDescriptions.push_back(d);
}

void TemplateElement::removeElementOption(const QString &name)
{
    auto i = std::find_if(std::begin(m_elementValues),
                          std::end(m_elementValues),
                          [=](TemplateElementValueSPtr e) { return (e->name() == name); });

    if (std::end(m_elementValues) != i) {
        m_elementValues.erase(i);
    }
}
