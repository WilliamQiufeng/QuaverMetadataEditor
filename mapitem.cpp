#include "mapitem.h"

MapItem::MapItem(const QFileInfo& fileInfo) : fileInfo(QFileInfo(fileInfo)), map(new QuaverMap) {
    auto file = new QFile(fileInfo.filePath());
    if (!file->open(QFile::ReadOnly | QFile::Text))
        return;
    auto content = file->readAll();
    file->close();
    qInfo() << content.toStdString().substr(0, 100);
    map->load(content.toStdString());
}
