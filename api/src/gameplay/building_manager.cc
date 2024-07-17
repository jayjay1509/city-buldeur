
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

void BuildingManager::Addwoodhouse(Tile& tile,sf::Vector2f pos)
{
	if(!is_active_)
	{
		return;
	}
	//std::cout << "Tile clicked, can we finally add a house ? [" << tile.Position().x << ":" << tile.Position().y << "]" << std::endl;
	woodhouses_.emplace_back(pos.x, pos.y);
	tile.set_walkable(false);
}


void BuildingManager::Addstonehouse(Tile& tile, sf::Vector2f pos)
{
	if (!is_active_)
	{
		return;
	}
	//std::cout << "Tile clicked, can we finally add a house ? [" << tile.Position().x << ":" << tile.Position().y << "]" << std::endl;
	stonehouses_.emplace_back(pos.x, pos.y);
	tile.set_walkable(false);
}


void BuildingManager::Addfoodhouse(Tile& tile, sf::Vector2f pos)
{
	if (!is_active_)
	{
		return;
	}
	//std::cout << "Tile clicked, can we finally add a house ? [" << tile.Position().x << ":" << tile.Position().y << "]" << std::endl;
	foodhouses_.emplace_back(pos.x, pos.y);
	tile.set_walkable(false);
}

