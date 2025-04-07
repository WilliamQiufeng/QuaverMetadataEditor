//
// Created by willi on 25-4-7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MapStringEdit.h" resolved

#include "MapStringEdit.h"

#include "QVariantHasher.h"
#include <QCompleter>

inline uint qHash(const QVariant &key, uint seed) noexcept {
    return QVariantHasher().hash(key);
}

MapStringEdit::MapStringEdit(QWidget *parent) : StringFieldEdit(parent), dataRole(0) {
}

MapStringEdit::~MapStringEdit() = default;

void MapStringEdit::bind(QAbstractItemView *view, const int dataRole) {
    this->view = view;
    this->dataRole = dataRole;
    connect(view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MapStringEdit::selectionChanged);
    connect(this, &MapStringEdit::editingFinished, this, &MapStringEdit::applyValue);
    updateText();
}

void MapStringEdit::makeCompleter(const QStringList &wordList) {
    const auto completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    setCompleter(completer);
}

void MapStringEdit::updateText() {
    if (view == nullptr) return;
    // Update placeholder text based on selected items
    QSet<QVariant> values;
    const auto selectedIndexes = view->selectionModel()->selectedIndexes();

    for (const QModelIndex &idx: selectedIndexes) {
        auto value = idx.data(dataRole);
        values.insert(value);
    }

    setReadOnly(values.isEmpty());

    if (values.isEmpty()) {
        setText("");
    } else if (values.size() == 1) {
        setText(values.begin()->toString());
    } else {
        setText(multipleValuesText);
    }
    QStringList wordList;
    for (const auto &item: values) {
        wordList.append(item.toString());
    }

    makeCompleter(wordList);
}

void MapStringEdit::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    updateText();
}

void MapStringEdit::applyValue() const {
    auto newText = text();
    if (newText == multipleValuesText) return;

    QAbstractItemModel *model = view->model();
    if (!model) return;

    const auto selectedIndexes = view->selectionModel()->selectedIndexes();
    for (const QModelIndex &idx: selectedIndexes) {
        model->setData(idx, newText, dataRole); // Update the specified role
    }
}

void MapStringEdit::focusInEvent(QFocusEvent *event) {
    StringFieldEdit::focusInEvent(event);
    completer()->complete();
}

QString MapStringEdit::multipleValuesText = tr("(Multiple Values)");
