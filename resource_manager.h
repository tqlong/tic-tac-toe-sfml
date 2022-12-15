#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
/**
 * @brief The ResourceManager class
 * This class is responsible for loading all the resources
 * and providing them to the rest of the application.
 */
class ResourceManager
{
    sf::Texture texture;
    sf::Font font;
    sf::Texture buttonTexture;

public:
    ResourceManager();

    // Getters
    sf::Texture& getTexture();
    sf::Texture& getButtonTexture();
    sf::Font& getFont();
};


#endif