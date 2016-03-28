/*
 * (c) 2016  Johannes Lochmann
 * Email:    jolo@johanneslochmann.net
 * Website:  http://www.johanneslochmann.net/letterassistant
 *
 * This file is part of LetterAssistant.
 *
 * LetterAssistant is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LetterAssistant is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LetterAssistant.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    if (QMessageBox::Yes == QMessageBox::warning(this,
                                                 trUtf8("Abort?"),
                                                 trUtf8("Abort and loose changes?"),
                                                 QMessageBox::Yes|QMessageBox::No)) {
        done(QDialog::Rejected);
    }
}

bool LetterBuilderDialog::doSave()
{
    // dialog warns user if file already exists
    auto fname = QFileDialog::getSaveFileName(this,
                                              trUtf8("&Save File As..."),
                                              QDir::currentPath(),
                                              trUtf8("Text Files (*.tex *txt)"));

    if (fname.isEmpty()) {
        return false;
    }

    QFile f(fname);
    if (!f.open(QFile::Truncate | QFile::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this,
                              trUtf8("Failed to save"),
                              trUtf8("Failed to save data to file %1: %2").arg(fname).arg(f.errorString()));
        return false;
    }

    QTextStream ostrm(&f);
    ostrm << m_template->replaceKeywordsWithValues();

    ostrm.flush();
    f.flush();
    f.close();

    return true;
}
