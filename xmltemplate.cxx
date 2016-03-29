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

QString XMLTemplate::createShortTextFieldText(const QString &name, const QString &defaultValue)
{
    QDomDocument doc;
    doc.appendChild(createShortTextField(name, defaultValue, doc));
    return doc.toString(m_xmlIndent).toUtf8();
}

QString XMLTemplate::createLongTextFieldText(const QString &name, const QString &defaultValue)
{
    QDomDocument doc;
    doc.appendChild(createLongTextField(name, defaultValue, doc));
    return doc.toString(m_xmlIndent).toUtf8();
}

QString XMLTemplate::createDateEditFieldText(const QString &name, const QString &defaultValue)
{
    QDomDocument doc;
    doc.appendChild(createDateEditField(name, defaultValue, doc));
    return doc.toString(m_xmlIndent).toUtf8();
}

QString XMLTemplate::createOneOfFieldText(const QString &name)
{
    QDomDocument doc;

    doc.appendChild(createOneOfField(name, QStringList( { QObject::trUtf8("Item 1"),
                                                          QObject::trUtf8("Item 2"),
                                                          QObject::trUtf8("Item 3"),
                                                          QObject::trUtf8("Item 4")} ),
                                     doc));
    return doc.toString(m_xmlIndent).toUtf8();
}

QString XMLTemplate::createAnyOfFieldText(const QString &name)
{
    QDomDocument doc;
    doc.appendChild(createAnyOfField(name, QStringList( { QObject::trUtf8("Item 1"),
                                                          QObject::trUtf8("Item 2"),
                                                          QObject::trUtf8("Item 3"),
                                                          QObject::trUtf8("Item 4")} ),
                                     doc));
    return doc.toString(m_xmlIndent).toUtf8();
}

void XMLTemplate::initDom()
{
    m_domM.appendChild(m_domM.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\""));

    m_rootNode = m_domM.createElement(m_rootNodeName);

    m_rootNode.appendChild(createConfigNode());
    m_rootNode.appendChild(createTemplateNode());
    m_rootNode.appendChild(createLetterNode());

    m_domM.appendChild(m_rootNode);
}

QDomNode XMLTemplate::createConfigNode()
{
    m_configNode = m_domM.createElement(m_configNodeName);

    m_dateFormatNode = m_domM.createElement(m_dateFormatNodeName);
    m_dateFormatNode.appendChild(m_domM.createTextNode(m_defaultDateFormat));
    m_configNode.appendChild(m_dateFormatNode);

    m_columnsInCheckBoxGroups = m_domM.createElement(m_columnsInCheckBoxGroupsNodeName);
    m_columnsInCheckBoxGroups.appendChild(m_domM.createTextNode(QString::fromUtf8("2")));
    m_configNode.appendChild(m_columnsInCheckBoxGroups);

    m_columnsInRadioButtonBoxGroups = m_domM.createElement(m_columnsInRadioButtonGroupsNodeName);
    m_columnsInRadioButtonBoxGroups.appendChild(m_domM.createTextNode(QString::fromUtf8("2")));
    m_configNode.appendChild(m_columnsInRadioButtonBoxGroups);

    return m_configNode;
}

QDomNode XMLTemplate::createTemplateNode()
{
    m_templateNode = m_domM.createElement(m_templateNodeName);

    m_fields = m_domM.createElement(m_fieldsNodeName);

    m_fields.appendChild(createShortTextField(QString::fromUtf8("Place"), QObject::trUtf8("New York"), m_domM));
    m_fields.appendChild(createDateEditField(QString::fromUtf8("Date"), QDate::currentDate().toString(m_defaultDateFormat.toLatin1()), m_domM));
    m_fields.appendChild(createOneOfField(QString::fromUtf8("Title"), QStringList( { QObject::trUtf8("Mr."),
                                                                                     QObject::trUtf8("Ms."),
                                                                                     QObject::trUtf8("Dr."),
                                                                                     QObject::trUtf8("Prof.")} )
                                          , m_domM));
    m_fields.appendChild(createShortTextField(QString::fromUtf8("FirstName"), QObject::trUtf8("First Name"), m_domM));
    m_fields.appendChild(createShortTextField(QString::fromUtf8("FamilyName"), QObject::trUtf8("Family Name"), m_domM));
    m_fields.appendChild(createShortTextField(QString::fromUtf8("Signature"), QObject::trUtf8("Dr. Foo Bar"), m_domM));

    m_fields.appendChild(createOneOfField(QString::fromUtf8("ChooseOne"), QStringList( { QObject::trUtf8("first"),
                                                                                         QObject::trUtf8("second"),
                                                                                         QObject::trUtf8("third"),
                                                                                         QObject::trUtf8("fourth")} ),
                                          m_domM));
    m_fields.appendChild(createAnyOfField(QString::fromUtf8("ChooseAny"), QStringList( { QObject::trUtf8("first"),
                                                                                         QObject::trUtf8("second"),
                                                                                         QObject::trUtf8("<third"),
                                                                                         QObject::trUtf8("fourth")} ),
                                          m_domM));
    m_fields.appendChild(createLongTextField(QString::fromUtf8("Comment"), QObject::trUtf8(""), m_domM));

    m_templateNode.appendChild(m_fields);
    return m_templateNode;
}

QDomNode XMLTemplate::createLetterNode()
{
    m_letterNode = m_domM.createElement(m_letterNodeName);

    m_letterNode.appendChild(m_domM.createTextNode(QObject::trUtf8("\n"
                                                                   "!Place!, !Date!\n\n"
                                                                   "Subject: !FirstName! !LastName!\n\n"
                                                                   "Dear !Title! !FirstName! !LastName!\n\n"
                                                                   "Blindtext\n\n"
                                                                   "Regards,\n\n"
                                                                   "!Signature!\n")));

    return m_letterNode;
}

QDomNode XMLTemplate::createShortTextField(const QString &name, const QString &defaultValue, QDomDocument& doc)
{
    auto n = doc.createElement(m_shortTextFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);
    n.appendChild(doc.createTextNode(defaultValue));
    return n;
}

QDomNode XMLTemplate::createLongTextField(const QString &name, const QString &defaultValue, QDomDocument &doc)
{
    auto n = doc.createElement(m_longTextFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);
    n.appendChild(doc.createTextNode(defaultValue));
    return n;
}

QDomNode XMLTemplate::createDateEditField(const QString &name, const QString &defaultValue, QDomDocument &doc)
{
    auto n = doc.createElement(m_dateEditFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);
    n.appendChild(doc.createTextNode(defaultValue));
    return n;
}

QDomNode XMLTemplate::createOneOfField(const QString &name, const QStringList &items, QDomDocument &doc)
{
    auto n = doc.createElement(m_oneOfTextFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);

    for (auto& i : items) {
        n.appendChild(createItem(i, doc));
    }

    return n;
}

QDomNode XMLTemplate::createAnyOfField(const QString &name, const QStringList &items, QDomDocument& doc)
{
    auto n = doc.createElement(m_anyOfTextFieldNodeName);
    n.setAttribute(m_fieldNameAttributeName, name);

    for (auto& i : items) {
        n.appendChild(createItem(i, doc));
    }

    return n;
}

QDomNode XMLTemplate::createItem(const QString &name, QDomDocument &doc)
{
    auto n = doc.createElement(m_itemNodeName);

    n.appendChild(doc.createTextNode(name));
    n.setAttribute(m_isCheckedAttributeName, m_falseConstant);

    return n;
}
