#include "quavermap.h"

QuaverMap::QuaverMap() {

}

void QuaverMap::load(std::string str) {
    node = YAML::Load(str);
    difficulty_name = node["DifficultyName"].as<std::string>();
    tags = node["Tags"].as<std::string>();
    title = node["Title"].as<std::string>();
}

void QuaverMap::serialise(YAML::Emitter& emitter) {
    node["DifficultyName"] = difficulty_name;
    node["Tags"] = tags;
    node["Title"] = title;
    emitter << node;
}
