#include "scenes/GameScene.hpp"
#include "scenes/MainMenuScene.hpp"
#include <SFML/Graphics.hpp>

enum class GameState {
    MainMenu,
    InGame,
    Quit
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Visual Novel");
    window.setFramerateLimit(60);

    MainMenuScene mainMenu;
    GameScene gameScene;
    GameState currentState = GameState::MainMenu;

    if (!mainMenu.init()) {
        return -1;
    }

    sf::Clock clock;
    while (window.isOpen() && currentState != GameState::Quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            
            if (currentState == GameState::MainMenu) {
                mainMenu.handleEvent(event);
                
                // Check for scene transitions from main menu
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), 
                                             static_cast<float>(event.mouseButton.y));
                        
                        // Check if new game button was clicked
                        if (mainMenu.isNewGameClicked(mousePos)) {
                            if (!gameScene.init()) {
                                return -1;
                            }
                            currentState = GameState::InGame;
                        }
                        // Check if quit button was clicked
                        else if (mainMenu.isQuitClicked(mousePos)) {
                            currentState = GameState::Quit;
                        }
                    }
                }
            }
            else if (currentState == GameState::InGame) {
                gameScene.handleEvent(event);
                
                // Check for returning to main menu (ESC key)
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                    currentState = GameState::MainMenu;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Update current scene
        if (currentState == GameState::MainMenu) {
            mainMenu.update(window, deltaTime);
        }
        else if (currentState == GameState::InGame) {
            gameScene.update(deltaTime, window);

            // Check if game scene requested to return to main menu
            if (gameScene.shouldReturnToMainMenu()) {
                currentState = GameState::MainMenu;
                gameScene.resetMainMenuRequest();
            }
        }

        // Render current scene
        window.clear();
        if (currentState == GameState::MainMenu) {
            mainMenu.render(window);
        }
        else if (currentState == GameState::InGame) {
            gameScene.render(window);
        }
        window.display();
    }

    return 0;
}
