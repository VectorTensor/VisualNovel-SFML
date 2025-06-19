#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <SFML/Graphics.hpp>
#include "../ui/DialogueBox.hpp"
#include "../ui/CharacterImage.hpp"
#include "../ui/ChoiceUI.hpp"
#include "../ui/Button.hpp"
#include "PauseMenu.hpp"

class GameScene {
public:
    GameScene();
    ~GameScene();
    bool init();
    void update(float deltaTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    bool shouldReturnToMainMenu() const;
    void resetMainMenuRequest();

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    DialogueBox dialogueBox;
    CharacterImage characterImage;
    ChoiceUI choiceUI;
    PauseMenu pauseMenu;
    Button pauseButton;
    bool isPaused;
    bool returnToMainMenu;

    bool loadResources();
    void setupUI();
};

#endif // GAMESCENE_HPP