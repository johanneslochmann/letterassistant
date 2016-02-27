#include "templateelement.hxx"

TemplateElement::TemplateElement(const QString &name, const QString &typeName, const QStringList &options)
    : m_name(name), m_typeName(typeName), m_options(options)
{
}

TemplateElement::~TemplateElement()
{
}
