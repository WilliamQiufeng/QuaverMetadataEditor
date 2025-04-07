#ifndef QUAVERMAP_H
#define QUAVERMAP_H

#include <string>
#include <yaml-cpp/yaml.h>

class QuaverMap
{
private:
    YAML::Node node;
public:
    std::string difficulty_name;
    std::string title;
    std::string tags;
    QuaverMap();

    void load(const std::string &str);

    void serialise(YAML::Emitter& emitter);
};

#endif // QUAVERMAP_H
