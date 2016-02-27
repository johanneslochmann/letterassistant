#pragma once

#include <QDialog>

class QDialogButtonBox;
class QScrollArea;

class LetterBuilderDialog : public QDialog
{
    Q_OBJECT
public:
    LetterBuilderDialog(QWidget* p, const QString& templateText);

private:
    QString m_templateTxt;

    QDialogButtonBox* m_buttons;
    QScrollArea* m_scrollArea;
};
