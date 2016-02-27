#pragma once

#include <memory>
#include <vector>

#include <QString>
#include <QStringList>

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

    void setValues(const QStringList& v) { m_values = v; }
    void setSingleValue(const QString& v) { clearValues(); m_values.append(v); }
    void addValue(const QString& v) { m_values.append(v); }
    void clearValues() { m_values.clear(); }
    const QStringList& values() const { return m_values; }

private:
    TextTemplate* m_textTemplate;

    QString m_name;
    QString m_typeName;
    QStringList m_options;

    QStringList m_values;
};
