#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include <SFML/Graphics.hpp>
#include "../ui/Button.hpp"

class PauseMenu {
public:
    PauseMenu();
    void init();
    void setFont(const sf::Font& font);
    void update(float deltaTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    bool isActive() const;
    void setActive(bool active);
    bool isMainMenuRequested() const;
    void resetMainMenuRequest();

private:
    bool active;
    bool mainMenuRequested;
    sf::RectangleShape background;
    sf::Font font;
    Button resumeButton;
    Button mainMenuButton;
    Button quitButton;
    void setupButtons();
};

#endif // PAUSEMENU_HPP