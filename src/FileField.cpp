//
// Created by willi on 25-4-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FileField.h" resolved

#include "../include/FileField.h"

#include <QFileDialog>

#include "ui_FileField.h"
#include "WorkspaceState.h"
#include <QFileInfo>

FileField::FileField(QWidget *parent) : QWidget(parent), ui(new Ui::FileField) {
    ui->setupUi(this);
    connect(ui->chooseFile, &QPushButton::clicked, this, &FileField::chooseFile);
}

FileField::~FileField() {
    delete ui;
}

void FileField::bind(QAbstractItemView *view, int dataRole) {
    ui->pathEdit->bind(view, dataRole);
}

void FileField::chooseFile() {
    const auto mapsetPath = QFileDialog::getOpenFileName(this, tr("Select File"),
                                                         WorkspaceState::instance()->currentFolder().absolutePath(),
                                                         chooseFileMask);
    if (mapsetPath.isEmpty() || mapsetPath.isNull()) return;

    ui->pathEdit->setText(WorkspaceState::instance()->currentFolder().relativeFilePath(mapsetPath));
    ui->pathEdit->applyValue();
}
