
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/stonehouse.h"

#include "gameplay/sprite_entity.h"
#include "tilemaps/RessourceManager.h"

void stonehouse::defineTexture(ResourceManager::Resource texture)
{
	shape_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::kMaison2));
}