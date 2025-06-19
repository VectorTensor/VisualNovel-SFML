#include "CharacterImage.hpp"

CharacterImage::CharacterImage() {
    currentImage = "";
}

bool CharacterImage::loadFromFile(const std::string& filename) {
    if (texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
        currentImage = filename;
        return true;
    }
    return false;
}

void CharacterImage::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void CharacterImage::setScale(float x, float y) {
    sprite.setScale(x, y);
}

void CharacterImage::render(sf::RenderWindow& window) {
    window.draw(sprite);
}