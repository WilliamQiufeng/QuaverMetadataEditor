#include "MainWindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QStringList>
#include <ui_MapListFieldEdit.h>

#include "MapListFieldEdit.h"
#include <QRegularExpressionValidator>

#include "WorkspaceState.h"

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
    ui->backgroundEdit->bind(ui->mapList, MapListModel::BackgroundFileRole);
    const auto imageMask = tr("Image Files (*.png *.jpg *.jpeg)");
    const auto audioMask = tr("Audio Files (*.mp3 *.wav *.ogg)");
    ui->backgroundEdit->chooseFileMask = imageMask;
    ui->bannerEdit->bind(ui->mapList, MapListModel::BannerFileRole);
    ui->bannerEdit->chooseFileMask = imageMask;
    ui->audioEdit->bind(ui->mapList, MapListModel::AudioFileRole);
    ui->audioEdit->chooseFileMask = audioMask;
    connect(ui->save, &QPushButton::clicked, this, &MainWindow::saveMaps);
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
    WorkspaceState::instance()->setCurrentFolder(mapsetDir);
    const auto entries = mapsetDir.entryInfoList({"*.qua"});
    qInfo() << "Going through " << mapsetDir;
    mapListModel->setList(entries);
    ui->mapList->selectAll();
}

void MainWindow::saveMaps() {
    auto* model = dynamic_cast<MapListModel *>(ui->mapList->model());
    for (const auto& item : model->items()) {
        YAML::Emitter out;
        out.SetIndent(2);
        // out.SetMapFormat(YAML::Flow);
        // out.SetSeqFormat(YAML::Flow);
        auto path = item.fileInfo.dir().filePath(item.fileInfo.fileName() + ".bak");
        item.map->serialise(out);
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        file.write(out.c_str());
        file.close();
    }
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openMapsetAction);
}
