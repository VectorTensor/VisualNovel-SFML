#include "GameScene.hpp"
#include "../ui/DialogueBox.hpp"
#include "../ui/CharacterImage.hpp"
#include "../ui/ChoiceUI.hpp"
#include "../utils/ResourceManager.hpp"
#include "../utils/DialogueManager.hpp"
#include <SFML/Graphics.hpp>

GameScene::GameScene() {
    isPaused = false;
    returnToMainMenu = false;
    dialogueActive = false;
}

GameScene::~GameScene() {
    // Destructor - cleanup if needed
}

bool GameScene::init() {
    if (!loadResources()) {
        return false;
    }
    setupUI();

    // Load initial dialogue if available
    if (!loadDialogue("../assets/dialogues/sample_dialogue.yml")) {
        // If no dialogue file found, provide a default message
        dialogueBox.setText("No dialogue file found. This is a placeholder.");
        dialogueBox.setSpeaker("System");
    }

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
    pauseButton.setText("||"); // Pause symbol
    pauseButton.setFont(font);
    pauseButton.setSize(50, 40); // Smaller size for pause button
    pauseButton.setPosition(740, 10); // Top-right corner with 10px margin
    pauseButton.loadTexture("assets/ButtonsIcons/IconButton_Large_Blue_Circle.png");

    // Set up character image initial position
    characterImage.setPosition(400, 200); // Center of screen, adjust as needed
}

void GameScene::update(float deltaTime, sf::RenderWindow& window) {
    // Get mouse position and convert to world coordinates
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

    // Always update pause button for hover effects
    pauseButton.update(deltaTime, mousePosF);
    
    if (!isPaused) {
        dialogueBox.update(deltaTime);
        choiceUI.update(window);
        
        // Check for choice selection if we're at a choice point
        int selectedChoice = choiceUI.getSelectedChoice();
        if (selectedChoice >= 0 && dialogueManager.isAtChoicePoint()) {
            // Get the choice text and pass it to dialogue manager
            std::string choiceText = choiceUI.getChoiceText(selectedChoice);
            dialogueManager.selectChoice(choiceText);
            choiceUI.clearChoices();
            updateDialogueDisplay(); // Update the dialogue with the new entry
        }
    } else {
        pauseMenu.update(deltaTime, window);

        // Check if main menu was requested
        if (pauseMenu.isMainMenuRequested()) {
            returnToMainMenu = true;
            pauseMenu.resetMainMenuRequest();
        }

        // Check if pause menu wants to resume
        if (!pauseMenu.isActive()) {
            isPaused = false;
        }
    }
}

void GameScene::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    
    // Only render character image if dialogue is active
    if (dialogueActive) {
        characterImage.render(window);
    }

    dialogueBox.render(window);
    
    if (!isPaused) {
        // Show choices if at a choice point
        if (dialogueManager.isAtChoicePoint()) {
            choiceUI.render(window);
        }
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
        else if (!isPaused && event.key.code == sf::Keyboard::Space) {
            // Space bar advances dialogue when not paused
            if (dialogueBox.isDialogueComplete()) {
                advanceDialogue();
            } else {
                dialogueBox.skipToEnd();
            }
        }
    }
}

GameState GameScene::mouseClickHandle(const sf::Vector2f& mousePos, GameState currentState) {
    // Handle clicks for the game scene
    if (isPaused) {
        // Direct check for Main Menu button click
        if (pauseMenu.isMainMenuButtonClicked(mousePos)) {
            isPaused = false;
            pauseMenu.resetMainMenuRequest();
            return GameState::MainMenu;
        }

        // Check for Quit button click
        if (pauseMenu.isQuitButtonClicked(mousePos)) {
            return GameState::Quit;
        }

        // Also handle existing logic for main menu requests
        if (pauseMenu.isMainMenuRequested()) {
            isPaused = false;
            pauseMenu.resetMainMenuRequest();
            return GameState::MainMenu;
        }

        // Handle pause button clicks
        if (pauseButton.isClicked(mousePos)) {
            isPaused = false;
            pauseMenu.setActive(false);
        }
    } else {
        // Handle game scene clicks
        if (pauseButton.isClicked(mousePos)) {
            isPaused = true;
            pauseMenu.setActive(true);
        }
        else if (dialogueBox.isDialogueComplete()) {
            // Clicking anywhere advances dialogue when dialogue is complete
            advanceDialogue();
        } else {
            // Clicking the dialogue box when not complete skips to end
            dialogueBox.skipToEnd();
        }
    }

    // Return the current state if nothing changes
    return currentState;
}

bool GameScene::loadDialogue(const std::string& dialogueFile) {
    if (dialogueManager.loadDialogueFromFile(dialogueFile)) {
        dialogueActive = true;
        updateDialogueDisplay();
        return true;
    }
    return false;
}

void GameScene::advanceDialogue() {
    if (dialogueManager.advanceDialogue()) {
        updateDialogueDisplay();
    } else if (dialogueManager.isDialogueComplete()) {
        // Handle end of dialogue
        dialogueActive = false;
        dialogueBox.setText("End of dialogue");
        dialogueBox.setSpeaker("");
    }
}

void GameScene::updateDialogueDisplay() {
    // Get current dialogue entry
    DialogueEntry entry = dialogueManager.getCurrentEntry();

    // Update dialogue box with current entry
    dialogueBox.setText(entry.text);
    dialogueBox.setSpeaker(entry.speaker);

    // Update character image if provided
    if (!entry.characterImage.empty()) {
        characterImage.loadFromFile(entry.characterImage);

        // Position character based on position parameter
        if (entry.position == "left") {
            characterImage.setPosition(200, 200);
        } else if (entry.position == "right") {
            characterImage.setPosition(600, 200);
        } else { // center by default
            characterImage.setPosition(400, 200);
        }
    }

    // Update choices if any
    if (dialogueManager.isAtChoicePoint()) {
        choiceUI.clearChoices();
        for (const auto& choice : entry.choices) {
            choiceUI.addChoice(choice);
        }
    }
}
