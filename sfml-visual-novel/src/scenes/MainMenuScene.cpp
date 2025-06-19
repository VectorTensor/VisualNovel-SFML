#include "MainMenuScene.hpp"
#include "../ui/Button.hpp"
#include <SFML/Graphics.hpp>

MainMenuScene::MainMenuScene() {
    // Constructor - basic initialization done here
}

bool MainMenuScene::init() {
    // Try to load font - use a default system font if custom font fails
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        // If custom font fails, try system default
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf") && 
            !font.loadFromFile("/System/Library/Fonts/Arial.ttf") &&
            !font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            // Create a default font if all else fails
            return false;
        }
    }
    
    // Set up title
    title.setFont(font);
    title.setString("No You Na");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(300, 100);
    
    // Try to load background
    if (!backgroundTexture.loadFromFile("assets/backgrounds/main_menu.png")) {
        // Create a simple colored background if image fails
        backgroundTexture.create(800, 600);
        sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];
        for (int i = 0; i < 800 * 600 * 4; i += 4) {
            pixels[i] = 50;     // R
            pixels[i + 1] = 50; // G
            pixels[i + 2] = 100; // B
            pixels[i + 3] = 255; // A
        }
        backgroundTexture.update(pixels);
        delete[] pixels;
    }
    background.setTexture(backgroundTexture);
    
    setupButtons();
    return true;
}

void MainMenuScene::setupButtons() {
    newGameButton = Button(font, "New Game", 24);
    newGameButton.setPosition(350, 200);
    
    loadGameButton = Button(font, "Load Game", 24);
    loadGameButton.setPosition(350, 270);
    
    settingsButton = Button(font, "Settings", 24);
    settingsButton.setPosition(350, 340);
    
    quitButton = Button(font, "Quit", 24);
    quitButton.setPosition(350, 410);
}

void MainMenuScene::update(sf::RenderWindow& window, float deltaTime) {
    // Get mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    // Update button animations with actual deltaTime
    newGameButton.update(deltaTime, mousePosF);
    loadGameButton.update(deltaTime, mousePosF);
    settingsButton.update(deltaTime, mousePosF);
    quitButton.update(deltaTime, mousePosF);
}

void MainMenuScene::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(title);
    newGameButton.render(window);
    loadGameButton.render(window);
    settingsButton.render(window);
    quitButton.render(window);
}

void MainMenuScene::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), 
                                 static_cast<float>(event.mouseButton.y));
            
            if (newGameButton.isClicked(mousePos)) {
                // New game clicked - handled in main.cpp
            } else if (loadGameButton.isClicked(mousePos)) {
                // Load game
            } else if (settingsButton.isClicked(mousePos)) {
                // Open settings
            } else if (quitButton.isClicked(mousePos)) {
                // Quit clicked - handled in main.cpp
            }
        }
    }
}

bool MainMenuScene::isNewGameClicked(const sf::Vector2f& mousePos) const {
    return newGameButton.isClicked(mousePos);
}

bool MainMenuScene::isQuitClicked(const sf::Vector2f& mousePos) const {
    return quitButton.isClicked(mousePos);
}