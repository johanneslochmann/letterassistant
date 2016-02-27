#include "config.hxx"

#include "mainwindow.hxx"
#include "letterassistant.hxx"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(APPLICATION_VERSION);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QApplication::setApplicationDisplayName(QObject::tr("%1 V. %2")
                                            .arg(QCoreApplication::applicationName())
                                            .arg(QCoreApplication::applicationVersion()));
    LetterAssistant a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
