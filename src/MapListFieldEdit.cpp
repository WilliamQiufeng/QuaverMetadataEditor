//
// Created by willi on 25-4-7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MapListFieldEdit.h" resolved

#include "MapListFieldEdit.h"
#include "ui_MapListFieldEdit.h"
#include <QStringListModel>

MapListFieldEdit::MapListFieldEdit(QWidget *parent) :
    QDialog(parent), ui(new Ui::MapListFieldEdit) {
    ui->setupUi(this);
    ui->list->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

MapListFieldEdit::~MapListFieldEdit() {
    delete ui;
}

void MapListFieldEdit::setMapStringEdit(MapStringEdit *edit) {
    mapStringEdit = edit;
    auto items = mapStringEdit->text().split(',', Qt::SkipEmptyParts);
    for (auto& item : items) {
        item = item.trimmed();
    }
    auto *model = new QStringListModel(items);
    ui->list->setModel(model);
}
