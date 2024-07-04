#include "tilemaps/tile.h"

#include <Tracy/Tracy.hpp>

Tile::Tile(ResourceManager::Resource resource, float x = 0, float y = 0, bool is_walkable = true, TileType tile = TileType::kWater2) : type_(tile)
{

	

	sprite_.setTexture(ResourceManager::Get().GetTexture(resource));
	sprite_.setPosition(x, y);

	//outline_.setSize(sf::Vector2f(sprite_.getTexture()->getSize()));
	//outline_.setPosition(x, y);
	//outline_.setFillColor(sf::Color(255, 255, 255, 0));
	//outline_.setOutlineColor(sf::Color::White);
	//outline_.setOutlineThickness(-1);

	isWalkable_ = is_walkable;
}

void Tile::set_walkable(const bool cond) 
{
	isWalkable_ = cond;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);

	if (isSelected_) {
		target.draw(outline_, states);
	}
}

void Tile::Select()
{
	isSelected_ = true;
}
void Tile::Unselect()
{
	isSelected_ = false;
}

