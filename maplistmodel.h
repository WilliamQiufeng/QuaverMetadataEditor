#ifndef MAPLISTMODEL_H
#define MAPLISTMODEL_H

#include <QAbstractListModel>
#include "mapitem.h"

class MapListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MapListModel(QObject *parent = nullptr);
    // Basic implementations for a list model
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    void setList(QList<QFileInfo> files);
private:
    QList<MapItem> items;
};

#endif // MAPLISTMODEL_H
