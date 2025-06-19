#ifndef DIALOGUEBOX_HPP
#define DIALOGUEBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

class DialogueBox {
public:
    DialogueBox();
    void setFont(const sf::Font& font);
    void setText(const std::string& text);
    void setCharacterSize(unsigned int size);
    void setPosition(float x, float y);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    std::string fullText;
    std::string currentText;
    float textSpeed;
    float elapsedTime;
    bool isComplete;
};

#endif // DIALOGUEBOX_HPP