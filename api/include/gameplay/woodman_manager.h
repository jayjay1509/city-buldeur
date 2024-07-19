#ifndef woodman_MANAGER_H_
#define woodman_MANAGER_H_

#include <vector>
#include "woodhouse.h"
#include "woodman.h"
#include "tilemaps/tile.h"


class woodmanManager : public sf::Drawable
{
private:
	bool is_active_ = true;
public :
	void Addwoodman(const Tile& tile,Tilemap& map);
	std::vector<woodman> woodmans_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif 
