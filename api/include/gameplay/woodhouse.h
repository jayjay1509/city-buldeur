#ifndef BUILDING_H
#define BUILDING_H
#include <SFML/Graphics/Sprite.hpp>

#include "sprite_entity.h"

class woodhouse : public SpriteEntity {
public:

	woodhouse(float x, float y) :SpriteEntity(x, y)
	{
		defineTexture(ResourceManager::Resource::kMaison1);
	}

protected:
	virtual void defineTexture(ResourceManager::Resource texture) override;

public:;
};


#endif // BUILDING_H
