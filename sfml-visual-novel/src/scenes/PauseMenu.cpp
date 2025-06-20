#include "PauseMenu.hpp"

PauseMenu::PauseMenu() {
    active = false;
    mainMenuRequested = false;

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
    mainMenuButton.setText("Main Menu");
    mainMenuButton.setFont(font);
    quitButton.setText("Quit");
    quitButton.setFont(font);
    setupButtons(); // Re-setup buttons after font is set
}

void PauseMenu::setupButtons() {
    // Center buttons properly (assuming 800px window width and 200px button width)
    float centerX = (800 - 200) / 2; // Center position for 200px wide buttons
    
    resumeButton.setPosition(centerX, 250);
    mainMenuButton.setPosition(centerX, 320);
    quitButton.setPosition(centerX, 390);

    // Load textures for buttons
    resumeButton.loadTexture();
    mainMenuButton.loadTexture();
    quitButton.loadTexture();
}

void PauseMenu::update(float deltaTime, sf::RenderWindow& window) {
    if (!active) return;
    
    // Get proper mouse coordinates that account for viewport transformation
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

    // Update buttons for hover animations
    resumeButton.update(deltaTime, mousePosF);
    mainMenuButton.update(deltaTime, mousePosF);
    quitButton.update(deltaTime, mousePosF);
    
    // NOTE: We're no longer handling button clicks here
    // Instead, we're letting GameScene's mouseClickHandle method handle them
    // This is part of our scene-based click handling system
}

void PauseMenu::render(sf::RenderWindow& window) {
    if (!active) return;
    
    window.draw(background);
    resumeButton.render(window);
    mainMenuButton.render(window);
    quitButton.render(window);
}

bool PauseMenu::isActive() const {
    return active;
}

void PauseMenu::setActive(bool isActive) {
    active = isActive;
}

bool PauseMenu::isMainMenuRequested() const {
    return mainMenuRequested;
}

void PauseMenu::resetMainMenuRequest() {
    mainMenuRequested = false;
}

bool PauseMenu::isMainMenuButtonClicked(const sf::Vector2f& mousePos) const {
    if (!active) return false;
    return mainMenuButton.isClicked(mousePos);
}

bool PauseMenu::isQuitButtonClicked(const sf::Vector2f& mousePos) const {
    if (!active) return false;
    return quitButton.isClicked(mousePos);
}
