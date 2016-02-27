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

class LetterAssistant : public QApplication
{
    Q_OBJECT
public:
    LetterAssistant(int& argc, char** argv);

    static LetterAssistant* get();

    QAction* createLetterAction() const { return m_createLetterAction; }
    QAction* quitAction() const { return m_quitAction; }
    QAction* aboutProgramAction() const { return m_aboutProgramAction; }
    QAction* aboutQtAction() const { return m_aboutQtAction; }

signals:
    void aboutProgram();

public slots:
    void onAboutProgram();
    void onCreateLetter();

protected:
    void initActions();

private:
    QAction* m_createLetterAction;
    QAction* m_quitAction;
    QAction* m_aboutProgramAction;
    QAction* m_aboutQtAction;
};
