
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/woodhouse.h"
#include "tilemaps/RessourceManager.h"

SpriteEntity::SpriteEntity(float x, float y) : position_(x, y)
{
	if (rect_debug_)
	{
		rect_.setOutlineColor(sf::Color::Magenta);
		rect_.setOutlineThickness(1);
		rect_.setFillColor(sf::Color(100, 100, 100, 0));
	}
	shape_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::kWater1));
	shape_.setPosition(position_);
	rect_.setPosition(position_);
}

sf::Vector2f SpriteEntity::GetPosition() const
{
	return position_;
}

void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape_, states);
	target.draw(rect_, states);
}


void SpriteEntity::SetPosition(float x, float y) 
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
	rect_.setPosition(position_);
}