#include <iostream>
#include <queue>

#include <SFML/Graphics.hpp>

#include "resource_manager.h" // resource management
#include "game_state.h" // model
#include "render_engine.h" // view
#include "controller.h" // controller

int main()
{
    sf::RenderWindow window(sf::VideoMode(RenderEngine::WINDOW_WIDTH, RenderEngine::WINDOW_HEIGHT), "Tic-tac-toe!");
    ResourceManager manager;
    GameState state; // Model
    RenderEngine engine(window, manager, state); // View
    Controller controller(state, window); // Controller
    controller.launch(); // launch the event thread

    // Start the game loop - Controller
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            controller.processEvent(event);
        }
        engine.render();
    }

    controller.wait();
    return 0;
}

