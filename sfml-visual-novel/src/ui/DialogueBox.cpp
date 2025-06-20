#include "DialogueBox.hpp"
#include <SFML/Graphics.hpp>

DialogueBox::DialogueBox() {
    // Initialize default values
    box.setSize(sf::Vector2f(700, 150));
    box.setFillColor(sf::Color(0, 0, 0, 200));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::White);
    box.setPosition(50, 400);
    
    // Set up speaker box
    speakerBox.setSize(sf::Vector2f(200, 40));
    speakerBox.setFillColor(sf::Color(50, 50, 120, 220));
    speakerBox.setOutlineThickness(2);
    speakerBox.setOutlineColor(sf::Color::White);

    // Set up text display
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(70, 420);
    
    // Set up speaker text
    speakerText.setCharacterSize(20);
    speakerText.setFillColor(sf::Color::White);

    textSpeed = 50.0f; // characters per second
    elapsedTime = 0.0f;
    isComplete = false;
    fullText = "";
    currentText = "";
    speakerName = "";
}

void DialogueBox::setFont(const sf::Font& dialogueFont) {
    font = dialogueFont;
    text.setFont(font);
    speakerText.setFont(font);
}

void DialogueBox::setText(const std::string& dialogueText) {
    fullText = dialogueText;
    currentText = "";
    elapsedTime = 0.0f;
    isComplete = false;
}

void DialogueBox::setSpeaker(const std::string& speaker) {
    speakerName = speaker;
    speakerText.setString(speakerName);

    // Position the speaker box and name based on dialogue box position
    sf::Vector2f boxPos = box.getPosition();
    speakerBox.setPosition(boxPos.x, boxPos.y - speakerBox.getSize().y - 5);

    // Center the speaker text in the speaker box
    sf::FloatRect textBounds = speakerText.getLocalBounds();
    speakerText.setPosition(
        boxPos.x + 10,
        boxPos.y - speakerBox.getSize().y - 5 + (speakerBox.getSize().y - textBounds.height) / 2 - textBounds.top
    );
}

void DialogueBox::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

void DialogueBox::setPosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x + 20, y + 20);

    // Update speaker box and text position as well
    if (!speakerName.empty()) {
        setSpeaker(speakerName); // This will recalculate positions
    }
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

    // Only draw speaker box and name if there is a speaker
    if (!speakerName.empty()) {
        window.draw(speakerBox);
        window.draw(speakerText);
    }
}

bool DialogueBox::isDialogueComplete() const {
    return isComplete;
}

void DialogueBox::skipToEnd() {
    currentText = fullText;
    isComplete = true;
    text.setString(currentText);
}