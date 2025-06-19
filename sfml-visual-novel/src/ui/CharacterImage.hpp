#ifndef CHARACTERIMAGE_HPP
#define CHARACTERIMAGE_HPP

#include <SFML/Graphics.hpp>
#include <string>

class CharacterImage {
public:
    CharacterImage();
    bool loadFromFile(const std::string& filename);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void render(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string currentImage;
};

#endif // CHARACTERIMAGE_HPP