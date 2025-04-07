//
// Created by willi on 25-4-7.
//

#ifndef MAPSTRINGEDIT_H
#define MAPSTRINGEDIT_H

#include <QAbstractItemView>

#include "StringFieldEdit.h"

class MapStringEdit : public StringFieldEdit {
    Q_OBJECT

public:
    explicit MapStringEdit(QWidget *parent = nullptr);

    ~MapStringEdit() override;

    void bind(QAbstractItemView *view, int dataRole);

    void makeCompleter(const QStringList &wordList);

    void updateText();

    QString multipleValuesText;
signals:
    void fieldValueChanged(QString content);
private slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
public slots:
    void applyValue();

private:
    QAbstractItemView *view = nullptr;
    int dataRole;

    void focusInEvent(QFocusEvent *event) override;
};


#endif //MAPSTRINGEDIT_H
