//
// Created by willi on 25-4-8.
//

#include "WorkspaceState.h"

Q_GLOBAL_STATIC(WorkspaceState, globalWorkspaceState)

WorkspaceState* WorkspaceState::instance() {
    return globalWorkspaceState();
}

WorkspaceState::WorkspaceState(QObject *parent) : QObject(parent) {}

QDir WorkspaceState::currentFolder() const {
    return m_currentFolder;
}

void WorkspaceState::setCurrentFolder(const QDir &folder) {
    if (m_currentFolder != folder) {
        m_currentFolder = folder;
        emit currentFolderChanged(folder);
    }
}