#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button();
    Button(const sf::Font& font, const std::string& text, unsigned int characterSize = 24);
    
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    void setSize(float width, float height);
    void setSize(const sf::Vector2f& size);
    void setText(const std::string& text);
    std::string getText() const; // New method to retrieve button text
    void setFont(const sf::Font& font);
    void loadTexture(const std::string& texturePath = "");
    bool isClicked(const sf::Vector2f& mousePos) const;
    bool isHovered(const sf::Vector2f& mousePos) const;
    void update(float deltaTime, const sf::Vector2f& mousePos);
    void render(sf::RenderWindow& window);

private:
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    sf::Text text;
    sf::Font buttonFont;
    sf::Vector2f originalPosition;
    sf::Vector2f originalSize;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color currentColor;
    bool isCurrentlyHovered;
    float hoverScale;
    float targetScale;
    float animationSpeed;
    
    void updateHoverAnimation(float deltaTime);
    void centerText();
};

#endif // BUTTON_HPP