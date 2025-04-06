#ifndef MAPITEM_H
#define MAPITEM_H
#include <QFileInfo>
#include "quavermap.h"

class MapItem
{
public:
    MapItem(const QFileInfo& fileInfo);
    QFileInfo fileInfo;
    QuaverMap* map;
};

#endif // MAPITEM_H
