#include "templateelement.hxx"

TemplateElement::TemplateElement(TextTemplate* t, const QString &name, const QString &typeName, const QStringList &options)
    : m_textTemplate(t), m_name(name.trimmed()), m_typeName(typeName.trimmed()), m_options(options)
{
}

TemplateElement::~TemplateElement()
{
}
