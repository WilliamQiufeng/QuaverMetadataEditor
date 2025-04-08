#include "QuaverMap.h"
#include "qtyaml.h"

QuaverMap::QuaverMap() {
}

void QuaverMap::load(const QString& str) {
    node = YAML::Load(str.toStdString());
    difficultyName = node["DifficultyName"].as<QString>("");
    tags = node["Tags"].as<QString>("");
    title = node["Title"].as<QString>("");
    source = node["Source"].as<QString>("");
    artist = node["Artist"].as<QString>("");
    creator = node["Creator"].as<QString>("");
    previewTime = node["SongPreviewTime"].as<int>(0);
    backgroundFile = node["BackgroundFile"].as<QString>("");
    bannerFile = node["BannerFile"].as<QString>("");
    audioFile = node["AudioFile"].as<QString>("");
}

void QuaverMap::serialise(YAML::Emitter &emitter) {
    node["DifficultyName"] = difficultyName;
    node["Tags"] = tags;
    node["Title"] = title;
    node["Source"] = source;
    node["Artist"] = artist;
    node["Creator"] = creator;
    node["SongPreviewTime"] = previewTime;
    node["BackgroundFile"] = backgroundFile;
    node["BannerFile"] = bannerFile;
    node["AudioFile"] = audioFile;
    emitter << node;
}
