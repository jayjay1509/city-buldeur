
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

std::vector<sf::Vector2f> BuildingManager::GetWoodhousePositions()  {
	std::vector<sf::Vector2f> positions;
	for ( auto& house : woodhouses_) {
		positions.push_back(house.GetPosition());
	}
	return positions;
}

std::vector<sf::Vector2f> BuildingManager::GetStonehousePositions()  {
	std::vector<sf::Vector2f> positions;
	for ( auto& house : stonehouses_) {
		positions.push_back(house.GetPosition());
	}
	return positions;
}

std::vector<sf::Vector2f> BuildingManager::GetFoodhousePositions()  {
	std::vector<sf::Vector2f> positions;
	for ( auto& house : foodhouses_) {
		positions.push_back(house.GetPosition());
	}
	return positions;
}

void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& b : woodhouses_)
	{
		target.draw(b, states);
	}
	for (const auto& b : stonehouses_)
	{
		target.draw(b, states);
	}
	for (const auto& b : foodhouses_)
	{
		target.draw(b, states);
	}
}

void BuildingManager::Addwoodhouse(Tile& tile,sf::Vector2f pos,Tilemap& map)
{
	if(!is_active_)
	{
		return;
	}
	map.Remove(pos);
	tile.Set_house(TileType::Kgreen);
	woodhouses_.emplace_back(pos.x, pos.y);
	tile.set_walkable(false);
}


void BuildingManager::Addstonehouse(Tile& tile, sf::Vector2f pos, Tilemap& map)
{
	if (!is_active_)
	{
		return;
	}
	map.Remove(pos);
	tile.Set_house(TileType::Kgreen);
	stonehouses_.emplace_back(pos.x, pos.y);
	tile.set_walkable(false);
}


void BuildingManager::Addfoodhouse(Tile& tile, sf::Vector2f pos, Tilemap& map)
{
	if (!is_active_)
	{
		return;
	}
	map.Remove(pos);
	tile.Set_house(TileType::Kgreen);
	foodhouses_.emplace_back(pos.x, pos.y);
	tile.set_walkable(false);
}

void BuildingManager::ClearAll()
{
	woodhouses_.clear();
	stonehouses_.clear();
	foodhouses_.clear();
}

