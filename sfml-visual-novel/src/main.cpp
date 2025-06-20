#include "scenes/GameScene.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// Define constant target resolution
const unsigned int TARGET_WIDTH = 800;
const unsigned int TARGET_HEIGHT = 600;

int main() {
    // Start with a default window size
    sf::RenderWindow window(sf::VideoMode(TARGET_WIDTH, TARGET_HEIGHT), "Visual Novel");
    window.setFramerateLimit(60);

    // Create a view for our target resolution
    sf::View view(sf::FloatRect(0, 0, TARGET_WIDTH, TARGET_HEIGHT));

    // Create scenes
    std::unique_ptr<Scene> currentScene = std::make_unique<MainMenuScene>();
    std::unique_ptr<Scene> gameScene = std::make_unique<GameScene>();
    GameState currentState = GameState::MainMenu;

    if (!currentScene->init()) {
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
            
            // Handle window resize or fullscreen toggle
            if (event.type == sf::Event::Resized) {
                // Update the view to maintain the aspect ratio
                float aspectRatio = static_cast<float>(TARGET_WIDTH) / static_cast<float>(TARGET_HEIGHT);
                float windowRatio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
                float viewWidth, viewHeight;
                float viewX = 0, viewY = 0;

                if (windowRatio > aspectRatio) {
                    // Window is wider than the target aspect ratio
                    viewHeight = event.size.height;
                    viewWidth = viewHeight * aspectRatio;
                    viewX = (event.size.width - viewWidth) / 2.f;
                } else {
                    // Window is taller than the target aspect ratio
                    viewWidth = event.size.width;
                    viewHeight = viewWidth / aspectRatio;
                    viewY = (event.size.height - viewHeight) / 2.f;
                }

                view.reset(sf::FloatRect(0, 0, TARGET_WIDTH, TARGET_HEIGHT));
                view.setViewport(sf::FloatRect(
                    viewX / event.size.width,
                    viewY / event.size.height,
                    viewWidth / event.size.width,
                    viewHeight / event.size.height
                ));
            }

            // Toggle fullscreen with F11
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {
                static bool isFullscreen = false;
                isFullscreen = !isFullscreen;

                if (isFullscreen) {
                    window.create(sf::VideoMode::getDesktopMode(), "Visual Novel", sf::Style::Fullscreen);
                } else {
                    window.create(sf::VideoMode(TARGET_WIDTH, TARGET_HEIGHT), "Visual Novel", sf::Style::Default);
                }
                window.setFramerateLimit(60);

                // Make sure the view is updated after the window is recreated
                window.setView(view);
            }

            // Handle events in the current scene
            currentScene->handleEvent(event);

            // Handle mouse click events using the new mouseClickHandle method
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Convert mouse position to world coordinates
                    sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);

                    // Let the scene handle mouse clicks and state transitions
                    GameState newState = currentScene->mouseClickHandle(worldPos, currentState);

                    // Handle state changes
                    if (newState != currentState) {
                        if (newState == GameState::InGame) {
                            // Switch to game scene
                            if (!gameScene->init()) {
                                return -1;
                            }
                            currentScene = std::move(gameScene);
                            gameScene = std::make_unique<GameScene>();
                        }
                        else if (newState == GameState::MainMenu) {
                            // Switch to main menu scene - create a new instance first
                            std::unique_ptr<Scene> mainMenuScene = std::make_unique<MainMenuScene>();
                            if (!mainMenuScene->init()) {
                                return -1;
                            }
                            currentScene = std::move(mainMenuScene);
                        }
                        else if (newState == GameState::Quit) {
                            window.close();
                        }
                        currentState = newState;
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Always apply the view
        window.setView(view);

        // Update and render current scene
        currentScene->update(deltaTime, window);

        window.clear();
        currentScene->render(window);
        window.display();
    }

    return 0;
}
