#include "aboutprogramdialog.hxx"

#include <QLabel>
#include <QApplication>

#include "ui_aboutprogramdialog.h"

AboutProgramDialog::AboutProgramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutProgramDialog)
{
    ui->setupUi(this);

    ui->m_lbl->setText(tr("<p>This is %1.</p>"
                          "<p>Mail <a href=\"mailto:info@johanneslochmann.net\">info@johanneslochmann.net</a> for more information.</p>").arg(QApplication::applicationDisplayName()));
}

AboutProgramDialog::~AboutProgramDialog()
{
    delete ui;
}
