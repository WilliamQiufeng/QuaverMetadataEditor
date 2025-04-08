#ifndef MAPLISTMODEL_H
#define MAPLISTMODEL_H

#include <QAbstractListModel>
#include "MapItem.h"

class MapListModel final : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        ArtistRole,
        TagsRole,
        SourceRole,
        DifficultyNameRole,
        CreatorRole,
        PreviewTimeRole,
        BackgroundFileRole,
        BannerFileRole,
        AudioFileRole
    };

    explicit MapListModel(QObject *parent = nullptr);

    // Basic implementations for a list model
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    void setList(const QList<QFileInfo> &files);

    QList<MapItem> items();

private:
    QList<MapItem> m_items;
};

#endif // MAPLISTMODEL_H
