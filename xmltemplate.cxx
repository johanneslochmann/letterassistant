#include "xmltemplate.hxx"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDate>

XMLTemplate::XMLTemplate()
{
}

XMLTemplate::~XMLTemplate()
{

}

QString XMLTemplate::fileName() const
{
    return m_fileName;
}

void XMLTemplate::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

bool XMLTemplate::loadFromFile(const QString &fname)
{
    m_fileName = fname;

    return false;
}

bool XMLTemplate::saveToFile(const QString &fname)
{
    if (!fname.isEmpty()) {
        m_fileName = fname;
    }

    QFile f(m_fileName);

    if (!f.open(QFile::Truncate | QFile::WriteOnly)) {
        m_lastError = f.errorString();
        return false;
    }

    QTextStream s(&f);
    s << documentToString();

    f.flush();
    f.close();

    return true;
}

QString XMLTemplate::lastError() const
{
    return m_lastError;
}

bool XMLTemplate::hasError() const
{
    return (!lastError().isEmpty());
}

XMLTemplate* XMLTemplate::createNewTemplate(const QString &fname)
{
    auto t = new XMLTemplate();

    t->initDom();
    t->saveToFile(fname);

    return t;
}

XMLTemplate* XMLTemplate::openTemplate(const QString &fname)
{
    auto t = new XMLTemplate();

    t->loadFromFile(fname);

    return t;
}

QString XMLTemplate::documentToString() const
{
    return m_domM.toString(m_xmlIndent).toUtf8();
}

void XMLTemplate::initDom()
{
    auto pi = m_domM.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    m_domM.appendChild(pi);

    m_rootNode = m_domM.createElement(m_rootNodeName);

    m_letterNode = m_domM.createElement(m_letterNodeName);
    m_templateNode.appendChild(createConfigNode());
    m_rootNode.appendChild(createTemplateNode());
    m_rootNode.appendChild(m_letterNode);
    m_domM.appendChild(m_rootNode);
}

QDomNode &XMLTemplate::createConfigNode()
{
    m_configNode = m_domM.createElement(m_configNodeName);

    m_dateFormatNode = m_domM.createElement(m_dateFormatNodeName);
    m_dateFormatNode.appendChild(m_domM.createTextNode(m_defaultDateFormat));

    m_columnsInCheckBoxGroups = m_domM.createElement(m_columnsInCheckBoxGroupsNodeName);
    m_columnsInCheckBoxGroups.appendChild(m_domM.createTextNode(QString::fromUtf8("2")));

    m_columnsInRadioButtonBoxGroups = m_domM.createElement(m_columnsInRadioButtonGroupsNodeName);
    m_columnsInRadioButtonBoxGroups.appendChild(m_domM.createTextNode(QString::fromUtf8("2")));

    m_configNode.appendChild(m_dateFormatNode);
    m_configNode.appendChild(m_columnsInCheckBoxGroups);
    m_configNode.appendChild(m_columnsInRadioButtonBoxGroups);

    return m_configNode;
}

QDomNode &XMLTemplate::createTemplateNode()
{
    m_templateNode = m_domM.createElement(m_templateNodeName);

    m_fields = m_domM.createElement(m_fieldsNodeName);

    m_fields.appendChild(createShortTextField(QString::fromUtf8("FirstName"), QObject::trUtf8("First Name")));
    m_fields.appendChild(createShortTextField(QString::fromUtf8("FamilyName"), QObject::trUtf8("Family Name")));
    m_fields.appendChild(createDateEditField(QString::fromUtf8("Date"), QDate::currentDate().toString(m_defaultDateFormat.toLatin1())));
    m_fields.appendChild(createLongTextField(QString::fromUtf8("Comment"), QObject::trUtf8("")));

    m_templateNode.appendChild(m_fields);
    return m_templateNode;
}

QDomNode XMLTemplate::createShortTextField(const QString &name, const QString &defaultValue)
{
    auto n = m_domM.createElement(m_shortTextFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);
    n.appendChild(m_domM.createTextNode(defaultValue));
    return n;
}

QDomNode XMLTemplate::createLongTextField(const QString &name, const QString &defaultValue)
{
    auto n = m_domM.createElement(m_longTextFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);
    n.appendChild(m_domM.createTextNode(defaultValue));
    return n;
}

QDomNode XMLTemplate::createDateEditField(const QString &name, const QString &defaultValue)
{
    auto n = m_domM.createElement(m_dateEditFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);
    n.appendChild(m_domM.createTextNode(defaultValue));
    return n;
}
