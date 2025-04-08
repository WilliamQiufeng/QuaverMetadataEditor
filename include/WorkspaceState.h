//
// Created by willi on 25-4-8.
//

#ifndef WORKSPACESTATE_H
#define WORKSPACESTATE_H


#include <QObject>
#include <QString>
#include <QDir>

class WorkspaceState : public QObject {
    Q_OBJECT
    Q_PROPERTY(QDir currentFolder READ currentFolder WRITE setCurrentFolder NOTIFY currentFolderChanged)

public:
    static WorkspaceState *instance();

    explicit WorkspaceState(QObject *parent = nullptr);

    [[nodiscard]] QDir currentFolder() const;

    void setCurrentFolder(const QDir &folder);

signals:
    void currentFolderChanged(const QDir &folder);

private:
    QDir m_currentFolder;
};

#endif //WORKSPACESTATE_H
