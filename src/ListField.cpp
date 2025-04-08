//
// Created by willi on 25-4-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ListField.h" resolved

#include "../include/ListField.h"

#include "MapListModel.h"
#include "ui_ListField.h"


ListField::ListField(QWidget *parent) :
    QWidget(parent), ui(new Ui::ListField) {
    ui->setupUi(this);
}

ListField::~ListField() {
    delete ui;
}

void ListField::bind(QAbstractItemView *view, int dataRole) {
    ui->stringEdit->bind(view, dataRole);
    ui->listEdit->bind(ui->stringEdit, view);
}
