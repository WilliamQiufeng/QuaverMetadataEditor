//
// Created by willi on 25-4-7.
//

#ifndef QVARIANTHASHER_H
#define QVARIANTHASHER_H
#include <QBuffer>

class QVariantHasher {
public:
    QVariantHasher() : buff(&bb), ds(&buff) {
        bb.reserve(1000);
        buff.open(QIODevice::WriteOnly);
    }
    uint hash(const QVariant & v) {
        buff.seek(0);
        ds << v;
        return qHashBits(bb.constData(), buff.pos());
    }
private:
    QByteArray bb;
    QBuffer buff;
    QDataStream ds;
};
#endif //QVARIANTHASHER_H
