#pragma once

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
