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
#include <xmltemplate.hxx>

LetterAssistant::LetterAssistant(int &argc, char **argv)
    : QApplication(argc, argv)
{
    initActions();
}

LetterAssistant::~LetterAssistant()
{
    for (auto& t : m_openTemplates) {
        delete t;
    }

    m_openTemplates.clear();
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

void LetterAssistant::newXmlTemplate()
{
    auto fname = QFileDialog::getSaveFileName(activeWindow(),
                                              trUtf8("Create New Template"),
                                              QDir::currentPath(),
                                              trUtf8("XML Files, *xml"));

    if (fname.isEmpty()) {
        return;
    }

    XMLTemplate* t = XMLTemplate::createNewTemplate(fname);
    Q_CHECK_PTR(t);

    if (t->hasError()) {
        QMessageBox::critical(activeWindow(),
                              trUtf8("Failed to create template file"),
                              trUtf8("Failed to create template file:\n%1").arg(t->lastError()));
        delete t;
        return;
    }

    m_openTemplates.append(t);
    emit templateLoaded(t);
}

void LetterAssistant::initTemplateActions()
{
    m_createTemplateAction = new QAction(trUtf8("New Template..."), this);
    connect(m_createTemplateAction, &QAction::triggered, this, &LetterAssistant::newXmlTemplate);

    m_closeTemplateAction = new QAction(trUtf8("Close Template"), this);
    connect(m_closeTemplateAction, &QAction::triggered, this, &LetterAssistant::closeTemplate);

    m_openTemplateAction = new QAction(trUtf8("Open Template..."), this);
    connect(m_openTemplateAction, &QAction::triggered, this, &LetterAssistant::closeTemplate);

    m_saveTemplateAction = new QAction(trUtf8("Save Template"), this);
    connect(m_saveTemplateAction, &QAction::triggered, this, &LetterAssistant::saveTemplate);

    m_saveTemplateAsAction = new QAction(trUtf8("Save Template As..."), this);
    connect(m_saveTemplateAsAction, &QAction::triggered, this, &LetterAssistant::saveTemplateAs);
}

void LetterAssistant::initMdiActions()
{
    m_activateNextSubWindowAction = new QAction(trUtf8("Activate Next Window"), this);
    connect(m_activateNextSubWindowAction, &QAction::triggered, this, &LetterAssistant::activateNextSubWindow);

    m_activatePreviousSubWindowAction = new QAction(trUtf8("Activate Previous Window"), this);
    connect(m_activatePreviousSubWindowAction, &QAction::triggered, this, &LetterAssistant::activatePreviousSubWindow);

    m_cascadeSubWindowsAction = new QAction(trUtf8("Cascade Windows"), this);
    connect(m_cascadeSubWindowsAction, &QAction::triggered, this, &LetterAssistant::cascadeSubWindows);

    m_closeActiveSubWindowAction = new QAction(trUtf8("Close Active Window"), this);
    connect(m_closeActiveSubWindowAction, &QAction::triggered, this, &LetterAssistant::closeActiveSubWindow);

    m_closeAllSubWindowsAction = new QAction(trUtf8("Close All Windows"), this);
    connect(m_closeAllSubWindowsAction, &QAction::triggered, this, &LetterAssistant::closeAllSubWindows);

    m_tileSubWindowsAction = new QAction(trUtf8("Tile Windows"), this);
    connect(m_tileSubWindowsAction, &QAction::triggered, this, &LetterAssistant::tileSubWindows);
}

void LetterAssistant::initLetterActions()
{
    m_createLetterAction = new QAction(trUtf8("&New Letter..."), this);
    m_createLetterAction->setShortcut(QKeySequence::New);
    connect(m_createLetterAction, &QAction::triggered, this, &LetterAssistant::onCreateLetter);
}

void LetterAssistant::initFileActions()
{
    m_quitAction = new QAction(trUtf8("&Quit"), this);
    m_quitAction->setShortcut(QKeySequence::Quit);
    connect(m_quitAction, &QAction::triggered, this, &LetterAssistant::quit);
}

void LetterAssistant::initHelpActions()
{
    m_aboutProgramAction = new QAction(trUtf8("&About this program..."), this);
    connect(m_aboutProgramAction, &QAction::triggered, this, &LetterAssistant::onAboutProgram);

    m_aboutQtAction = new QAction(trUtf8("&About Qt..."), this);
    connect(m_aboutQtAction, &QAction::triggered, this, &LetterAssistant::aboutQt);
}

void LetterAssistant::initActions()
{
    initTemplateActions();
    initMdiActions();
    initLetterActions();
    initFileActions();
    initHelpActions();
}
