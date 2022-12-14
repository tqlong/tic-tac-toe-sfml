#include "render_engine.h"

// position of O, X in texture image.png
const sf::IntRect RenderEngine::ORECT = sf::IntRect(110, 20, 80, 80);
const sf::IntRect RenderEngine::XRECT = sf::IntRect(20, 20, 80, 80);

// Render the game state to the screen
// create shape X, O
// create text to display final message
void RenderEngine::render() {
    window.clear();

    sf::Texture& texture = manager.getTexture();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (state.s[i][j] != ' ') {
                sf::CircleShape shape = createShape(texture, i, j, state.s[i][j]);
                window.draw(shape);
            }
        }
    }

    if (state.gameStop) {
        sf::Text text = createText(
            manager.getFont(),
            state.getFinalMessage()
        );
        window.draw(text);
    }

    window.display();
}

// Create shape X, O
sf::CircleShape RenderEngine::createShape(sf::Texture& texture, int i, int j, char player)
{
    sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    shape.setTexture(&texture);
    if (player == 'O')
        shape.setTextureRect(ORECT);
    else
        shape.setTextureRect(XRECT);
    shape.setPosition(sf::Vector2f(i*CELL_HEIGHT, j*CELL_WIDTH));

    return shape;
}

// Create text to display final message
sf::Text RenderEngine::createText(sf::Font& font, const std::string& msg)
{
    sf::Text text;
    // select the font
    text.setFont(font); // font is a sf::Font

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Cyan);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setScale(3.0f, 3.0f);

    // set the string to display
    text.setString(msg);
    // set the origin to the center of the text
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    // set the position to the center of the window
    text.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    return text;
}  

