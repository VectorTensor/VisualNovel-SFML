#include "Button.hpp"
#include <cmath>

Button::Button() 
    : originalSize(200.0f, 50.0f),
      originalPosition(0.0f, 0.0f),
      hoverScale(1.0f),
      targetScale(1.0f),
      animationSpeed(5.0f),
      normalColor(sf::Color::White),
      hoverColor(sf::Color(220, 220, 255)),
      currentColor(sf::Color::White),
      isCurrentlyHovered(false) {
    
    // Don't load texture here - will be loaded later via loadTexture()
    text.setString("");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
}

Button::Button(const sf::Font& font, const std::string& buttonText, unsigned int characterSize) 
    : Button() {
    setText(buttonText);
    setFont(font);
    text.setCharacterSize(characterSize);
}

void Button::setText(const std::string& buttonText) {
    text.setString(buttonText);
    centerText();
}

void Button::setFont(const sf::Font& font) {
    buttonFont = font;
    text.setFont(buttonFont);
    centerText();
}

void Button::setPosition(float x, float y) {
    originalPosition = sf::Vector2f(x, y);
    buttonSprite.setPosition(x, y);
    centerText();
}

void Button::setPosition(const sf::Vector2f& position) {
    originalPosition = position;
    buttonSprite.setPosition(position);
    centerText();
}

void Button::setSize(float width, float height) {
    originalSize = sf::Vector2f(width, height);
    
    // Update sprite scale if texture is loaded
    sf::Vector2u textureSize = buttonTexture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        float scaleX = width / static_cast<float>(textureSize.x);
        float scaleY = height / static_cast<float>(textureSize.y);
        buttonSprite.setScale(scaleX, scaleY);
    }
    
    centerText();
}

void Button::setSize(const sf::Vector2f& size) {
    setSize(size.x, size.y);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
    return buttonSprite.getGlobalBounds().contains(mousePos);
}

bool Button::isHovered(const sf::Vector2f& mousePos) const {
    return buttonSprite.getGlobalBounds().contains(mousePos);
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
    buttonSprite.setColor(currentColor);
}

void Button::updateHoverAnimation(float deltaTime) {
    // Smooth scale transition
    float scaleDiff = targetScale - hoverScale;
    hoverScale += scaleDiff * animationSpeed * deltaTime;
    
    // Apply scale to button sprite
    sf::Vector2u textureSize = buttonTexture.getSize();
    sf::Vector2f baseScale = sf::Vector2f(originalSize.x / textureSize.x, originalSize.y / textureSize.y);
    sf::Vector2f newScale = baseScale * hoverScale;
    buttonSprite.setScale(newScale);
    
    // Center the scaled button
    sf::Vector2f scaledSize = sf::Vector2f(textureSize.x * newScale.x, textureSize.y * newScale.y);
    sf::Vector2f offset = (scaledSize - originalSize) * 0.5f;
    buttonSprite.setPosition(originalPosition - offset);
    
    // Update text position to stay centered
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::Vector2f buttonCenter = buttonSprite.getPosition() + scaledSize * 0.5f;
    text.setPosition(buttonCenter.x - textBounds.width * 0.5f - textBounds.left,
                     buttonCenter.y - textBounds.height * 0.5f - textBounds.top);
}

void Button::render(sf::RenderWindow& window) {
    window.draw(buttonSprite);
    window.draw(text);
}


void Button::loadTexture(const std::string& texturePath) {
    bool loaded = false;
    
    // Try to load custom texture path if provided
    if (!texturePath.empty()) {
        if (buttonTexture.loadFromFile(texturePath) ||
            buttonTexture.loadFromFile("../" + texturePath)) {
            loaded = true;
        }
    }

    // If no texture path provided or loading failed, use default
    if (!loaded) {
        // Try to load default button texture
        if (buttonTexture.loadFromFile("assets/ButtonsIcons/IconButton_Large_Blue_Rounded.png") ||
            buttonTexture.loadFromFile("../assets/ButtonsIcons/IconButton_Large_Blue_Rounded.png")) {
            loaded = true;
        }
    }
    
    if (!loaded) {
        // Create fallback texture
        buttonTexture.create(static_cast<unsigned int>(originalSize.x), 
                           static_cast<unsigned int>(originalSize.y));
        
        sf::Uint8* pixels = new sf::Uint8[static_cast<size_t>(originalSize.x * originalSize.y * 4)];
        for (size_t i = 0; i < originalSize.x * originalSize.y * 4; i += 4) {
            pixels[i] = 70;     // Red
            pixels[i + 1] = 130; // Green  
            pixels[i + 2] = 180; // Blue
            pixels[i + 3] = 255; // Alpha
        }
        buttonTexture.update(pixels);
        delete[] pixels;
    }
    
    // Set texture to sprite
    buttonSprite.setTexture(buttonTexture);
    
    // Calculate proper scale to fit originalSize
    sf::Vector2u textureSize = buttonTexture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        float scaleX = originalSize.x / static_cast<float>(textureSize.x);
        float scaleY = originalSize.y / static_cast<float>(textureSize.y);
        buttonSprite.setScale(scaleX, scaleY);
    }
    
    // Set position if already set
    if (originalPosition.x != 0 || originalPosition.y != 0) {
        buttonSprite.setPosition(originalPosition);
    }
    
    centerText();
}

void Button::centerText() {
    if (text.getString().isEmpty()) return;
    
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect spriteBounds = buttonSprite.getGlobalBounds();
    
    float textX = spriteBounds.left + (spriteBounds.width - textBounds.width) * 0.5f - textBounds.left;
    float textY = spriteBounds.top + (spriteBounds.height - textBounds.height) * 0.5f - textBounds.top;
    
    text.setPosition(textX, textY);
}