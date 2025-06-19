#include "PauseMenu.hpp"

PauseMenu::PauseMenu() {
    active = false;
    
    // Set up background
    background.setSize(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setPosition(0, 0);
}

void PauseMenu::init() {
    setupButtons();
}

void PauseMenu::setFont(const sf::Font& pauseFont) {
    font = pauseFont;
    resumeButton.setText("Resume");
    resumeButton.setFont(font);
    quitButton.setText("Quit");
    quitButton.setFont(font);
    setupButtons(); // Re-setup buttons after font is set
}

void PauseMenu::setupButtons() {
    // Center buttons properly (assuming 800px window width and 200px button width)
    float centerX = (800 - 200) / 2; // Center position for 200px wide buttons
    
    resumeButton.setPosition(centerX, 250);
    quitButton.setPosition(centerX, 320);
    
    // Load textures for buttons
    resumeButton.loadTexture();
    quitButton.loadTexture();
}

void PauseMenu::update(float deltaTime, sf::RenderWindow& window) {
    if (!active) return;
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    // Update buttons for hover animations
    resumeButton.update(deltaTime, mousePosF);
    quitButton.update(deltaTime, mousePosF);
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (resumeButton.isClicked(mousePosF)) {
            setActive(false);
        } else if (quitButton.isClicked(mousePosF)) {
            window.close();
        }
    }
}

void PauseMenu::render(sf::RenderWindow& window) {
    if (!active) return;
    
    window.draw(background);
    resumeButton.render(window);
    quitButton.render(window);
}

bool PauseMenu::isActive() const {
    return active;
}

void PauseMenu::setActive(bool isActive) {
    active = isActive;
}