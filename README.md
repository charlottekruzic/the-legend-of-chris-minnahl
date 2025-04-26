# The Legend Of Chris Minnahl
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey.svg)](https://opensource.org/licenses/MIT)

## Description
The Legend Of Chris Minnahl is a strategic infiltration game developed during our Bachelor's degree in Computer Science at the University of Franche-Comté, and supervised by associate professor Julien Bernard, where players take on the role of a thief who must navigate through a museum, steal diamonds, and escape without being caught by guards. Developed in C++ using the [GameDev Framework](https://gamedevframework.github.io/) (gf) library, the game combines stealth mechanics with strategic planning.

##  Game features
- Navigate through museum levels with top-down perspective
- Steal diamonds and reach the exit without being spotted by patrolling guards
- Transform into a statue on special pedestals to avoid detection
- Access a mini-map (press M) to view the entire level (guards not visible)
- Multiple levels with increasing difficulty
- Guards with predefined patrol routes and vision cones

## Controls
- **Arrow keys**: Move the player character
- **Space**: Transform into a statue (when standing on a pedestal)
- **M**: View mini-map
- **Escape**: Pause game


## Project structure
The game is built with a scene-based architecture:

- **GameManager**: Controls scene transitions and manages game resources
- **Scene System:** Includes title screen, rules, gameplay, pause menu, map viewer, and end screens
- **ResourceManager**: Handles game assets including textures, fonts, level data, and JSON files
- **Entity Classes**: Player, Guard, Wall and other classes that model the game's interactive elements.

## Building the project

1. Make sure you have the [GameDev Framework](https://gamedevframework.github.io/) installed.
2. Clone the repository:
   ```bash
   git clone https://github.com/charlottekruzic/the-legend-of-chris-minnahl.git
   ```
3. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
4. Run the game:
   ```bash
   ./TheLegendOfChrisMinnahl
   ```

## 📑 Full documentation
For more detailed information about the game's design and implementation, please refer to the [full project report (in french)](./ressources/project-report-fr.pdf) included in the repository.

## 👷 Contributors
- GURNAUD Jade
- TURAN Baturay
- KRUZIC Charlotte