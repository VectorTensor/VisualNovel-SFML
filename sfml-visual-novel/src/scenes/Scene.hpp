#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>

enum class GameState {
    MainMenu,
    InGame,
    Paused,
    Quit
};

class Scene {
public:

    sf::RenderWindow window;
    virtual ~Scene() = default;

    virtual bool init() = 0;
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;

    // New method for handling mouse clicks with state change
    virtual GameState mouseClickHandle(const sf::Vector2f& mousePos, GameState currentState) = 0;
};

#endif // SCENE_HPP
