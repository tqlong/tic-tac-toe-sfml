#include "render_engine.h"

// position of O, X in texture image.png
const sf::IntRect GameWindow::ORECT = sf::IntRect(110, 20, 80, 80);
const sf::IntRect GameWindow::XRECT = sf::IntRect(20, 20, 80, 80);

// Render the game state to the screen
// create shape X, O
// create text to display final message
void GameWindow::render() {
    clear();

    switch (state.getPlayScreen()) {
    case GameState::PlayScreen::PlayModeScreen:
        renderPlayModeScreen();
        break;
    case GameState::PlayScreen::PlayingScreen:
        renderPlayingScreen();
        break;
    }

    display();
}

void GameWindow::renderPlayModeScreen()
{
    // Draw the play buttons
    sf::Sprite buttonHvsH = createButton("Human vs Human");
    buttonHvsH.setPosition(BUTTON_HvH_X, BUTTON_HvH_Y);
    if (isHoverOnButtonHvsH) {
        buttonHvsH.setColor(sf::Color(255, 255, 255, 200));
    }

    sf::Sprite buttonHvsM = createButton("Human vs Machine");
    buttonHvsM.setPosition(BUTTON_HvM_X, BUTTON_HvM_Y);
    if (isHoverOnButtonHvsM) {
        buttonHvsM.setColor(sf::Color(255, 255, 255, 200));
    }

    sf::Sprite buttonMvsH = createButton("Machine vs Human");
    buttonMvsH.setPosition(BUTTON_MvH_X, BUTTON_MvH_Y);
    if (isHoverOnButtonMvsH) {
        buttonMvsH.setColor(sf::Color(255, 255, 255, 200));
    }

    draw(buttonHvsH);
    draw(buttonHvsM);
    draw(buttonMvsH);
}

void GameWindow::renderPlayingScreen()
{
    if (hoverI != -1 && hoverJ != -1) {
        sf::RectangleShape shape(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
        shape.setFillColor(sf::Color(0, 0, 0, 100));
        shape.setOutlineColor(sf::Color::Yellow);
        shape.setOutlineThickness(3);
        shape.setPosition(hoverI*CELL_WIDTH, hoverJ*CELL_HEIGHT);
        
        draw(shape);
    }

    // Draw the shapes
    sf::Texture& texture = manager.getTexture();
    for (int i = 0; i < GameState::SIZE; i++) {
        for (int j = 0; j < GameState::SIZE; j++) {
            char play = state.getPlay(i, j);
            if (play != ' ') {
                sf::CircleShape shape = createShape(texture, i, j, play);
                draw(shape);
            }
        }
    }

    // Draw the final message
    if (state.isGameStop()) {
        sf::Text text = createText(manager.getFont(), state.getFinalMessage());
        draw(text);
    } else if (state.isThinking()) {
        sf::Text text = createText(manager.getFont(), "Thinking...");
        draw(text);
    }
}

// Create shape X, O
sf::CircleShape GameWindow::createShape(sf::Texture& texture, int i, int j, char player)
{
    sf::CircleShape shape(SHAPE_RADIUS);
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
sf::Text GameWindow::createText(sf::Font& font, const std::string& msg)
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

sf::Sprite GameWindow::createButton(const std::string& msg)
{
    sf::Sprite button;
    button.setTexture(manager.getButtonTexture());
    if (msg == "Human vs Machine")
        button.setTextureRect(sf::IntRect(20, 20, 200, 200));
    else if (msg == "Human vs Human")
        button.setTextureRect(sf::IntRect(230, 20, 200, 200));
    else // if (msg == "Machine vs Human")
        button.setTextureRect(sf::IntRect(220, 20, -200, 200));
    return button;
}

void GameWindow::setHoveredCell(int i, int j)
{
    if (i >= 0 && i < GameState::SIZE && j >= 0 && j < GameState::SIZE) {
        hoverI = i;
        hoverJ = j;
    }
}

void GameWindow::setHoveredButtons(sf::Vector2i localPosition)
{
    isHoverOnButtonHvsH = GameWindow::getButtonHvsHRect().contains(localPosition);
    isHoverOnButtonHvsM = GameWindow::getButtonHvsMRect().contains(localPosition);
    isHoverOnButtonMvsH = GameWindow::getButtonMvsHRect().contains(localPosition);
}
