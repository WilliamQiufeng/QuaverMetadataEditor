#include "MapListModel.h"

MapListModel::MapListModel(QObject *parent)
    : QAbstractListModel{parent} {
}

int MapListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant MapListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_items.size())
        return {};

    const MapItem &mapItem = m_items.at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            // Return the string to display in the view
            return QString("%1 (%2)").arg(mapItem.map->difficultyName).arg(mapItem.fileInfo.fileName());
        case TitleRole:
            return mapItem.map->title;
        case TagsRole:
            return mapItem.map->tags;
        case ArtistRole:
            return mapItem.map->artist;
        case SourceRole:
            return mapItem.map->source;
        case CreatorRole:
            return mapItem.map->creator;
        case PreviewTimeRole:
            return mapItem.map->previewTime;
        case BackgroundFileRole:
            return mapItem.map->backgroundFile;
        case BannerFileRole:
            return mapItem.map->bannerFile;
        case AudioFileRole:
            return mapItem.map->audioFile;
        default:
            return {};
    }
}

bool MapListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= m_items.size())
        return false;
    MapItem &mapItem = m_items[index.row()];
    switch (role) {
        case TitleRole:
            mapItem.map->title = value.toString();
            break;
        case TagsRole:
            mapItem.map->tags = value.toString();
            break;
        case ArtistRole:
            mapItem.map->artist = value.toString();
            break;
        case SourceRole:
            mapItem.map->source = value.toString();
            break;
        case CreatorRole:
            mapItem.map->creator = value.toString();
            break;
        case PreviewTimeRole:
            mapItem.map->previewTime = value.toInt();
            break;
        case BackgroundFileRole:
            mapItem.map->backgroundFile = value.toString();
            break;
        case BannerFileRole:
            mapItem.map->bannerFile = value.toString();
            break;
        case AudioFileRole:
            mapItem.map->audioFile = value.toString();
            break;
        default:
            return false;
    }
    emit dataChanged(index, index, {role});
    return true;
}

void MapListModel::setList(const QList<QFileInfo> &files) {
    beginResetModel();
    m_items.clear();
    for (const auto &file: files) {
        auto mapInfo = MapItem(file);
        m_items << mapInfo;
    }
    endResetModel();
}

QList<MapItem> MapListModel::items() {
    return m_items;
}
