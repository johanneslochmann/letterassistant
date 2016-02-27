#include "letterassistant.hxx"

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

}

void LetterAssistant::initActions()
{
    m_createLetterAction = new QAction(tr("&New Letter..."), this);
    m_createLetterAction->setShortcut(QKeySequence::New);
    connect(m_createLetterAction, &QAction::triggered, this, &LetterAssistant::createLetter);

    m_quitAction = new QAction(tr("&Quit"), this);
    m_quitAction->setShortcut(QKeySequence::New);
    connect(m_quitAction, &QAction::triggered, this, &LetterAssistant::quit);

    m_aboutProgramAction = new QAction(tr("&About this program..."), this);
    connect(m_aboutProgramAction, &QAction::triggered, this, &LetterAssistant::onAboutProgram);

    m_aboutQtAction = new QAction(tr("&About Qt..."), this);
    connect(m_aboutQtAction, &QAction::triggered, this, &LetterAssistant::aboutQt);
}
