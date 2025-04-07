//
// Created by willi on 25-4-7.
//

#ifndef STRINGFIELDEDIT_H
#define STRINGFIELDEDIT_H

#include <QLineEdit>
#include <QEvent>

class StringFieldEdit : public QLineEdit {
  Q_OBJECT

public:
  explicit StringFieldEdit(QWidget *parent = nullptr);

  ~StringFieldEdit() override;

  void cancelEdit();

signals:
  void editCancelled();

private:
  QString textBeforeEdit;
  QAction *cancelAction;

protected:
  void focusInEvent(QFocusEvent *event) override;

private slots:
  void clearFocusAfterEdit();
};


#endif //STRINGFIELDEDIT_H
