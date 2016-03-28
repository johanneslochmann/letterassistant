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

#include "letterassistant.hxx"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

#include "aboutprogramdialog.hxx"
#include "letterbuilderdialog.hxx"

LetterAssistant::LetterAssistant(int &argc, char **argv)
    : QApplication(argc, argv)
{
    initActions();
}

LetterAssistant *LetterAssistant::get()
{
    return qobject_cast<LetterAssistant*>(qApp);
}

void LetterAssistant::onAboutProgram()
{
    auto dlg = new AboutProgramDialog(activeWindow());
    dlg->exec();
}

void LetterAssistant::onCreateLetter()
{
    auto fname = QFileDialog::getOpenFileName(activeWindow(),
                                              trUtf8("Select Letter Template"),
                                              QDir::currentPath(),
                                              trUtf8("Text Files (*.tex *.txt)"));

    if (fname.isEmpty()) {
        return;
    }

    QFile f(fname);
    if (!f.open(QFile::ReadOnly)) {
        QMessageBox::critical(activeWindow(), trUtf8("Failed to open file"),
                              trUtf8("<p>Could not open file <b>%1</b> for reading:</p><p>%2</p>")
                              .arg(fname)
                              .arg(f.errorString()));
        return;
    }

    QString txt = QString::fromUtf8(f.readAll());
    f.close();

    auto dlg = new LetterBuilderDialog(activeWindow(), txt);
    dlg->showMaximized();
}

void LetterAssistant::initActions()
{
    m_createLetterAction = new QAction(trUtf8("&New Letter..."), this);
    m_createLetterAction->setShortcut(QKeySequence::New);
    connect(m_createLetterAction, &QAction::triggered, this, &LetterAssistant::onCreateLetter);

    m_quitAction = new QAction(trUtf8("&Quit"), this);
    m_quitAction->setShortcut(QKeySequence::Quit);
    connect(m_quitAction, &QAction::triggered, this, &LetterAssistant::quit);

    m_aboutProgramAction = new QAction(trUtf8("&About this program..."), this);
    connect(m_aboutProgramAction, &QAction::triggered, this, &LetterAssistant::onAboutProgram);

    m_aboutQtAction = new QAction(trUtf8("&About Qt..."), this);
    connect(m_aboutQtAction, &QAction::triggered, this, &LetterAssistant::aboutQt);
}
