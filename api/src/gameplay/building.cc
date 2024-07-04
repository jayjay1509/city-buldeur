
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/building.h"

#include "gameplay/sprite_entity.h"
#include "tilemaps/RessourceManager.h"

void Building::defineTexture(ResourceManager::Resource texture)
{
	shape_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::kMaison1));
}