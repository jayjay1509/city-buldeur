#ifndef stonehouse_H
#define stonehouse_H
#include <SFML/Graphics/Sprite.hpp>

#include "sprite_entity.h"

class stonehouse : public SpriteEntity {
public:

	stonehouse(float x, float y) :SpriteEntity(x, y)
	{
		defineTexture(ResourceManager::Resource::kMaison2);
	}

protected:
	virtual void defineTexture(ResourceManager::Resource texture) override;

public:;
};


#endif // BUILDING_H
