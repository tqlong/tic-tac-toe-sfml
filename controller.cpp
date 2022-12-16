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
    if (state.playScreen == GameState::PlayScreen::PlayModeScreen) {
        sf::Vector2i localPosition = { event.mouseMove.x, event.mouseMove.y};
        checkButtonHovered(localPosition);
    } else {
        sf::Vector2i localPosition = { event.mouseMove.x, event.mouseMove.y};
        int i = localPosition.x / RenderEngine::CELL_HEIGHT,
            j = localPosition.y / RenderEngine::CELL_WIDTH;
        state.setHoveredCell(i, j);
    }
}

void Controller::onMouseButtonReleased(sf::Event &event)
{
    if (state.playScreen == GameState::PlayScreen::PlayingScreen)
    {
        if (!state.gameStop) {
            sf::Vector2i localPosition = { event.mouseButton.x, event.mouseButton.y};
            int i = localPosition.x / RenderEngine::CELL_HEIGHT,
                j = localPosition.y / RenderEngine::CELL_WIDTH;
            state.playAndChangePlayer(i, j);
        } else { // game is over so reset the game
            state.resetGame();
            // change the play screen to PlayModeScreen
            state.playScreen = GameState::PlayScreen::PlayModeScreen;
        }
    } else { // GameState::PlayScreen::PlayModeScreen
        sf::Vector2i localPosition = { event.mouseButton.x, event.mouseButton.y};
        checkButtonClicked(localPosition);
    }
}

// check if a button is clicked
void Controller::checkButtonClicked(sf::Vector2i localPosition)
{
   if (RenderEngine::getButtonHvsHRect().contains(localPosition)) {
        state.playScreen = GameState::PlayScreen::PlayingScreen;
        state.playMode = GameState::PlayMode::HumanVsHuman;
        std::cout << "Human vs Human" << std::endl;
    } else if (RenderEngine::getButtonHvsMRect().contains(localPosition)) {
        state.playScreen = GameState::PlayScreen::PlayingScreen;
        state.playMode = GameState::PlayMode::HumanVsMachine;
        std::cout << "Human vs Machine" << std::endl;
    } else if (RenderEngine::getButtonMvsHRect().contains(localPosition)) {
        state.playScreen = GameState::PlayScreen::PlayingScreen;
        state.playMode = GameState::PlayMode::HumanVsMachine;
        state.computerPlayFirst();
        std::cout << "Machine vs Human" << std::endl;
    }
}

// check if a button is hovered
void Controller::checkButtonHovered(sf::Vector2i localPosition)
{
    state.isHoverOnButtonHvsH = RenderEngine::getButtonHvsHRect().contains(localPosition);
    state.isHoverOnButtonHvsM = RenderEngine::getButtonHvsMRect().contains(localPosition);
    state.isHoverOnButtonMvsH = RenderEngine::getButtonMvsHRect().contains(localPosition);
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