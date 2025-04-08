//
// Created by willi on 25-4-7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MapListFieldEdit.h" resolved

#include "MapListFieldEdit.h"
#include "ui_MapListFieldEdit.h"
#include <QStringListModel>
#include <QTimer>

MapListFieldEdit::MapListFieldEdit(QWidget *parent) : QDialog(parent), ui(new Ui::MapListFieldEdit) {
    ui->setupUi(this);
    ui->list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->list->setEditTriggers(
        QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    connect(ui->add, &QPushButton::clicked, this, &MapListFieldEdit::add);
    connect(ui->remove, &QPushButton::clicked, this, &MapListFieldEdit::remove);
    connect(ui->apply, &QPushButton::clicked, this, &MapListFieldEdit::apply);
    connect(ui->cancel, &QPushButton::clicked, this, &MapListFieldEdit::cancel);
    connect(ui->list->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&] {
        ui->remove->setDisabled(ui->list->selectionModel()->selectedRows().isEmpty());
    });
}

MapListFieldEdit::~MapListFieldEdit() {
    delete ui;
}

void MapListFieldEdit::add() {
    auto *model = ui->list->model();
    model->insertRow(model->rowCount());
    const auto index = model->index(model->rowCount() - 1, 0);
    model->setData(index, "");
    ui->list->edit(index);
}

void MapListFieldEdit::remove() {
    auto *model = ui->list->model();
    QModelIndexList indicesToRemove = ui->list->selectionModel()->selectedIndexes();
    std::sort(indicesToRemove.begin(), indicesToRemove.end(), std::greater<>());
    for (const auto &index: indicesToRemove) {
        int row = index.row();
        model->removeRow(row);
    }

    // Select the row nearest to the last selected row
    const int nextSelectedRow = indicesToRemove.front().row() - indicesToRemove.size();
    QTimer::singleShot(0, [&] {
        ui->list->selectionModel()->select(
            model->index(nextSelectedRow, 0),
            QItemSelectionModel::Select);
    });
}

void MapListFieldEdit::apply() {
    QString result = "";
    auto model = ui->list->model();
    const int row_count = model->rowCount();
    for (int i = 0; i < row_count; i++) {
        // We trim the tags so they are well-formed (separated by a comma followed by a trailing space)
        auto component = model->data(model->index(i, 0), Qt::DisplayRole).toString();
        result += component.trimmed();
        if (i != row_count - 1) {
            result += ", ";
        }
    }
    if (mapStringEdit != nullptr) {
        mapStringEdit->setText(result);
        mapStringEdit->applyValue();
    }
    accept();
}

void MapListFieldEdit::cancel() {
    reject();
}

void MapListFieldEdit::setMapStringEdit(MapStringEdit *edit) {
    mapStringEdit = edit;
    const auto text = mapStringEdit->text();
    auto items = text.split(',', Qt::SkipEmptyParts);
    for (auto &item: items) {
        item = item.trimmed();
    }
    auto *model = new QStringListModel(items);
    ui->list->setModel(model);
}
