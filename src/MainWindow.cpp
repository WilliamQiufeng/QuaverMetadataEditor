#include "MainWindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QStringList>
#include <ui_MapListFieldEdit.h>

#include "MapListFieldEdit.h"
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), settings(new QSettings()) {
    ui->setupUi(this);
    createActions();
    createMenus();
    mapListModel = new MapListModel();
    ui->mapList->setModel(mapListModel);
    ui->mapList->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->titleEdit->bind(ui->mapList, MapListModel::TitleRole);
    ui->tagsEdit->bind(ui->mapList, MapListModel::TagsRole);
    ui->artistEdit->bind(ui->mapList, MapListModel::ArtistRole);
    ui->sourceEdit->bind(ui->mapList, MapListModel::SourceRole);
    ui->creatorEdit->bind(ui->mapList, MapListModel::CreatorRole);
    ui->previewTimeEdit->bind(ui->mapList, MapListModel::PreviewTimeRole);
    ui->previewTimeEdit->setValidator(new QIntValidator());
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::createActions() {
    openMapsetAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
                                   tr("&Open"), this);
    openMapsetAction->setShortcuts(QKeySequence::Open);
    openMapsetAction->setStatusTip(tr("Open a mapset"));
    connect(openMapsetAction, &QAction::triggered, this, &MainWindow::openMapset);
}

void MainWindow::openMapset() {
    const auto lastDir = settings->value("LastMapsetDir", QDir::homePath()).toString();
    const auto mapsetPath = QFileDialog::getExistingDirectory(this, tr("Open Mapset"), lastDir,
                                                              QFileDialog::ShowDirsOnly);
    if (mapsetPath.isEmpty() || mapsetPath.isNull()) return;
    settings->setValue("LastMapsetDir", mapsetPath);

    const auto mapsetDir = QDir(mapsetPath);
    const auto entries = mapsetDir.entryInfoList({"*.qua"});
    qInfo() << "Going through " << mapsetDir;
    mapListModel->setList(entries);
    ui->mapList->selectAll();
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openMapsetAction);
}
