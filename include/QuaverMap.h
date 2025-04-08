#ifndef QUAVERMAP_H
#define QUAVERMAP_H

#include <QString>
#include <string>
#include <yaml-cpp/yaml.h>

class QuaverMap {
private:
    YAML::Node node;

public:
    QString difficultyName;
    QString title;
    QString tags;
    QString source;
    int previewTime;
    QString artist;
    QString creator;
    QString audioFile;
    QString backgroundFile;
    QString bannerFile;

    QuaverMap();

    void load(const QString& str);

    void serialise(YAML::Emitter &emitter);
};

#endif // QUAVERMAP_H
