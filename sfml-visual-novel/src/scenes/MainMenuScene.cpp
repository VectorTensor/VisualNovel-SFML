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
    title.setString("Or Something Like It");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    
    // Center the title properly
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition((800 - titleBounds.width) / 2 - titleBounds.left, 100);
    
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
    // Configure buttons with font and text (avoiding double initialization)
    newGameButton.setText("New Game");
    newGameButton.setFont(font);
    
    loadGameButton.setText("Load Game");
    loadGameButton.setFont(font);
    
    settingsButton.setText("Settings");
    settingsButton.setFont(font);
    
    quitButton.setText("Quit");
    quitButton.setFont(font);
    
    // Center buttons better (assuming 800px window width and 200px button width)
    float centerX = (800 - 200) / 2; // Center position for 200px wide buttons
    
    newGameButton.setPosition(centerX, 200);
    loadGameButton.setPosition(centerX, 270);
    settingsButton.setPosition(centerX, 340);
    quitButton.setPosition(centerX, 410);
    
    // Load textures for all buttons with specific styles
    newGameButton.loadTexture("../assets/ButtonsIcons/IconButton_Large_Blue_Rounded.png");
    loadGameButton.loadTexture("../assets/ButtonsIcons/IconButton_Large_Green_Rounded.png");
    settingsButton.loadTexture("../assets/ButtonsIcons/IconButton_Large_Orange_Rounded.png");
    quitButton.loadTexture("../assets/ButtonsIcons/IconButton_Large_Red_Rounded.png");
}

void MainMenuScene::update(float deltaTime, sf::RenderWindow& window) {
    // Get mouse position and convert to world coordinates
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

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
    // Keep basic event handling for non-mouse click events
    // Mouse click events will now be handled by mouseClickHandle
}

GameState MainMenuScene::mouseClickHandle(const sf::Vector2f& mousePos, GameState currentState) {
    if (newGameButton.isClicked(mousePos)) {
        return GameState::InGame;
    } else if (loadGameButton.isClicked(mousePos)) {
        // For now, just return the current state
        // You can update this when load game functionality is implemented
        return currentState;
    } else if (settingsButton.isClicked(mousePos)) {
        // For now, just return the current state
        // You can update this when settings functionality is implemented
        return currentState;
    } else if (quitButton.isClicked(mousePos)) {
        return GameState::Quit;
    }
    return currentState; // No change if no button was clicked
}

bool MainMenuScene::isNewGameClicked(const sf::Vector2f& mousePos) const {
    return newGameButton.isClicked(mousePos);
}

bool MainMenuScene::isQuitClicked(const sf::Vector2f& mousePos) const {
    return quitButton.isClicked(mousePos);
}