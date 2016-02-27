#include "texttemplate.hxx"

#include <QDebug>
#include <QMessageBox>
#include <QApplication>

TextTemplate::TextTemplate(QObject *parent, const QString &txt)
    : QObject(parent), m_txt(txt)
{
    parseText();
}

void TextTemplate::parseText()
{
    QStringList rows = m_txt.split("\n");

    for (auto& row : rows) {
        if (row.startsWith("%%%")) {
            QStringList rowData = trimFields(row.replace("%%%", "").split(':'));

            if (rowData.size() != 3) {
                QMessageBox::warning(qApp->activeWindow(), tr("Error on Template File"),
                                     tr("Template row does not consist of 3 parts separated by \":\": %1").arg(row));
            } else {

                auto e = std::make_shared<TemplateElement>(rowData.at(0), rowData.at(1), rowData.at(2).split("|"));
                m_elements.push_back(e);
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
