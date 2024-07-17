#ifndef foodhouse_H
#define foodhouse_H
#include <SFML/Graphics/Sprite.hpp>

#include "sprite_entity.h"

class foodhouse : public SpriteEntity {
public:

	foodhouse(float x, float y) :SpriteEntity(x, y)
	{
		defineTexture(ResourceManager::Resource::kMaison3);
	}

protected:
	virtual void defineTexture(ResourceManager::Resource texture) override;

public:;
};


#endif // BUILDING_H
