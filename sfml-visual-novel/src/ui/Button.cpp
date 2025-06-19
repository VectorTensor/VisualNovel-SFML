#include "Button.hpp"
#include <cmath>

Button::Button() {
    // Initialize default values
    originalSize = sf::Vector2f(200, 50);
    shape.setSize(originalSize);
    normalColor = sf::Color::Blue;
    hoverColor = sf::Color(100, 150, 255); // Lighter blue
    currentColor = normalColor;
    shape.setFillColor(currentColor);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    isCurrentlyHovered = false;
    hoverScale = 1.0f;
    targetScale = 1.0f;
    animationSpeed = 5.0f;
}

Button::Button(const sf::Font& font, const std::string& buttonText, unsigned int characterSize) {
    originalSize = sf::Vector2f(200, 50);
    shape.setSize(originalSize);
    normalColor = sf::Color::Blue;
    hoverColor = sf::Color(100, 150, 255); // Lighter blue
    currentColor = normalColor;
    shape.setFillColor(currentColor);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::White);
    
    isCurrentlyHovered = false;
    hoverScale = 1.0f;
    targetScale = 1.0f;
    animationSpeed = 5.0f;
}

void Button::setPosition(float x, float y) {
    originalPosition = sf::Vector2f(x, y);
    shape.setPosition(x, y);
    text.setPosition(x + 10, y + 10);
}

void Button::setSize(float width, float height) {
    originalSize = sf::Vector2f(width, height);
    shape.setSize(originalSize);
    // Center the text within the button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        originalPosition.x + (width - textBounds.width) / 2,
        originalPosition.y + (height - textBounds.height) / 2
    );
}

void Button::setText(const std::string& buttonText) {
    text.setString(buttonText);
}

void Button::setFont(const sf::Font& font) {
    text.setFont(font);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
    return shape.getGlobalBounds().contains(mousePos);
}

bool Button::isHovered(const sf::Vector2f& mousePos) const {
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::update(float deltaTime, const sf::Vector2f& mousePos) {
    bool wasHovered = isCurrentlyHovered;
    isCurrentlyHovered = isHovered(mousePos);
    
    // Set target scale based on hover state
    targetScale = isCurrentlyHovered ? 1.1f : 1.0f;
    
    // Update hover animation
    updateHoverAnimation(deltaTime);
    
    // Color transition
    if (isCurrentlyHovered) {
        currentColor = hoverColor;
    } else {
        currentColor = normalColor;
    }
    shape.setFillColor(currentColor);
}

void Button::updateHoverAnimation(float deltaTime) {
    // Smooth scale transition
    float scaleDiff = targetScale - hoverScale;
    hoverScale += scaleDiff * animationSpeed * deltaTime;
    
    // Apply scale to button
    sf::Vector2f newSize = originalSize * hoverScale;
    shape.setSize(newSize);
    
    // Center the scaled button
    sf::Vector2f offset = (newSize - originalSize) * 0.5f;
    shape.setPosition(originalPosition - offset);
    
    // Update text position to stay centered
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::Vector2f buttonCenter = shape.getPosition() + newSize * 0.5f;
    text.setPosition(buttonCenter.x - textBounds.width * 0.5f - textBounds.left,
                     buttonCenter.y - textBounds.height * 0.5f - textBounds.top);
}

void Button::render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}