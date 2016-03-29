#include "xmltemplate.hxx"

#include <QFile>
#include <QTextStream>

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

    QFile f;

    if (!f.open(QFile::Truncate | QFile::WriteOnly)) {
        m_lastError = f.errorString();
        return false;
    }

    QTextStream s(&f);
    s << m_domM.toString(m_xmlIndent).toUtf8();

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

XMLTemplate XMLTemplate::createNewTemplate(const QString &fname)
{
    XMLTemplate t;

    t.initDom();
    t.saveToFile(fname);

    return t;
}

XMLTemplate XMLTemplate::openTemplate(const QString &fname)
{
    XMLTemplate t;

    t.loadFromFile(fname);

    return t;
}

void XMLTemplate::initDom()
{
    m_domM.createElement(m_rootNodeName);
}
