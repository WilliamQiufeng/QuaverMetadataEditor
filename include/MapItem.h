#ifndef MAPITEM_H
#define MAPITEM_H
#include <QFileInfo>
#include "QuaverMap.h"

class MapItem
{
public:
    explicit MapItem(const QFileInfo &fileInfo);

    QFileInfo fileInfo;
    QuaverMap* map;
};

#endif // MAPITEM_H
