#pragma once
#include <list>
#include <map>
#include <string>

#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class AudioManager {
public:
    void loadSound(const std::string& name, const std::string& path);
    void playSound(const std::string& name, float volume);
    void startMusic(const std::string& path, float volume);
    void update(float dt);
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::list<sf::Sound> activeSounds;

    std::unique_ptr<sf::Music> currentMusic;
    std::unique_ptr<sf::Music> fadingMusic;
    float fadeSpeed = 50.f;
    float musicTargetVolume = 20.f;
};

