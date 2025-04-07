//
// Created by willi on 25-4-7.
//

#include "MapStringEdit.h"
#include <QKeyEvent>
#include <QKeySequence>
#include <QTimer>

StringFieldEdit::StringFieldEdit(QWidget *parent) {
    cancelAction = new QAction(tr("Cancel"), this);
    cancelAction->setShortcut(QKeySequence::Cancel);
    cancelAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    addAction(cancelAction);
    connect(cancelAction, &QAction::triggered, this, &StringFieldEdit::cancelEdit);
    connect(this, &StringFieldEdit::editingFinished, this, &StringFieldEdit::clearFocusAfterEdit);
}

StringFieldEdit::~StringFieldEdit() = default;

void StringFieldEdit::cancelEdit() {
    setText(textBeforeEdit);
    deselect();
    clearFocus();
    emit editCancelled();
}

void StringFieldEdit::focusInEvent(QFocusEvent *event) {
    QLineEdit::focusInEvent(event);
    // Then select the text by a single shot timer, so that everything will
    // be processed before (calling selectAll() directly won't work)
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
    textBeforeEdit = text();
}

void StringFieldEdit::clearFocusAfterEdit() {
    clearFocus();
}
