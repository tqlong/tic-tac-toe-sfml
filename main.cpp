#include "resource_manager.h"
#include "game_state.h"
#include "render_engine.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tic-tac-toe!");
    ResourceManager manager;
    GameState state;
    RenderEngine engine(window, manager, state);

    // Start the game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                // Play by mouse click
                case sf::Event::MouseButtonReleased: {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    int i = localPosition.x / 200, j = localPosition.y / 200;
                    state.playAndChangePlayer(i, j);
                    break;
                }
                default: break;
            }
        }
        state.checkAndProcessFinalState();
        
        engine.render();
    }

    return 0;
}
