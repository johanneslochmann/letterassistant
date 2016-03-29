#pragma once

#include <QString>
#include <QDomDocument>

class XMLTemplate
{
public:
    virtual ~XMLTemplate();

    QString fileName() const;
    void setFileName(const QString &fileName);

    bool loadFromFile(const QString& fname);
    bool saveToFile(const QString& fname = "");
    QString lastError() const;
    bool hasError() const;

    static XMLTemplate *createNewTemplate(const QString& fname);
    static XMLTemplate *openTemplate(const QString& fname);

    QString documentToString() const;

protected:
    XMLTemplate();
    void initDom();

private:
    QString m_fileName;
    QString m_lastError;

    QDomDocument m_domM;

    int m_xmlIndent { 4 };
    QString m_rootNodeName { QString::fromUtf8("LetterAssistantTemplate") };
    QString m_templateNodeName { QString::fromUtf8("Template") };
    QString m_letterNodeName { QString::fromUtf8("Letter") };
    QString m_configNodeName { QString::fromUtf8("Config") };
    QString m_dateFormatNodeName { QString::fromUtf8("DateFormat") };
    QString m_columnsInCheckBoxGroupsNodeName { QString::fromUtf8("ColumnsInCheckBoxGroup") };
    QString m_columnsInRadioButtonGroupsNodeName { QString::fromUtf8("ColumnsInRadioButtonGroup") };

    QDomNode m_rootNode;
    QDomNode m_templateNode;
    QDomNode m_configNode;
    QDomNode m_dateFormatNode;
    QDomNode m_columnsInCheckBoxGroups;
    QDomNode m_columnsInRadioButtonBoxGroups;

    QDomNode m_letterNode;
};
