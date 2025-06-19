#include "DialogueBox.hpp"
#include <SFML/Graphics.hpp>

DialogueBox::DialogueBox() {
    // Initialize default values
    box.setSize(sf::Vector2f(700, 150));
    box.setFillColor(sf::Color(0, 0, 0, 200));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::White);
    box.setPosition(50, 400);
    
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(70, 420);
    
    textSpeed = 50.0f; // characters per second
    elapsedTime = 0.0f;
    isComplete = false;
    fullText = "";
    currentText = "";
}

void DialogueBox::setFont(const sf::Font& dialogueFont) {
    font = dialogueFont;
    text.setFont(font);
}

void DialogueBox::setText(const std::string& dialogueText) {
    fullText = dialogueText;
    currentText = "";
    elapsedTime = 0.0f;
    isComplete = false;
}

void DialogueBox::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

void DialogueBox::setPosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x + 20, y + 20);
}

void DialogueBox::update(float deltaTime) {
    if (!isComplete && !fullText.empty()) {
        elapsedTime += deltaTime;
        
        int charactersToShow = static_cast<int>(elapsedTime * textSpeed);
        if (charactersToShow >= static_cast<int>(fullText.length())) {
            currentText = fullText;
            isComplete = true;
        } else {
            currentText = fullText.substr(0, charactersToShow);
        }
        
        text.setString(currentText);
    }
}

void DialogueBox::render(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}