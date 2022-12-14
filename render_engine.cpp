#include "render_engine.h"

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
        shape.setTextureRect(sf::IntRect(110, 20, 80, 80));
    else
        shape.setTextureRect(sf::IntRect(20, 20, 80, 80));
    shape.setPosition(sf::Vector2f(i*200,j*200));

    return shape;
}

// Create text to display final message
sf::Text RenderEngine::createText(sf::Font& font, const std::string& msg)
{
    sf::Text text;
    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("X wins");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Cyan);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(150, 200);
    text.setScale(3.0f, 3.0f);

    text.setString(msg);

    return text;
}  

