#pragma once

#include <QObject>
#include <QList>

#include <templateelement.hxx>

class TextTemplate : public QObject
{
    Q_OBJECT
public:
    explicit TextTemplate(QObject *parent, const QString& txt);

    const TemplateElementSPtrVector& elements() const { return m_elements; }

    QString replaceKeywordsWithValues();
    QString dateFormat() const { return m_dateFormat; }
    int columnsInRadioButtonGroups() const { return m_columnsInRadioButtonGroups; }
    int columnsInCheckBoxButtonGroups() const { return m_columnsInCheckBoxButtonGroups; }

signals:

public slots:

protected:
    void parseText();

    QStringList trimFields(const QStringList& data);

private:
    QString m_txt;
    QString m_dateFormat { "dd/mm/yyyy" };
    int m_columnsInRadioButtonGroups { 3 };
    int m_columnsInCheckBoxButtonGroups { 1 };

    TemplateElementSPtrVector m_elements;
};
