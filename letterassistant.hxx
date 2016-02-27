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
    void createLetter();
    void aboutProgram();

public slots:
    void onAboutProgram();

protected:
    void initActions();

private:
    QAction* m_createLetterAction;
    QAction* m_quitAction;
    QAction* m_aboutProgramAction;
    QAction* m_aboutQtAction;
};
