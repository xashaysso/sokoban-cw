#include "AudioManager.h"

#include "SFML/Audio/SoundBuffer.hpp"

void AudioManager::startMusic(const std::string &path, const float volume) {
    if (currentMusic) {
        fadingMusic = std::move(currentMusic);
    }
    currentMusic = std::make_unique<sf::Music>();
    if (currentMusic->openFromFile(path)) {
        currentMusic->setLooping(true);
        currentMusic->setVolume(volume);
        currentMusic->play();
        musicTargetVolume = volume;
    }
}

void AudioManager::update(const float dt) {
    if (fadingMusic) {
        float vol = fadingMusic->getVolume();
        vol -= fadeSpeed * dt;
        if (vol <= 0.0f) {
            fadingMusic->stop();
            fadingMusic.reset();
        } else {
            fadingMusic->setVolume(vol);
        }
    }
}

void AudioManager::loadSound(const std::string &name, const std::string &path) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path)) {
        soundBuffers[name] = buffer;
    }
}

void AudioManager::playSound(const std::string &name, float volume) {
    if (soundBuffers.find(name) != soundBuffers.end()) {
        activeSounds.emplace_back(soundBuffers[name]);
        activeSounds.back().setVolume(volume);
        activeSounds.back().play();
    }
}
