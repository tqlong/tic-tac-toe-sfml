#include <SFML/Graphics.hpp>
#include <iostream>

#include "resource_manager.h"

ResourceManager::ResourceManager()
{
    // Load the texture for the shapes
    if (!texture.loadFromFile("resource/image.png"))
    {
        std::cerr << "Error loading image.png" << std::endl;
        exit(1);
    }

    if (!buttonTexture.loadFromFile("resource/buttons.png"))
    {
        std::cerr << "Error loading buttons.png" << std::endl;
        exit(1);
    }

    // Load the font for the text
    if (!font.loadFromFile("resource/arial.ttf"))
    {
        std::cerr << "Error loading arial.ttf" << std::endl;
        exit(1);
    }
}

// Getters
sf::Texture& ResourceManager::getTexture() {
    return texture;
}

sf::Texture& ResourceManager::getButtonTexture() {
    return buttonTexture;
}

sf::Font& ResourceManager::getFont() {
    return font;
}

