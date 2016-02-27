#pragma once

#include <QWidget>

class TextTemplate;

class TextTemplateElementsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextTemplateElementsWidget(QWidget *parent, TextTemplate* textTemplate);

signals:

public slots:

protected:
    void createWidgets();

private:
    TextTemplate* m_tmpl;
};
