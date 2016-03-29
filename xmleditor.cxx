#include "xmleditor.hxx"

#include <QMenu>
#include <QAction>
#include <QTextDocument>
#include <QMessageBox>
#include <QInputDialog>

#include <xmltemplate.hxx>

XMLEditor::XMLEditor(QWidget *p)
    : QTextEdit(p)
{
    createActions();

    setAcceptRichText(false);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &XMLEditor::customContextMenuRequested, this, &XMLEditor::onCustomContextMenuRequested);
    connect(document(), &QTextDocument::cursorPositionChanged, this, &XMLEditor::onCursorPositionChanged);
}

XMLEditor::~XMLEditor()
{
}

void XMLEditor::setXMLTemplate(XMLTemplate *t)
{
    m_t = t;

    if (!m_t) {
        clear();
        return;
    }

    setPlainText(m_t->documentToString());
}

void XMLEditor::onCustomContextMenuRequested(const QPoint &pos)
{
    auto menu = createStandardContextMenu(mapToGlobal(pos));

    menu->addSeparator();
    menu->addAction(m_createShortTextField);
    menu->addAction(m_createLongTextField);
    menu->addAction(m_createDateField);
    menu->addAction(m_createOneOfField);
    menu->addAction(m_createAnyOfField);
    menu->addSeparator();
    menu->addAction(m_insertKey);
    menu->addSeparator();
    menu->addAction(m_validate);
    menu->addAction(m_updateTemplate);
    menu->addSeparator();
    menu->addAction(m_save);

    menu->exec(mapToGlobal(pos));
}

void XMLEditor::createShortTextField()
{
    insertTextAtCursorPosition(m_t->createShortTextFieldText(trUtf8("NewKey"), QString::fromUtf8("")));
}

void XMLEditor::createLongTextField()
{
    insertTextAtCursorPosition(m_t->createLongTextFieldText(trUtf8("NewKey")));
}

void XMLEditor::createDateField()
{
    insertTextAtCursorPosition(m_t->createDateEditFieldText(trUtf8("NewKey")));
}

void XMLEditor::createOneOfField()
{
    insertTextAtCursorPosition(m_t->createOneOfFieldText(trUtf8("NewKey")));
}

void XMLEditor::createAnyOfField()
{
    insertTextAtCursorPosition(m_t->createAnyOfFieldText(trUtf8("NewKey")));
}

void XMLEditor::insertKey()
{
    bool ok { false };

    auto txt = QInputDialog::getItem(this,
                                     trUtf8("Select Key"),
                                     trUtf8("Key"),
                                     m_t->availableFieldNames(),
                                     0,
                                     true,
                                     &ok);

    if (ok && !txt.isEmpty()) {
        insertTextAtCursorPosition(QString::fromUtf8("!%1!").arg(txt));
    }
}

void XMLEditor::updateTemplate()
{
    (void) implUpdateTemplate();
}

void XMLEditor::validate()
{
    if (xmlIsValid()) {
        QMessageBox::information(this,
                                 trUtf8("Validation OK"),
                                 trUtf8("XML Structure is valid."));
    }
}

void XMLEditor::save()
{
    if (!implSave()) {
        QMessageBox::critical(this,
                              trUtf8("Failed to save"),
                              trUtf8("Failed to save template"));
    }
}

void XMLEditor::onCursorPositionChanged(const QTextCursor &c)
{
    m_cursor = c;
}

void XMLEditor::createActions()
{
    m_createShortTextField = new QAction(trUtf8("Create Short Text Field"), this);
    m_createLongTextField = new QAction(trUtf8("Create Long Text Field"), this);
    m_createDateField = new QAction(trUtf8("Create Date Field"), this);
    m_createOneOfField = new QAction(trUtf8("Create OneOf Field"), this);
    m_createAnyOfField = new QAction(trUtf8("Create AnyOf Field"), this);
    m_insertKey = new QAction(trUtf8("Insert Key..."), this);
    m_updateTemplate = new QAction(trUtf8("Update Template"), this);
    m_save = new QAction(trUtf8("Save"), this);

    m_validate = new QAction(trUtf8("Validate"), this);

    connect(m_createShortTextField, &QAction::triggered, this, &XMLEditor::createShortTextField);
    connect(m_createLongTextField, &QAction::triggered, this, &XMLEditor::createLongTextField);
    connect(m_createDateField, &QAction::triggered, this, &XMLEditor::createDateField);
    connect(m_createOneOfField, &QAction::triggered, this, &XMLEditor::createOneOfField);
    connect(m_createAnyOfField, &QAction::triggered, this, &XMLEditor::createAnyOfField);
    connect(m_insertKey, &QAction::triggered, this, &XMLEditor::insertKey);
    connect(m_updateTemplate, &QAction::triggered, this, &XMLEditor::updateTemplate);
    connect(m_save, &QAction::triggered, this, &XMLEditor::save);

    connect(m_validate, &QAction::triggered, this, &XMLEditor::validate);
}

void XMLEditor::insertTextAtCursorPosition(const QString &txt)
{
    m_cursor.clearSelection();
    m_cursor.insertText(txt);
}

bool XMLEditor::xmlIsValid()
{
    QDomDocument doc;

    QString m_errMsg;
    int m_errLine { 0 };
    int m_errCol { 0 };
    auto validationResult = doc.setContent(toPlainText(), &m_errMsg, &m_errLine, &m_errCol);

    if (!validationResult) {
        QMessageBox::warning(this,
                             trUtf8("Validation failed"),
                             trUtf8("Validation failed at Line %1 Column %2: %3 ")
                             .arg(m_errLine)
                             .arg(m_errCol)
                             .arg(m_errMsg));

    }

    return validationResult;
}

bool XMLEditor::implUpdateTemplate()
{
    if (!xmlIsValid()) {
        return false;
    }

    if (!m_t->setPlainText(toPlainText().toUtf8())) {
        QMessageBox::critical(this,
                              trUtf8("Template Update Failed"),
                              trUtf8("Failed to update template because it contains errors."));
    }

    return true;
}

bool XMLEditor::implSave()
{
    return (implUpdateTemplate() && m_t->saveToFile());
}
