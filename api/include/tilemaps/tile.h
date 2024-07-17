#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "RessourceManager.h"

enum class TileType {
    kForet1,
    kForetCoupe1,
    kSand1,
    kSnow1,
    kStone1,
    kStone2,
    kTerre1,
    kTerre2,
    kWater1,
    kMan,
    kMaison1,
    kMaison2,
    kMaison3,
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
    void UpdateSprite();
    void set_walkable(bool cond) ;
    void Set_Tree(TileType newtiletype);
    void Set_earther(TileType newtiletype);
    void Set_Stone(TileType newtiletype);
    void Set_Stone_2(TileType newtiletype);

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



