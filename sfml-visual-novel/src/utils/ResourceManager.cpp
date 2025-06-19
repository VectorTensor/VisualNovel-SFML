#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <stdexcept>

ResourceManager::ResourceManager() {
    // Constructor
}

ResourceManager::~ResourceManager() {
    // Destructor - SFML resources clean up automatically
}

void ResourceManager::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    textures[name] = texture;
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it == textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}

void ResourceManager::loadFont(const std::string& name, const std::string& filePath) {
    sf::Font font;
    if (!font.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load font: " + filePath);
    }
    fonts[name] = font;
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    auto it = fonts.find(name);
    if (it == fonts.end()) {
        throw std::runtime_error("Font not found: " + name);
    }
    return it->second;
}

void ResourceManager::loadSound(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer sound;
    if (!sound.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load sound: " + filePath);
    }
    sounds[name] = sound;
}

sf::SoundBuffer& ResourceManager::getSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it == sounds.end()) {
        throw std::runtime_error("Sound not found: " + name);
    }
    return it->second;
}