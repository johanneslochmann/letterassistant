#include "letterbuilderdialog.hxx"

#include <QLayout>
#include <QScrollArea>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "texttemplate.hxx"
#include "texttemplateelementswidget.hxx"

LetterBuilderDialog::LetterBuilderDialog(QWidget *p, const QString &templateText)
    : QDialog(p)
{
    m_template = new TextTemplate(this, templateText);

    setLayout(new QVBoxLayout(this));

    m_scrollArea = new QScrollArea(this);
    m_elementsW = new TextTemplateElementsWidget(this, m_template);
    m_scrollArea->setWidget(m_elementsW);

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, this);
    connect(m_buttons, &QDialogButtonBox::accepted, this, &LetterBuilderDialog::accept);
    connect(m_buttons, &QDialogButtonBox::rejected, this, &LetterBuilderDialog::reject);

    layout()->addWidget(m_scrollArea);
    layout()->addWidget(m_buttons);
}

void LetterBuilderDialog::accept()
{
    QMessageBox::information(this, tr("Result"), m_template->replaceKeywordsWithValues());

    done(QDialog::Accepted);
}
