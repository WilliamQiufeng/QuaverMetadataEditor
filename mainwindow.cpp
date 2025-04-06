#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();
    mapListModel = new MapListModel();
    ui->mapList->setModel(mapListModel);
    ui->mapList->setSelectionMode(QAbstractItemView::MultiSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::createActions()
{
    openMapsetAction = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
                         tr("&Open"), this);
    openMapsetAction->setShortcuts(QKeySequence::Open);
    openMapsetAction->setStatusTip(tr("Open a mapset"));
    connect(openMapsetAction, &QAction::triggered, this, &MainWindow::openMapset);
}

void MainWindow::openMapset()
{
    auto mapsetPath = QFileDialog::getExistingDirectory(this, tr("Open Mapset"), "/home", QFileDialog::ShowDirsOnly);
    auto mapsetDir = QDir(mapsetPath);
    auto entries = mapsetDir.entryInfoList({"*.qua"});
    auto list = QStringList();
    qInfo() << "Going through " << mapsetDir;
    mapListModel->setList(entries);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openMapsetAction);
}

