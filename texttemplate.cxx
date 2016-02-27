#include "texttemplate.hxx"

#include <QDebug>
#include <QMessageBox>
#include <QApplication>

TextTemplate::TextTemplate(QObject *parent, const QString &txt)
    : QObject(parent), m_txt(txt)
{
    parseText();
}

QString TextTemplate::replaceKeywordsWithValues()
{
    QString buf = m_txt;

    for (auto& e : elements()) {
        buf.replace(QString("!%1!").arg(e->name()), e->values().join(" "));
    }

    return buf;
}

void TextTemplate::parseText()
{
    QStringList rows = m_txt.split("\n");

    for (auto& row : rows) {
        if (row.startsWith("%%%")) {
            QStringList rowData = trimFields(row.replace("%%%", "").split(':'));

            if (rowData.size() != 3) {
                if (rowData.at(0) == "DateFormat") {
                    m_dateFormat = rowData.at(1);
                } else if (rowData.at(0) == "ColumnsInRadioButtonGroups") {
                    m_columnsInRadioButtonGroups = rowData.at(1).toInt();
                } else if (rowData.at(0) == "ColumnsInCheckBoxButtonGroups") {
                    m_columnsInCheckBoxButtonGroups = rowData.at(1).toInt();
                } else {
                    QMessageBox::warning(qApp->activeWindow(), tr("Warning"), tr("Unknown configuration row: %1").arg(row));
                }
            } else {
                auto options = rowData.at(2);

                if (options.contains("|")) {
                    auto e = std::make_shared<TemplateElement>(this, rowData.at(0), rowData.at(1), options.split("|"));
                    m_elements.push_back(e);
                } else {
                    auto e = std::make_shared<TemplateElement>(this, rowData.at(0), rowData.at(1), QStringList(options));
                    m_elements.push_back(e);
                }

            }
        }
    }
}

QStringList TextTemplate::trimFields(const QStringList &data)
{
    QStringList r;

    for (const auto& d : data) {
        r.append(d.trimmed());
    }

    return r;
}
