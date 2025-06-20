#ifndef DIALOGUEBOX_HPP
#define DIALOGUEBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

class DialogueBox {
public:
    DialogueBox();
    void setFont(const sf::Font& font);
    void setText(const std::string& text);
    void setSpeaker(const std::string& speaker);
    void setCharacterSize(unsigned int size);
    void setPosition(float x, float y);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    bool isDialogueComplete() const;
    void skipToEnd();

private:
    sf::RectangleShape box;
    sf::RectangleShape speakerBox;
    sf::Text text;
    sf::Text speakerText;
    sf::Font font;
    std::string fullText;
    std::string currentText;
    std::string speakerName;
    float textSpeed;
    float elapsedTime;
    bool isComplete;
};

#endif // DIALOGUEBOX_HPP