
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/woodhouse.h"

#include "gameplay/sprite_entity.h"
#include "tilemaps/RessourceManager.h"

void woodhouse::defineTexture(ResourceManager::Resource texture)
{
	shape_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::kMaison1));
}