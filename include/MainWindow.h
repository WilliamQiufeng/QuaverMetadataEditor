#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MapListModel.h"
#include <QSettings>

#include "MapStringEdit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu{};
    QAction *openMapsetAction{};
    void openListEditDialog(MapStringEdit *mapStringEdit);

    void createMenus();
    void createActions();
    void openMapset();
    MapListModel* mapListModel;
    QSettings *settings;
};
#endif // MAINWINDOW_H
