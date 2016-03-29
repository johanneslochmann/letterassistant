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

    QDomNode& createConfigNode();
    QDomNode& createTemplateNode();

    QDomNode createShortTextField(const QString& name, const QString& defaultValue);
    QDomNode createLongTextField(const QString& name, const QString& defaultValue);
    QDomNode createDateEditField(const QString& name, const QString& defaultValue);

private:
    QString m_fileName;
    QString m_lastError;

    QDomDocument m_domM;

    int m_xmlIndent { 4 };
    QString m_defaultDateFormat { QString::fromUtf8("dd/MM/yyyy") };

    QString m_rootNodeName { QString::fromUtf8("LetterAssistantTemplate") };
    QString m_templateNodeName { QString::fromUtf8("Template") };
    QString m_letterNodeName { QString::fromUtf8("Letter") };
    QString m_configNodeName { QString::fromUtf8("Config") };
    QString m_dateFormatNodeName { QString::fromUtf8("DateFormat") };
    QString m_columnsInCheckBoxGroupsNodeName { QString::fromUtf8("ColumnsInCheckBoxGroup") };
    QString m_columnsInRadioButtonGroupsNodeName { QString::fromUtf8("ColumnsInRadioButtonGroup") };
    QString m_fieldsNodeName { QString::fromUtf8("Fields") };
    QString m_shortTextFieldNodeName { QString::fromUtf8("ShortText") };
    QString m_longTextFieldNodeName { QString::fromUtf8("LongText") };
    QString m_dateEditFieldNodeName { QString::fromUtf8("DateEdit") };
    QString m_oneOfTextFieldNodeName { QString::fromUtf8("OneOf") };
    QString m_anyOfTextFieldNodeName { QString::fromUtf8("AnyOf") };
    QString m_itemNodeName { QString::fromUtf8("Item") };

    QString m_fieldNameAttributeName { QString::fromUtf8("name") };

    QDomNode m_rootNode;
    QDomNode m_templateNode;
    QDomNode m_configNode;
    QDomNode m_dateFormatNode;
    QDomNode m_columnsInCheckBoxGroups;
    QDomNode m_columnsInRadioButtonBoxGroups;
    QDomNode m_fields;

    QDomNode m_letterNode;
};
