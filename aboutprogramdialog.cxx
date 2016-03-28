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

#include "aboutprogramdialog.hxx"

#include <QLabel>
#include <QApplication>

#include "ui_aboutprogramdialog.h"

#include "config.hxx"

AboutProgramDialog::AboutProgramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutProgramDialog)
{
    ui->setupUi(this);

    ui->m_lbl->setText(trUtf8("<p>This is %1.</p>"
                              "<p>Visit <a href=\"%2\">%2</a> for more information</p>"
                              "<p>The author Johannes Lochmann can be reached via the above website or by sending an email to <a href=\"mailto:%3\">%3</a>.</p>")
                       .arg(QApplication::applicationDisplayName())
                       .arg(APPLICATION_URL)
                       .arg(AUTHOR_EMAIL));
}

AboutProgramDialog::~AboutProgramDialog()
{
    delete ui;
}
