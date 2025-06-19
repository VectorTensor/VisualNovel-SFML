#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    void loadTexture(const std::string& name, const std::string& filePath);
    sf::Texture& getTexture(const std::string& name);

    void loadFont(const std::string& name, const std::string& filePath);
    sf::Font& getFont(const std::string& name);

    void loadSound(const std::string& name, const std::string& filePath);
    sf::SoundBuffer& getSound(const std::string& name);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> sounds;
};

#endif // RESOURCE_MANAGER_HPP