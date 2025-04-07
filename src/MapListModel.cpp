#include "MapListModel.h"

MapListModel::MapListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int MapListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return items.size();
}

QVariant MapListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= items.size())
        return {};

    const MapItem &mapItem = items.at(index.row());

    if (role == Qt::DisplayRole) {
        // Return the string to display in the view
        return QString("%1 (%2)").arg(mapItem.map->difficulty_name).arg(mapItem.fileInfo.fileName());
    }

    return {};
}

void MapListModel::setList(const QList<QFileInfo> &files) {
    beginResetModel();
    items.clear();
    for (const auto& file : files) {
        auto mapInfo = MapItem(file);
        items << mapInfo;
    }
    endResetModel();
}
