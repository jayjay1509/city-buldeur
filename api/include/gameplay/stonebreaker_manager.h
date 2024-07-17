#ifndef stone_MANAGER_H_
#define stone_MANAGER_H_

#include <vector>
#include "woodhouse.h"
#include "stonebreaker.h"
#include "tilemaps/tile.h"


class stonebreakerManager : public sf::Drawable
{
private:

	bool is_active_ = true;

public :
	void Addstonebreaker(const Tile& tile,Tilemap& map);
	std::vector<stonebreaker> stonebreakers_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif 
