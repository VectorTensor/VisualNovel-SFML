#ifndef CHOICEUI_HPP
#define CHOICEUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.hpp"

class ChoiceUI {
public:
    ChoiceUI();
    void setFont(const sf::Font& font);
    void addChoice(const std::string& text);
    void clearChoices();
    void setPosition(float x, float y);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    int getSelectedChoice() const;
    std::string getChoiceText(int index) const;

private:
    std::vector<Button> choices;
    sf::Font font;
    float spacing;
    int selectedChoice;
};

#endif // CHOICEUI_HPP