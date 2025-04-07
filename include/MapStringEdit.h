//
// Created by willi on 25-4-7.
//

#ifndef MAPSTRINGEDIT_H
#define MAPSTRINGEDIT_H

#include "StringFieldEdit.h"

class MapStringEdit : public StringFieldEdit {
    Q_OBJECT

public:
    explicit MapStringEdit(QWidget *parent = nullptr);

    ~MapStringEdit() override;

private:
};


#endif //MAPSTRINGEDIT_H
