#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <SFML/Graphics.hpp>

#include "resource_manager.h"
#include "game_state.h"

/**
 * @brief The RenderEngine class
 * This class is responsible for rendering the game state
 * to the screen.
 */
class RenderEngine {
    sf::RenderWindow& window;
    ResourceManager& manager;
    GameState& state;

public:
    // Size of the game board
    static const int WINDOW_WIDTH = 600;
    static const int WINDOW_HEIGHT = 600;
    // Size of each cell
    static const int CELL_WIDTH = 200;
    static const int CELL_HEIGHT = 200;
    // position of O, X in texture image.png
    static const sf::IntRect ORECT;
    static const sf::IntRect XRECT;

    RenderEngine(sf::RenderWindow& window_, ResourceManager& manager_, GameState& state_)
        : window(window_), manager(manager_), state(state_) {}

    // Render the game state to the screen
    // create shape X, O
    // create text to display final message
    void render();
private:
    // Create shape X, O
    sf::CircleShape createShape(sf::Texture& texture, int i, int j, char player);

    // Create text to display final message
    sf::Text createText(sf::Font& font, const std::string& msg);
};

#endif