cmake_minimum_required(VERSION 3.10)
project(SFMLVisualNovel)

set(CMAKE_CXX_STANDARD 17)

# Set SFML include and lib paths manually
include_directories(/usr/include/SFML)
link_directories(/usr/lib/x86_64-linux-gnu)


# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
    src/scenes/MainMenuScene.cpp
    src/scenes/GameScene.cpp
    src/scenes/PauseMenu.cpp
    src/ui/Button.cpp
    src/ui/DialogueBox.cpp
    src/ui/CharacterImage.cpp
    src/ui/ChoiceUI.cpp
    src/utils/ResourceManager.cpp
)

# Create the executable
add_executable(SFMLVisualNovel ${SOURCES})

# Link SFML libraries
target_link_libraries(SFMLVisualNovel sfml-graphics sfml-window sfml-system sfml-audio)
