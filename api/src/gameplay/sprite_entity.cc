
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/building.h"
#include "tilemaps/RessourceManager.h"

SpriteEntity::SpriteEntity(float x, float y)
{
	if (rect_debug_)
	{
		rect_.setOutlineColor(sf::Color::Magenta);
		rect_.setOutlineThickness(1);
		rect_.setFillColor(sf::Color(100, 100, 100, 0));
	}
	shape_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::kWater1));
	shape_.setPosition(x, y);
}

void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape_, states);
	target.draw(rect_, states);
}