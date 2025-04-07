//
// Created by willi on 25-4-7.
//

#ifndef MAPLISTFIELDEDIT_H
#define MAPLISTFIELDEDIT_H

#include <QDialog>

#include "MapStringEdit.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class MapListFieldEdit;
}

QT_END_NAMESPACE

class MapListFieldEdit : public QDialog {
    Q_OBJECT

public:
    explicit MapListFieldEdit(QWidget *parent = nullptr);

    ~MapListFieldEdit() override;

private:
    Ui::MapListFieldEdit *ui;
    MapStringEdit *mapStringEdit;

public:
    void setMapStringEdit(MapStringEdit *edit);
};


#endif //MAPLISTFIELDEDIT_H
