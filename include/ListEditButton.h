//
// Created by willi on 25-4-8.
//

#ifndef LISTEDITBUTTON_H
#define LISTEDITBUTTON_H
#include <QListView>
#include <QPushButton>

#include "MapStringEdit.h"


class ListEditButton : public QPushButton {
public:
    explicit ListEditButton(QWidget *parent = nullptr);

    ~ListEditButton();

    void bind(MapStringEdit *mapStringEdit, QAbstractItemView *mapList);

private:
    MapStringEdit *mapStringEdit = nullptr;
    QAbstractItemView *mapList = nullptr;

private slots:
    void updateEnabled();

    void openListEditDialog();
};


#endif //LISTEDITBUTTON_H
