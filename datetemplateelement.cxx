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

#include "datetemplateelement.hxx"


DateTemplateElement::DateTemplateElement(TextTemplate *t, const QString &name, const QString &typeName, const QStringList &options)
    : TemplateElement(t, name, typeName, options)
{
}

QString DateTemplateElement::implToString() const
{
    QStringList ret;

    for (auto& e : elementValues()) {
        ret.append(e->value());
    }

    return ret.join(", ");
}
