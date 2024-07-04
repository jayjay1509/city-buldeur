
#include <iostream>

#include <gameplay/building_manager.h>

void BuildingManager::SetActive(bool active)
{
	is_active_ = active;
}
bool BuildingManager::GetActive() const
{
	return is_active_;
}

void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& b : buildings_)
	{
		target.draw(b, states);
	}
}

void BuildingManager::AddBuilding(Tile& tile)
{
	if(!is_active_)
	{
		return;
	}

	std::cout << "Tile clicked, can we finally add a house ? [" << tile.Position().x << ":" << tile.Position().y << "]" << std::endl;

	if(tile.GetType() == TileType::kWater1 || tile.GetType() == TileType::kWater2)
	{
		buildings_.emplace_back(tile.Position().x, tile.Position().y);
		tile.set_walkable(false);
	}

}

