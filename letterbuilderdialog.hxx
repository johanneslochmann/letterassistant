#pragma once

#include <QDialog>

class QDialogButtonBox;
class QScrollArea;

class TextTemplate;
class TextTemplateElementsWidget;

class LetterBuilderDialog : public QDialog
{
    Q_OBJECT
public:
    LetterBuilderDialog(QWidget* p, const QString& templateText);

private:
    TextTemplate* m_template;

    QDialogButtonBox* m_buttons;
    QScrollArea* m_scrollArea;
    TextTemplateElementsWidget* m_elementsW;
};
