#ifndef Spriritentity_
#define Spriritentity_
#include <SFML/Graphics/Sprite.hpp>

#include "tilemaps/RessourceManager.h"

class SpriteEntity : public sf::Drawable
{

public:
	SpriteEntity(float x, float y);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Sprite shape_;
	sf::RectangleShape rect_;
	bool rect_debug_ = true;
	virtual void  defineTexture(ResourceManager::Resource texture) = 0;
};

#endif 


