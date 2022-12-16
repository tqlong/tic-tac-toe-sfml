#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "game_state.h"
#include "queue"

/// @brief Controller class
/// This class is responsible for handling events
///   + quick event in main thread
///   + heavy event in a separate thread
/// to avoid blocking the main thread (which is responsible for rendering)
class Controller
{
    GameState& state;
    sf::RenderWindow& window;
    sf::Mutex mutex;

    std::queue<sf::Event> queue;
    sf::Thread thread;
public:
    Controller(GameState& state_, sf::RenderWindow& window_)
        : state(state_), window(window_),
          thread(&Controller::run, this) {}

    // process an event
    void processEvent(sf::Event& event);

    // launch the thread
    void launch();

    // wait for the thread to finish
    void wait();
private:
    // process a mouse move event
    void onMouseMoved(sf::Event& event);

    // process a click event
    void onMouseButtonReleased(sf::Event& event);

    // check if window is open
    bool isWindowOpen() { return window.isOpen(); }

    void checkButtonClicked(sf::Vector2i localPosition);

    void checkButtonHovered(sf::Vector2i localPosition);

    // add an event to the queue
    void addEvent(sf::Event event);

    // get an event from the queue (blocking)
    sf::Event getEvent();

    // process events in the event thread
    void run();
};

#endif // CONTROLLER_H