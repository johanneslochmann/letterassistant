#include "xmltemplate.hxx"

#include <QFile>
#include <QTextStream>
#include <QDebug>

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

    m_templateNode = m_domM.createElement(m_templateNodeName);
    m_letterNode = m_domM.createElement(m_letterNodeName);
    m_configNode = m_domM.createElement(m_configNodeName);

    m_dateFormatNode = m_domM.createElement(m_dateFormatNodeName);
    m_dateFormatNode.appendChild(m_domM.createTextNode(QString::fromUtf8("dd/mm/yyyy")));

    m_columnsInCheckBoxGroups = m_domM.createElement(m_columnsInCheckBoxGroupsNodeName);
    m_columnsInCheckBoxGroups.appendChild(m_domM.createTextNode(QString::fromUtf8("2")));

    m_columnsInRadioButtonBoxGroups = m_domM.createElement(m_columnsInRadioButtonGroupsNodeName);
    m_columnsInRadioButtonBoxGroups.appendChild(m_domM.createTextNode(QString::fromUtf8("2")));

    m_configNode.appendChild(m_dateFormatNode);
    m_configNode.appendChild(m_columnsInCheckBoxGroups);
    m_configNode.appendChild(m_columnsInRadioButtonBoxGroups);

    m_templateNode.appendChild(m_configNode);
    m_rootNode.appendChild(m_templateNode);
    m_rootNode.appendChild(m_letterNode);
    m_domM.appendChild(m_rootNode);
}
