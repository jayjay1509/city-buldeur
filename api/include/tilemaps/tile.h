#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "RessourceManager.h"

enum class TileType {
    foret_1,
    foret_2,
    foret_3,
    foret_4,
    foret_5,
    foret_6,
    foret_7,
    foret_8,
    foret_9,
    foret_10,
    foret_11,
    foret_12,
    foret_coupe_1,
    foret_coupe_2,
    foret_coupe_3,
    foret_coupe_4,
    caisse_1,
    caisse_2,
    caisse_3,
    caisse_4,
    route_1,
    route_2,
    route_3,
    route_4,
    route_5,
    route_6,
    route_7,
    route_8,
    route_9,
    route_10,
    route_11,
    route_12,
    route_13,
    route_14,
    route_15,
    route_16,
    route_17,
    sand_1,
    sand_2,
    snow_1,
    snow_2,
    stone_1,
    stone_2,
    terre_1,
    terre_2,
    water_1,
    water_2,
    End
};
// Inclure le fichier d'en-tête qui contient l'énumération TileType

class Tile : public sf::Drawable
{
public:
    Tile(ResourceManager::Resource resource, float x, float y, bool is_walkable, TileType type);

    bool Walkable() const { return isWalkable_; }
    sf::Vector2f Position() const { return sprite_.getPosition(); }
    TileType GetType() const { return type_; }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite_;
    bool isWalkable_;
    TileType type_;
};

#endif // TILE_H
