
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/foodhouse.h"

#include "gameplay/sprite_entity.h"
#include "tilemaps/RessourceManager.h"

void foodhouse::defineTexture(ResourceManager::Resource texture)
{
	shape_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::kMaison3));
}