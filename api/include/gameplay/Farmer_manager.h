#ifndef farmer_MANAGER_H_
#define farmer_MANAGER_H_

#include <vector>
#include "woodhouse.h"
#include "Farmer.h"
#include "tilemaps/tile.h"


class Farmer_Manager : public sf::Drawable
{
private:

	bool is_active_ = true;

	

public :
	void AddFarmer(const Tile& tile,Tilemap& map);
	std::vector<Farmer> farmers_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif 
