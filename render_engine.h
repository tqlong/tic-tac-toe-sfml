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
class GameWindow: public sf::RenderWindow {
    ResourceManager& manager;
    GameState& state;

    bool isHoverOnButtonHvsH = false;
    bool isHoverOnButtonHvsM = false;
    bool isHoverOnButtonMvsH = false;
    int hoverI = -1;
    int hoverJ = -1;

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

    GameWindow(ResourceManager& manager_, GameState& state_)
        : sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tic Tac Toe"),
          manager(manager_), state(state_) {}

    // Render the game state to the screen
    // create shape X, O
    // create text to display final message
    void render();

    static sf::IntRect getButtonHvsHRect() {
        return sf::IntRect(
            BUTTON_HvH_X, BUTTON_HvH_Y,
            BUTTON_WIDTH, BUTTON_HEIGHT);
    }
    static sf::IntRect getButtonHvsMRect() { 
        return sf::IntRect(
            BUTTON_HvM_X, BUTTON_HvM_Y,
            BUTTON_WIDTH, BUTTON_HEIGHT);
    }
    static sf::IntRect getButtonMvsHRect() { 
        return sf::IntRect(
            BUTTON_MvH_X, BUTTON_MvH_Y,
            BUTTON_WIDTH, BUTTON_HEIGHT);
    }

    // set the hover cell
    void setHoveredCell(int i, int j);

    // set hovered buttons
    void setHoveredButtons(sf::Vector2i localPosition);
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