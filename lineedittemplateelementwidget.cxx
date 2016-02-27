#include "lineedittemplateelementwidget.hxx"

#include <QLayout>

LineEditTemplateElementWidget::LineEditTemplateElementWidget(QWidget *p, TemplateElementSPtr e)
    : TemplateElementWidget(p, e)
{
    setLayout(new QVBoxLayout(this));
    m_w = new QLineEdit(e->options().join(""), this);
    layout()->addWidget(m_w);

    connect(m_w, &QLineEdit::textChanged, this, &LineEditTemplateElementWidget::onValueChanged);
}

void LineEditTemplateElementWidget::onValueChanged(const QString &v)
{
    element()->setSingleValue(v);
}
