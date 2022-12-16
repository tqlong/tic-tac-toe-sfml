#include <iostream>
#include <queue>

#include <SFML/Graphics.hpp>

#include "resource_manager.h"
#include "game_state.h"
#include "render_engine.h"

// check if a button is clicked
void checkButtonClicked(GameState& state, sf::Vector2i localPosition)
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
void checkButtonHovered(GameState& state, sf::Vector2i localPosition)
{
    state.isHoverOnButtonHvsH = RenderEngine::getButtonHvsHRect().contains(localPosition);
    state.isHoverOnButtonHvsM = RenderEngine::getButtonHvsMRect().contains(localPosition);
    state.isHoverOnButtonMvsH = RenderEngine::getButtonMvsHRect().contains(localPosition);
}

// process a click event
void onMouseButtonReleased(GameState& state, sf::Event& event)
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
        checkButtonClicked(state, localPosition);
    }
}

// process a mouse move event
void onMouseMoved(GameState& state, sf::Event& event)
{
    if (state.playScreen == GameState::PlayScreen::PlayModeScreen) {
        sf::Vector2i localPosition = { event.mouseMove.x, event.mouseMove.y};
        checkButtonHovered(state, localPosition);
    } else {
        sf::Vector2i localPosition = { event.mouseMove.x, event.mouseMove.y};
        int i = localPosition.x / RenderEngine::CELL_HEIGHT,
            j = localPosition.y / RenderEngine::CELL_WIDTH;
        state.setHoveredCell(i, j);
    }
}

/// @brief EventThread class
/// This class is responsible for handling events in a separate thread
/// to avoid blocking the main thread (which is responsible for rendering)
class EventThread
{
    sf::RenderWindow& window;
    GameState& state;
    sf::Mutex& mutex;

    std::queue<sf::Event> queue;
    sf::Thread thread;
public:
    EventThread(sf::RenderWindow& window_, GameState& state_, sf::Mutex& mutex_)
        : window(window_), state(state_), mutex(mutex_),
          thread(&EventThread::run, this) {}
    
    void addEvent(sf::Event event)
    {
        mutex.lock();
        queue.push(event);
        mutex.unlock();
    }

    void launch() {
        thread.launch();
    }

    void wait() {
        thread.wait();
    }

private:
    sf::Event getEvent()
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

    void run()
    {
        std::cout << "Event thread started " << window.isOpen() << std::endl;
        while (window.isOpen()) {
            sf::Event event = getEvent();
            switch (event.type) {
                case sf::Event::MouseButtonReleased:
                    onMouseButtonReleased(state, event);
                    break;
                default: break;
            }
        }
    }
};

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(RenderEngine::WINDOW_WIDTH, RenderEngine::WINDOW_HEIGHT),
        "Tic-tac-toe!"
    );
    ResourceManager manager;
    GameState state; // Model
    RenderEngine engine(window, manager, state); // View
    sf::Mutex mutex;
    EventThread eventThread(window, state, mutex);
    eventThread.launch();

    // Start the game loop - Controller
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // only process quick events in the main thread
            // other heavy events (click & AI) are processed in the event thread
            // these heavy events, which change game state, are added to the event queue
            // so that the event thread processes them one by one
            // keeping the consistency of the game state
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonReleased:
                    eventThread.addEvent(event);
                    break;
                case sf::Event::MouseMoved:
                    onMouseMoved(state, event);
                    break;
                default: break;
            }
        }
        engine.render();
    }

    eventThread.wait();
    return 0;
}
