
#include "gameplay/Farmer_manager.h"

#include <iostream>

#include <gameplay/building_manager.h>




void Farmer_Manager::AddFarmer(const Tile& tile,Tilemap& map)
{
	std::cout << "woodman genere" << " X: "<<tile.Position().x << " Y: " << tile.Position().y << std::endl;
	farmers_.emplace_back(tile.Position().x, tile.Position().y,64,map,tile.Position());
	
}

void Farmer_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& b : farmers_)
	{
		target.draw(b, states);
	}
}