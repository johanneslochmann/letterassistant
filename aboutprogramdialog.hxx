#ifndef ABOUTPROGRAMDIALOG_HXX
#define ABOUTPROGRAMDIALOG_HXX

#include <QDialog>

namespace Ui {
class AboutProgramDialog;
}

class AboutProgramDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutProgramDialog(QWidget *parent = 0);
    ~AboutProgramDialog();

private:
    Ui::AboutProgramDialog *ui;
};

#endif // ABOUTPROGRAMDIALOG_HXX
