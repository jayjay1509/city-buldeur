#ifndef BUILDING_H
#define BUILDING_H
#include <SFML/Graphics/Sprite.hpp>

#include "sprite_entity.h"

class Building : public SpriteEntity {
public:

	Building(float x, float y) :SpriteEntity(x, y)
	{
		defineTexture(ResourceManager::Resource::kMaison1);
	}

protected:
	virtual void defineTexture(ResourceManager::Resource texture) override;

public:;
};


#endif // BUILDING_H
