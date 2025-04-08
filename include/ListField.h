//
// Created by willi on 25-4-8.
//

#ifndef LISTFIELD_H
#define LISTFIELD_H

#include <QAbstractItemView>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ListField; }
QT_END_NAMESPACE

class ListField : public QWidget {
Q_OBJECT

public:
    explicit ListField(QWidget *parent = nullptr);
    ~ListField() override;
    void bind(QAbstractItemView *view, int dataRole);

private:
    Ui::ListField *ui;
};


#endif //LISTFIELD_H
