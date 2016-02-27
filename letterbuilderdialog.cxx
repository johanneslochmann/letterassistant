#include "letterbuilderdialog.hxx"

#include <QLayout>
#include <QScrollArea>
#include <QDialogButtonBox>

LetterBuilderDialog::LetterBuilderDialog(QWidget *p, const QString &templateText)
    : QDialog(p), m_templateTxt(templateText)
{
    setLayout(new QVBoxLayout(this));

    m_scrollArea = new QScrollArea(this);

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, this);
    connect(m_buttons, &QDialogButtonBox::accepted, this, &LetterBuilderDialog::accept);
    connect(m_buttons, &QDialogButtonBox::rejected, this, &LetterBuilderDialog::reject);

    layout()->addWidget(m_scrollArea);
    layout()->addWidget(m_buttons);
}
