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
                                              tr("Select Letter Template"),
                                              QDir::currentPath(),
                                              tr("Latex Files *tex"));

    if (fname.isEmpty()) {
        return;
    }

    QFile f(fname);
    if (!f.open(QFile::ReadOnly)) {
        QMessageBox::critical(activeWindow(), tr("Failed to open file"),
                              tr("<p>Could not open file <b>%1</b> for reading:</p><p>%2</p>")
                              .arg(fname)
                              .arg(f.errorString()));
        return;
    }

    QString txt = f.readAll();
    f.close();

    auto dlg = new LetterBuilderDialog(activeWindow(), txt);
    dlg->showMaximized();
}

void LetterAssistant::initActions()
{
    m_createLetterAction = new QAction(tr("&New Letter..."), this);
    m_createLetterAction->setShortcut(QKeySequence::New);
    connect(m_createLetterAction, &QAction::triggered, this, &LetterAssistant::onCreateLetter);

    m_quitAction = new QAction(tr("&Quit"), this);
    m_quitAction->setShortcut(QKeySequence::Quit);
    connect(m_quitAction, &QAction::triggered, this, &LetterAssistant::quit);

    m_aboutProgramAction = new QAction(tr("&About this program..."), this);
    connect(m_aboutProgramAction, &QAction::triggered, this, &LetterAssistant::onAboutProgram);

    m_aboutQtAction = new QAction(tr("&About Qt..."), this);
    connect(m_aboutQtAction, &QAction::triggered, this, &LetterAssistant::aboutQt);
}
