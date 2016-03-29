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

protected:
    XMLTemplate();
    void initDom();

private:
    QString m_fileName;
    QString m_lastError;

    QDomDocument m_domM;

    int m_xmlIndent { 4 };
    QString m_rootNodeName { QString::fromUtf8("LetterAssistantTemplate") };
};
