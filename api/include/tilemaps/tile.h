#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "RessourceManager.h"

enum class TileType {
    kForet1,
    kForet2,
    kForet3,
    kForet4,
    kForet5,
    kForet6,
    kForet7,
    kForet8,
    kForet9,
    kForet10,
    kForet11,
    kForet12,
    kForetCoupe1,
    kForetCoupe2,
    kForetCoupe3,
    kForetCoupe4,
    kCaisse1,
    kCaisse2,
    kCaisse3,
    kCaisse4,
    kRoute1,
    kRoute2,
    kRoute3,
    kRoute4,
    kRoute5,
    kRoute6,
    kRoute7,
    kRoute8,
    kRoute9,
    kRoute10,
    kRoute11,
    kRoute12,
    kRoute13,
    kRoute14,
    kRoute15,
    kRoute16,
    kRoute17,
    kSand1,
    kSand2,
    kSnow1,
    kSnow2,
    kStone1,
    kStone2,
    kTerre1,
    kTerre2,
    kWater1,
    kWater2,
    kMan,
    kMaison1,
    kMaison2,
    kMaison3,
    kMaison4,
    kEnd
};


class Tile : public sf::Drawable
{
public:
    Tile(ResourceManager::Resource resource, float x, float y, bool is_walkable, TileType type);

    bool Walkable() const { return isWalkable_; }
    sf::Vector2f Position() const { return sprite_.getPosition(); }
    TileType GetType() const { return type_; }

    void Select();
    void Unselect();
    sf::Texture& GetFromType();
    void set_walkable(bool cond) ;
    

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite_;
    sf::RectangleShape outline_;
    bool isWalkable_;
    bool isSelected_ = false;
    TileType type_;
};


#endif



