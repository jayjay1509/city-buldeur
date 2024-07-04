#include "gameplay/woodman.h"


woodman::woodman(float x, float y, float linear_speed) : walker(x,y,linear_speed)
{
	rect_.setPosition(shape_.getGlobalBounds().getPosition());
	rect_.setSize(shape_.getGlobalBounds().getSize());
	defineTexture(ResourceManager::Resource::kMan);
}

void woodman::defineTexture(ResourceManager::Resource texture)
{
	shape_.setTexture(ResourceManager::Get().GetTexture(texture));
}

