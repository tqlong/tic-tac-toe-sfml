#include <iostream>
#include "render_engine.h"

#include "controller.h"

void Controller::processEvent(sf::Event &event)
{
    // only process quick events in the main thread
    // other heavy events (click & AI) are processed in the event thread
    // these heavy events, which change game state, are added to the event queue
    // so that the event thread processes them one by one
    // keeping the consistency of the game state
    switch (event.type) {
        case sf::Event::MouseButtonReleased:
            addEvent(event); // to event thread queue
            break;
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMoved(event);
            break;
        default: break;
    }
}

void Controller::onMouseMoved(sf::Event &event)
{
    if (state.getPlayScreen() == GameState::PlayScreen::PlayModeScreen) {
        sf::Vector2i localPosition = { event.mouseMove.x, event.mouseMove.y};
        checkButtonHovered(localPosition);
    } else {
        sf::Vector2i localPosition = { event.mouseMove.x, event.mouseMove.y};
        int i = localPosition.x / GameWindow::CELL_HEIGHT,
            j = localPosition.y / GameWindow::CELL_WIDTH;
        window.setHoveredCell(i, j);
    }
}

void Controller::onMouseButtonReleased(sf::Event &event)
{
    if (state.getPlayScreen() == GameState::PlayScreen::PlayingScreen)
    {
        if (!state.isGameStop()) {
            sf::Vector2i localPosition = { event.mouseButton.x, event.mouseButton.y};
            int i = localPosition.x / GameWindow::CELL_HEIGHT,
                j = localPosition.y / GameWindow::CELL_WIDTH;
            state.playAndChangePlayer(i, j);
        } else { // game is over so reset the game
            state.resetGame();
            // change the play screen to PlayModeScreen
            state.setPlayScreen(GameState::PlayScreen::PlayModeScreen);
        }
    } else { // GameState::PlayScreen::PlayModeScreen
        sf::Vector2i localPosition = { event.mouseButton.x, event.mouseButton.y};
        checkButtonClicked(localPosition);
    }
}

// check if a button is clicked
void Controller::checkButtonClicked(sf::Vector2i localPosition)
{
   if (GameWindow::getButtonHvsHRect().contains(localPosition)) {
        state.setPlayScreen(GameState::PlayScreen::PlayingScreen);
        state.setPlayMode(GameState::PlayMode::HumanVsHuman);
        std::cout << "Human vs Human" << std::endl;
    } else if (GameWindow::getButtonHvsMRect().contains(localPosition)) {
        state.setPlayScreen(GameState::PlayScreen::PlayingScreen);
        state.setPlayMode(GameState::PlayMode::HumanVsMachine);
        std::cout << "Human vs Machine" << std::endl;
    } else if (GameWindow::getButtonMvsHRect().contains(localPosition)) {
        state.setPlayScreen(GameState::PlayScreen::PlayingScreen);
        state.setPlayMode(GameState::PlayMode::HumanVsMachine);
        state.computerPlayFirst();
        std::cout << "Machine vs Human" << std::endl;
    }
}

// check if a button is hovered
void Controller::checkButtonHovered(sf::Vector2i localPosition)
{
    window.setHoveredButtons(localPosition);
}

void Controller::addEvent(sf::Event event)
{
    mutex.lock();
    queue.push(event);
    mutex.unlock();
}

void Controller::launch() {
    thread.launch();
}

void Controller::wait() {
    thread.wait();
}

sf::Event Controller::getEvent()
{
    sf::Event event;
    event.type = sf::Event::Count;
    mutex.lock();
    if (!queue.empty()) {
        event = queue.front();
        queue.pop();
    }
    mutex.unlock();
    // std::cout << "event pop " << event.type << " " << queue.size() << std::endl; 

    return event;
}

void Controller::run()
{
    while (window.isOpen()) {
        sf::Event event = getEvent();
        switch (event.type) {
            case sf::Event::MouseButtonReleased:
                onMouseButtonReleased(event);
                break;
            default: break;
        }
    }
}
