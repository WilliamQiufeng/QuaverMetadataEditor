#include "MapListModel.h"

MapListModel::MapListModel(QObject *parent)
    : QAbstractListModel{parent} {
}

int MapListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return items.size();
}

QVariant MapListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= items.size())
        return {};

    const MapItem &mapItem = items.at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            // Return the string to display in the view
            return QString("%1 (%2)").arg(mapItem.map->difficulty_name).arg(mapItem.fileInfo.fileName());
        case TitleRole:
            return QString::fromStdString(mapItem.map->title);
        case TagsRole:
            return QString::fromStdString(mapItem.map->tags);
        default:
            return {};
    }
}

bool MapListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= items.size())
        return false;
    MapItem &mapItem = items[index.row()];
    switch (role) {
        case TitleRole:
            mapItem.map->title = value.toString().toStdString();
            break;
        case TagsRole:
            mapItem.map->tags = value.toString().toStdString();
            break;
        default:
            return false;
    }
    emit dataChanged(index, index, {role});
    return true;
}

void MapListModel::setList(const QList<QFileInfo> &files) {
    beginResetModel();
    items.clear();
    for (const auto &file: files) {
        auto mapInfo = MapItem(file);
        items << mapInfo;
    }
    endResetModel();
}
