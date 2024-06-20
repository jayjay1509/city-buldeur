#include "tilemaps/tile.h"

#include <Tracy/Tracy.hpp>

Tile::Tile(ResourceManager::Resource resource, float x, float y, bool is_walkable,TileType tile) : type_(tile)
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    sprite_.setTexture(ResourceManager::Get().GetTexture(resource));
    sprite_.setPosition(x, y);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

    target.draw(sprite_, states);
}
