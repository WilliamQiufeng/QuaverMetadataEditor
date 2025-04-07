#ifndef MAPLISTMODEL_H
#define MAPLISTMODEL_H

#include <QAbstractListModel>
#include "MapItem.h"

class MapListModel final : public QAbstractListModel {
    Q_OBJECT

public:
    explicit MapListModel(QObject *parent = nullptr);
    // Basic implementations for a list model
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    void setList(const QList<QFileInfo> &files);

private:
    QList<MapItem> items;
};

#endif // MAPLISTMODEL_H
