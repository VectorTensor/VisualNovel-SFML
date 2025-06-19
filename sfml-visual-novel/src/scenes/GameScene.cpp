#include "GameScene.hpp"
#include "../ui/DialogueBox.hpp"
#include "../ui/CharacterImage.hpp"
#include "../ui/ChoiceUI.hpp"
#include "../utils/ResourceManager.hpp"
#include <SFML/Graphics.hpp>

GameScene::GameScene() {
    isPaused = false;
}

GameScene::~GameScene() {
    // Destructor - cleanup if needed
}

bool GameScene::init() {
    if (!loadResources()) {
        return false;
    }
    setupUI();
    return true;
}

bool GameScene::loadResources() {
    // Try to load font
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf") && 
            !font.loadFromFile("/System/Library/Fonts/Arial.ttf") &&
            !font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            return false;
        }
    }
    
    // Try to load background
    if (!backgroundTexture.loadFromFile("assets/backgrounds/game_background.png")) {
        // Create a simple gradient background
        backgroundTexture.create(800, 600);
        sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];
        for (int y = 0; y < 600; ++y) {
            for (int x = 0; x < 800; ++x) {
                int index = (y * 800 + x) * 4;
                pixels[index] = 100 + y / 6;     // R
                pixels[index + 1] = 150 + y / 8; // G
                pixels[index + 2] = 200 + y / 10; // B
                pixels[index + 3] = 255;         // A
            }
        }
        backgroundTexture.update(pixels);
        delete[] pixels;
    }
    backgroundSprite.setTexture(backgroundTexture);
    
    // Try to load character image (optional)
    characterImage.loadFromFile("assets/characters/character.png");
    characterImage.setPosition(500, 200);
    
    return true;
}

void GameScene::setupUI() {
    dialogueBox.setFont(font);
    dialogueBox.setPosition(50, 400);
    dialogueBox.setText("Welcome to the visual novel! This is your first dialogue.");
    
    choiceUI.setFont(font);
    choiceUI.setPosition(100, 300);
    
    pauseMenu.setFont(font);
    pauseMenu.init();
    
    // Setup pause button
    pauseButton = Button(font, "||", 18); // Pause symbol
    pauseButton.setSize(50, 40); // Smaller size for pause button
    pauseButton.setPosition(730, 20); // Top-right corner but within bounds
}

void GameScene::update(float deltaTime, sf::RenderWindow& window) {
    // Get mouse position for button hover effects
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    // Always update pause button for hover effects
    pauseButton.update(deltaTime, mousePosF);
    
    if (!isPaused) {
        dialogueBox.update(deltaTime);
        choiceUI.update(window);
        
        // Check for choice selection
        int selectedChoice = choiceUI.getSelectedChoice();
        if (selectedChoice >= 0) {
            // Handle choice selection
            choiceUI.clearChoices();
        }
    } else {
        pauseMenu.update(deltaTime, window);
        // Check if pause menu wants to resume
        if (!pauseMenu.isActive()) {
            isPaused = false;
        }
    }
}

void GameScene::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    characterImage.render(window);
    dialogueBox.render(window);
    
    if (!isPaused) {
        choiceUI.render(window);
    } else {
        pauseMenu.render(window);
    }
    
    // Always render pause button on top
    pauseButton.render(window);
}

void GameScene::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            isPaused = !isPaused;
            pauseMenu.setActive(isPaused);
        }
    }
    
    // Handle pause button click
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), 
                                 static_cast<float>(event.mouseButton.y));
            
            if (pauseButton.isClicked(mousePos)) {
                isPaused = !isPaused;
                pauseMenu.setActive(isPaused);
            }
        }
    }
}