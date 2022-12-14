#include <SFML/Graphics.hpp>
#include <iostream>

#include "resource_manager.h"

ResourceManager::ResourceManager()
{
    // Load the texture for the shapes
    if (!texture.loadFromFile("image.png"))
    {
        std::cerr << "Error loading image.png" << std::endl;
        exit(1);
    }

    // Load the font for the text
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error loading arial.ttf" << std::endl;
        exit(1);
    }
}

// Getters
sf::Texture& ResourceManager::getTexture() {
    return texture;
}

sf::Font& ResourceManager::getFont() {
    return font;
}

