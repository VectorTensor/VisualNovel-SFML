#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <SFML/Graphics.hpp>
#include "../ui/DialogueBox.hpp"
#include "../ui/CharacterImage.hpp"
#include "../ui/ChoiceUI.hpp"
#include "../ui/Button.hpp"
#include "../utils/DialogueManager.hpp"
#include "PauseMenu.hpp"
#include "Scene.hpp"

class GameScene : public Scene {
public:
    GameScene();
    ~GameScene();
    bool init() override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;

    // Override the mouse click handling method
    GameState mouseClickHandle(const sf::Vector2f& mousePos, GameState currentState) override;

    bool shouldReturnToMainMenu() const;
    void resetMainMenuRequest();

    // New methods for dialogue management
    bool loadDialogue(const std::string& dialogueFile);
    void advanceDialogue();

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    DialogueBox dialogueBox;
    CharacterImage characterImage;
    ChoiceUI choiceUI;
    PauseMenu pauseMenu;
    Button pauseButton;
    DialogueManager dialogueManager;
    bool isPaused;
    bool returnToMainMenu;
    bool dialogueActive;

    bool loadResources();
    void setupUI();
    void updateDialogueDisplay();
};

#endif // GAMESCENE_HPP