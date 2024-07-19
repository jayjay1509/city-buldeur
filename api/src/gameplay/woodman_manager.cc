
#include "gameplay/woodman_manager.h"

#include <iostream>

#include <gameplay/building_manager.h>





void woodmanManager::Addwoodman(const Tile& tile,Tilemap& map)
{
	//std::cout << "Tile clicked, can we finally add a house ? [" << tile.Position().x << ":" << tile.Position().y << "]" << std::endl;
	std::cout << "woodman genere" << " X: "<<tile.Position().x << " Y: " << tile.Position().y << std::endl;
	woodmans_.emplace_back(tile.Position().x, tile.Position().y,64,map);
}

void woodmanManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& b : woodmans_)
	{
		target.draw(b, states);
	}
}