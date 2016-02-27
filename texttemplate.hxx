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

signals:

public slots:

protected:
    void parseText();

    QStringList trimFields(const QStringList& data);

private:
    QString m_txt;

    TemplateElementSPtrVector m_elements;
};
