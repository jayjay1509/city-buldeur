#ifndef BUILDING_MANAGER_H_
#define BUILDING_MANAGER_H_

#include <vector>

#include "foodhouse.h"
#include "stonehouse.h"
#include "woodhouse.h"
#include "tilemaps/tile.h"
#include "tilemaps/tilemap.h"


class BuildingManager : public sf::Drawable
{
private:
	bool is_active_ = true;

	std::vector<woodhouse> woodhouses_;
	std::vector<stonehouse> stonehouses_;
	std::vector<foodhouse> foodhouses_;

public :
	void Addwoodhouse(Tile& tile, sf::Vector2f pos, Tilemap& map);
	void Addstonehouse(Tile& tile, sf::Vector2f pos, Tilemap& map);
	void Addfoodhouse(Tile& tile, sf::Vector2f pos, Tilemap& map);
	void ClearAll();
	

	void SetActive(bool active);
	bool GetActive() const;

	std::vector<sf::Vector2f> GetWoodhousePositions();
	std::vector<sf::Vector2f> GetStonehousePositions();
	std::vector<sf::Vector2f> GetFoodhousePositions();
	




protected:
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // BUILDING_MANAGER_H_
