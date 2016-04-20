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

#pragma once

#include <QApplication>

#include <QAction>
#include <QFont>

class XMLTemplate;

class LetterAssistant : public QApplication
{
    Q_OBJECT
public:
    LetterAssistant(int& argc, char** argv);
    virtual ~LetterAssistant();

    static LetterAssistant* get();

    QAction* createTemplateAction() const { return m_createTemplateAction; }
    QAction* openTemplateAction() const { return m_openTemplateAction; }
    QAction* closeTemplateAction() const { return m_closeTemplateAction; }
    QAction* saveTemplateAction() const { return m_saveTemplateAction; }
    QAction* saveTemplateAsAction() const { return m_saveTemplateAsAction; }

    QAction* createLetterAction() const { return m_createLetterAction; }
    QAction* quitAction() const { return m_quitAction; }
    QAction* aboutProgramAction() const { return m_aboutProgramAction; }
    QAction* aboutQtAction() const { return m_aboutQtAction; }

    QAction* activateNextSubWindowAction() { return m_activateNextSubWindowAction; }
    QAction* activatePreviousSubWindowAction() { return m_activatePreviousSubWindowAction; }
    QAction* cascadeSubWindowsAction() { return m_cascadeSubWindowsAction; }
    QAction* closeActiveSubWindowAction() { return m_closeActiveSubWindowAction; }
    QAction* closeAllSubWindowsAction() { return m_closeAllSubWindowsAction; }
    QAction* tileSubWindowsAction() { return m_tileSubWindowsAction; }

    QAction* increaseFontSizeAction() { return m_increaseFontSizeAction; }
    QAction* decreaseFontSizeAction() { return m_decreaseFontSizeAction; }

    QFont createDefaultFont();

signals:
    void aboutProgram();

    void createTemplate();
    void openTemplate();
    void closeTemplate();
    void saveTemplate();
    void saveTemplateAs();

    void activateNextSubWindow();
    void activatePreviousSubWindow();
    void cascadeSubWindows();
    void closeActiveSubWindow();
    void closeAllSubWindows();
    void tileSubWindows();

    void templateLoaded(XMLTemplate* t);

public slots:
    void onAboutProgram();
    void onCreateLetter();

    void increaseFontSize();
    void decreaseFontSize();

    void newXmlTemplate();

protected:
    void initActions();

    void initTemplateActions();
    void initMdiActions();
    void initLetterActions();
    void initFileActions();
    void initSettingsActions();
    void initHelpActions();

private:
    QAction* m_createTemplateAction;
    QAction* m_openTemplateAction;
    QAction* m_closeTemplateAction;
    QAction* m_saveTemplateAction;
    QAction* m_saveTemplateAsAction;

    QAction* m_activateNextSubWindowAction;
    QAction* m_activatePreviousSubWindowAction;
    QAction* m_cascadeSubWindowsAction;
    QAction* m_closeActiveSubWindowAction;
    QAction* m_closeAllSubWindowsAction;
    QAction* m_tileSubWindowsAction;

    QAction* m_createLetterAction;
    QAction* m_quitAction;
    QAction* m_aboutProgramAction;
    QAction* m_aboutQtAction;

    QAction* m_increaseFontSizeAction;
    QAction* m_decreaseFontSizeAction;

    QList<XMLTemplate*> m_openTemplates;
};
