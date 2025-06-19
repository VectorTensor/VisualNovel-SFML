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

private:
    bool active;
    sf::RectangleShape background;
    sf::Font font;
    Button resumeButton;
    Button quitButton;
    void setupButtons();
};

#endif // PAUSEMENU_HPP