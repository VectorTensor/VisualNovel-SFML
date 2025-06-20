#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include <SFML/Graphics.hpp>
#include "../ui/Button.hpp"
#include "Scene.hpp"

class MainMenuScene : public Scene {
public:
    MainMenuScene();
    bool init() override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;

    // Override the mouse click handling method
    GameState mouseClickHandle(const sf::Vector2f& mousePos, GameState currentState) override;

    bool isNewGameClicked(const sf::Vector2f &mousePos) const;

    bool isQuitClicked(const sf::Vector2f &mousePos) const;

private:
    sf::Font font;
    sf::Text title;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    
    Button newGameButton;
    Button loadGameButton;
    Button settingsButton;
    Button quitButton;

    void setupButtons();
};

#endif // MAINMENUSCENE_HPP