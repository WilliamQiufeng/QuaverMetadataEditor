//
// Created by willi on 25-4-8.
//

#include "../include/ListEditButton.h"

#include <QTimer>

#include "MainWindow.h"
#include "MapListFieldEdit.h"

ListEditButton::ListEditButton(QWidget *parent) : QPushButton(parent) {
}

ListEditButton::~ListEditButton() = default;

void ListEditButton::bind(MapStringEdit *mapStringEdit, QAbstractItemView *mapList) {
    this->mapStringEdit = mapStringEdit;
    this->mapList = mapList;
    connect(mapList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ListEditButton::updateEnabled);
    connect(this, &QPushButton::clicked, this, &ListEditButton::openListEditDialog);
    connect(mapStringEdit, &MapStringEdit::fieldValueChanged, this, &ListEditButton::updateEnabled);
    updateEnabled();
}

void ListEditButton::updateEnabled() {
    setEnabled(
        !mapList->selectionModel()->selectedRows().isEmpty() &&
        mapStringEdit->text() != mapStringEdit->multipleValuesText);
}

void ListEditButton::openListEditDialog() {
    auto dialog = MapListFieldEdit(this);
    dialog.setMapStringEdit(mapStringEdit);
    dialog.exec();
}
