#pragma once

#include <QString>
#include <QDomDocument>
#include <QDate>

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

    bool setPlainText(const QString& txt);

    QString documentToString() const;

    QString createShortTextFieldText(const QString& name, const QString& defaultValue = "");
    QString createLongTextFieldText(const QString& name, const QString& defaultValue = "");
    QString createDateEditFieldText(const QString& name, const QString& defaultValue = "");
    QString createOneOfFieldText(const QString& name);
    QString createAnyOfFieldText(const QString& name);

    QStringList availableFieldNames();
    bool isDirty() const { return m_isDirty; }

protected:
    XMLTemplate();
    void initDom();

    QDomNode createConfigNode();
    QDomNode createTemplateNode();
    QDomNode createLetterNode();

    QDomNode createShortTextField(const QString& name, const QString& defaultValue, QDomDocument &doc);
    QDomNode createLongTextField(const QString& name, const QString& defaultValue, QDomDocument &doc);
    QDomNode createDateEditField(const QString& name, const QString& defaultValue, QDomDocument &doc);
    QDomNode createOneOfField(const QString& name, const QStringList& items, QDomDocument &doc);
    QDomNode createAnyOfField(const QString& name, const QStringList& items, QDomDocument &doc);
    QDomNode createItem(const QString& name, QDomDocument &doc);

    void extractNameAttributeValues(const QString& nodeName, QStringList& buf);
    bool parseDom();
    bool parseConfig();
    bool parseTemplate();
    bool parseLetter();

    void parseShortTextFieldNode(QDomNode& n);
    void parseLongTextFieldNode(QDomNode& n);
    void parseDateEditFieldNode(QDomNode& n);
    void parseOneOfFieldNode(QDomNode& n);
    void parseAnyOfFieldNode(QDomNode& n);

private:
    QStringList m_parsingErrors;
    QString m_fileName;
    QString m_lastError;
    bool m_isDirty { false };

    QDomDocument m_domM;

    int m_xmlIndent { 4 };
    QString m_defaultDateFormat { QString::fromUtf8("dd/MM/yyyy") };
    QString m_trueConstant { QString::fromUtf8("true") };
    QString m_falseConstant { QString::fromUtf8("false") };

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
    QString m_oneOfFieldNodeName { QString::fromUtf8("OneOf") };
    QString m_anyOfFieldNodeName { QString::fromUtf8("AnyOf") };
    QString m_itemNodeName { QString::fromUtf8("Item") };
    QString m_isCheckedAttributeName { QString::fromUtf8("isChecked") };

    QString m_fieldNameAttributeName { QString::fromUtf8("name") };

    QDomNode m_rootNode;
    QDomNode m_templateNode;
    QDomNode m_dateFormatNode;
    QDomNode m_columnsInCheckBoxGroups;
    QDomNode m_columnsInRadioButtonBoxGroups;
    QDomNode m_fields;

    QDomNode m_letterNode;
};
