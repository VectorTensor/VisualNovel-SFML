#include "ChoiceUI.hpp"

ChoiceUI::ChoiceUI() {
    spacing = 60.0f;
    selectedChoice = -1;
}

void ChoiceUI::setFont(const sf::Font& choiceFont) {
    font = choiceFont;
    // Update existing choices with new font
    for (auto& choice : choices) {
        choice.setFont(font);
    }
}

void ChoiceUI::addChoice(const std::string& text) {
    Button choice(font, text);
    choices.push_back(choice);
    
    // Position the new choice
    float yPos = 300.0f + (choices.size() - 1) * spacing;
    choice.setPosition(100.0f, yPos);
    choices.back() = choice;
}

void ChoiceUI::clearChoices() {
    choices.clear();
    selectedChoice = -1;
}

void ChoiceUI::setPosition(float x, float y) {
    for (size_t i = 0; i < choices.size(); ++i) {
        choices[i].setPosition(x, y + i * spacing);
    }
}

void ChoiceUI::update(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    selectedChoice = -1;
    for (size_t i = 0; i < choices.size(); ++i) {
        if (choices[i].isClicked(mousePosF)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                selectedChoice = static_cast<int>(i);
            }
        }
    }
}

void ChoiceUI::render(sf::RenderWindow& window) {
    for (auto& choice : choices) {
        choice.render(window);
    }
}

int ChoiceUI::getSelectedChoice() const {
    return selectedChoice;
}

std::string ChoiceUI::getChoiceText(int index) const {
    if (index >= 0 && index < static_cast<int>(choices.size())) {
        // Need to get the text from the Button
        // Since Button doesn't have a getText() method, we'll return a placeholder
        // You may need to modify the Button class to add a getText() method

        // For now, return a placeholder
        return choices[index].getText();
    }
    return "";
}
