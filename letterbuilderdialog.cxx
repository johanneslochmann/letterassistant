#include "letterbuilderdialog.hxx"

#include <QLayout>
#include <QScrollArea>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

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

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel|QDialogButtonBox::Save, this);
    connect(m_buttons->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &LetterBuilderDialog::accept);
    connect(m_buttons, &QDialogButtonBox::rejected, this, &LetterBuilderDialog::reject);
    connect(m_buttons->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &LetterBuilderDialog::save);

    layout()->addWidget(m_scrollArea);
    layout()->addWidget(m_buttons);
}

void LetterBuilderDialog::accept()
{
    if (!doSave()) {
        return;
    }

    done(QDialog::Accepted);
}

void LetterBuilderDialog::save()
{
    (void) doSave();
}

void LetterBuilderDialog::reject()
{
    if (QMessageBox::Yes == QMessageBox::warning(this, tr("Abort?"), tr("Abort and loose changes?"),
                                                 QMessageBox::Yes|QMessageBox::No)) {
        done(QDialog::Rejected);
    }
}

bool LetterBuilderDialog::doSave()
{
    // dialog warns user if file already exists
    auto fname = QFileDialog::getSaveFileName(this,
                                              tr("&Save File As..."),
                                              QDir::currentPath(),
                                              tr("All Files *"));

    if (fname.isEmpty()) {
        return false;
    }

    QFile f(fname);
    if (!f.open(QFile::Truncate | QFile::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Failed to save"), tr("Failed to save data to file %1: %2").arg(fname).arg(f.errorString()));
        return false;
    }

    QTextStream ostrm(&f);
    ostrm << m_template->replaceKeywordsWithValues();

    ostrm.flush();
    f.flush();
    f.close();

    return true;
}
