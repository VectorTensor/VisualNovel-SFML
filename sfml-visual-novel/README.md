# SFML Visual Novel

## Overview
This project is a visual novel game developed using C++ and the SFML (Simple and Fast Multimedia Library) framework. It features a main menu with options for starting a new game, loading a game, adjusting settings, and quitting the application. The game scene includes a dialogue interface, character images, and choices for the player, all designed with smooth animations and an engaging user interface.

## Project Structure
The project is organized into several directories:

- **src/**: Contains the source code for the application.
  - **scenes/**: Implements different scenes of the game, including the main menu and game scenes.
  - **ui/**: Contains UI components such as buttons, dialogue boxes, and character images. Button animations are handled directly within the Button class.
  - **utils/**: Includes utility classes for resource management.

- **include/**: Contains SFML headers and other necessary includes.

- **assets/**: Holds game assets like backgrounds, character images, fonts, and audio files.

- **CMakeLists.txt**: Configuration file for building the project with CMake.

## Setup Instructions
1. **Install SFML**: Ensure that SFML is installed on your system. You can download it from the [SFML website](https://www.sfml-dev.org/download.php).

2. **Clone the Repository**: Clone this repository to your local machine using:
   ```
   git clone <repository-url>
   ```

3. **Build the Project**:
   - Navigate to the project directory.
   - Create a build directory:
     ```
     mkdir build
     cd build
     ```
   - Run CMake to configure the project:
     ```
     cmake ..
     ```
   - Build the project:
     ```
     make
     ```

4. **Run the Game**: After building, you can run the game executable located in the build directory.

## Usage
- Launch the game to access the main menu.
- Use the mouse to click on buttons to navigate through the game.
- In the game scene, interact with dialogue and make choices that affect the story.

## Contributing
Contributions are welcome! If you have suggestions or improvements, feel free to submit a pull request.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.