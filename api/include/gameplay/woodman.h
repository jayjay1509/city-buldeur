#ifndef woodman_
#define woodman_



#include "sprite_entity.h"
#include "walker.h"

class woodman : public walker
{


public:
	woodman(float x, float y, float linear_speed);

protected:
	void defineTexture(ResourceManager::Resource texture) override;

public:;
	
};




#endif
