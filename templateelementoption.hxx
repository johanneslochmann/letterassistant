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

class TemplateElementOption;
using templateElementOptionSPtr = std::shared_ptr<TemplateElementOption>;
using TemplateElementOptionSPtrVector = std::vector<templateElementOptionSPtr>;

class TemplateElementOption
{
public:
    TemplateElementOption(const QString& name, const QString& hint);

    const QString& name() const { return m_name; }
    const QString& hint() const { return m_hint; }

    void setHint(const QString& h) { m_hint = h; }
    void setName(const QString& n) { m_name = n; }

    bool hasHint() const { return (!hint().isEmpty()); }

private:
    QString m_name;
    QString m_hint;
};
