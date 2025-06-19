#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include <SFML/Graphics.hpp>
#include "../ui/Button.hpp"

class MainMenuScene {
public:
    MainMenuScene();
    bool init();  // Returns bool to match usage in main.cpp
    void update(sf::RenderWindow& window, float deltaTime = 1.0f/60.0f);  // Takes window parameter and deltaTime
    void render(sf::RenderWindow& window);  // Takes window parameter
    void handleEvent(const sf::Event& event);  // Added to match main.cpp usage
    
    // Scene transition methods
    bool isNewGameClicked(const sf::Vector2f& mousePos) const;
    bool isQuitClicked(const sf::Vector2f& mousePos) const;

private:
    sf::Font font;
    sf::Text title;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    
    Button newGameButton;
    Button loadGameButton;
    Button settingsButton;
    Button quitButton;

    void setupButtons();  // Added setupButtons() declaration
};

#endif // MAINMENUSCENE_HPP