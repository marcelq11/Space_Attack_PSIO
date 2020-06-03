#include "other.h"

sf::Texture Load_texture(std::string path)
{
    sf::Texture texture;

    if (!texture.loadFromFile(path)) {
        std::cerr << "Could not load texture" << std::endl;
    }
    return texture;
}
