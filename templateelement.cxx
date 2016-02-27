#include "templateelement.hxx"

TemplateElement::TemplateElement(const QString &name, const QString &typeName, const QStringList &options)
    : m_name(name.trimmed()), m_typeName(typeName.trimmed()), m_options(options)
{
}

TemplateElement::~TemplateElement()
{
}
