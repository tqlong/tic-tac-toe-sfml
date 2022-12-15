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
    static const int WINDOW_WIDTH = 900;
    static const int WINDOW_HEIGHT = 900;
    // Size of each cell
    static const int CELL_WIDTH = WINDOW_WIDTH / 3;
    static const int CELL_HEIGHT = WINDOW_HEIGHT / 3;
    //
    static const int SHAPE_RADIUS = CELL_WIDTH / 2;
    // position of O, X in texture image.png

    static const int BUTTON_HvH_X = 100;
    static const int BUTTON_HvH_Y = WINDOW_HEIGHT/2-100;
    static const int BUTTON_HvM_X = WINDOW_WIDTH/2+100;
    static const int BUTTON_HvM_Y = WINDOW_HEIGHT/2-200;
    static const int BUTTON_MvH_X = WINDOW_WIDTH/2+100;
    static const int BUTTON_MvH_Y = WINDOW_HEIGHT/2+100;
    static const int BUTTON_WIDTH = 200;
    static const int BUTTON_HEIGHT = 200;

    static const sf::IntRect ORECT;
    static const sf::IntRect XRECT;

    RenderEngine(sf::RenderWindow& window_, ResourceManager& manager_, GameState& state_)
        : window(window_), manager(manager_), state(state_) {}

    // Render the game state to the screen
    // create shape X, O
    // create text to display final message
    void render();

    static sf::IntRect getButtonHvsHRect() {
        return sf::IntRect(
            RenderEngine::BUTTON_HvH_X, RenderEngine::BUTTON_HvH_Y,
            RenderEngine::BUTTON_WIDTH, RenderEngine::BUTTON_HEIGHT);
    }
    static sf::IntRect getButtonHvsMRect() { 
        return sf::IntRect(
            RenderEngine::BUTTON_HvM_X, RenderEngine::BUTTON_HvM_Y,
            RenderEngine::BUTTON_WIDTH, RenderEngine::BUTTON_HEIGHT);
    }
    static sf::IntRect getButtonMvsHRect() { 
        return sf::IntRect(
            RenderEngine::BUTTON_MvH_X, RenderEngine::BUTTON_MvH_Y,
            RenderEngine::BUTTON_WIDTH, RenderEngine::BUTTON_HEIGHT);
    }
private:
    // Create shape X, O
    sf::CircleShape createShape(sf::Texture& texture, int i, int j, char player);

    // Create text to display final message
    sf::Text createText(sf::Font& font, const std::string& msg);

    // Render functions for each screen
    void renderPlayModeScreen();
    void renderPlayingScreen();

    // Create button
    sf::Sprite createButton(const std::string& msg);
};

#endif