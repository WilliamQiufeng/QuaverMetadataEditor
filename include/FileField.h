//
// Created by willi on 25-4-8.
//

#ifndef FILEFIELD_H
#define FILEFIELD_H

#include <qabstractitemview.h>
#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class FileField;
}

QT_END_NAMESPACE

class FileField : public QWidget {
    Q_OBJECT

public:
    explicit FileField(QWidget *parent = nullptr);

    ~FileField() override;

    void bind(QAbstractItemView *view, int dataRole);

    QString chooseFileMask;

private:
    Ui::FileField *ui;

private slots:
    void chooseFile();
};


#endif //FILEFIELD_H
