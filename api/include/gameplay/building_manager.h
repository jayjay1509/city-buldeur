#ifndef BUILDING_MANAGER_H_
#define BUILDING_MANAGER_H_

#include <vector>
#include "woodhouse.h"
#include "tilemaps/tile.h"


class BuildingManager : public sf::Drawable
{
private:
	bool is_active_ = true;

	std::vector<woodhouse> woodhouses_;
	std::vector<woodhouse> stonehouses_;
	std::vector<woodhouse> foodhouses_;

public :
	void Addwoodhouse(Tile& tile, sf::Vector2f pos);
	void Addstonehouse(Tile& tile, sf::Vector2f pos);
	void Addfoodhouse(Tile& tile, sf::Vector2f pos);
	void SetActive(bool active);
	bool GetActive() const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif // BUILDING_MANAGER_H_
