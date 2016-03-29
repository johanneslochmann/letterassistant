#pragma once

#include <QTextEdit>

class XMLTemplate;

class XMLEditor : public QTextEdit
{
    Q_OBJECT
public:
    XMLEditor(QWidget* p);
    virtual ~XMLEditor();

public slots:
    void setXMLTemplate(XMLTemplate* t);

    void onCustomContextMenuRequested(const QPoint& pos);

    void createShortTextField();
    void createLongTextField();
    void createDateField();
    void createOneOfField();
    void createAnyOfField();
    void insertKey();
    void updateTemplate();

    void validate();
    void save();

    void onCursorPositionChanged(const QTextCursor& c);

protected:
    void createActions();
    void insertTextAtCursorPosition(const QString& txt);

    bool xmlIsValid();
    bool implUpdateTemplate();
    bool implSave();

private:
    XMLTemplate* m_t { nullptr };

    QAction* m_createShortTextField;
    QAction* m_createLongTextField;
    QAction* m_createDateField;
    QAction* m_createOneOfField;
    QAction* m_createAnyOfField;
    QAction* m_insertKey;
    QAction* m_updateTemplate;
    QAction* m_save;

    QAction* m_validate;

    QTextCursor m_cursor;
};
