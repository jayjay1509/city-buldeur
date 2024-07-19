#include "gameplay/Farmer.h"

#include <iostream>

#include "bttree/bt_leaf.h"
#include "bttree/BtNode.h"
#include "bttree/bt_seletor.h"
#include "bttree/bt_sequence.h"
#include "gameplay/astar.h"
#include "gameplay/sfml_vec2f.h"
#include "tilemaps/Tilemap.h"


Farmer::Farmer(float x, float y, float linear_speed, Tilemap& tilemap,sf::Vector2f maison) : tilemap_(tilemap),  walker(x, y, linear_speed) ,maison(maison)
{
	maison = getPosition();
	rect_.setPosition(shape_.getGlobalBounds().getPosition());
	rect_.setSize(shape_.getGlobalBounds().getSize());
	defineTexture(ResourceManager::Resource::kMan3);
	InitiateBehaviour();
}




void Farmer::InitiateBehaviour()
{
	Path p = astar::CalculatePath(tilemap_.GetWalkable(), last_destination(), getPosition(), 64);
	set_path(p);

	BtLeaf* check_stamina = new BtLeaf( [this]()
		{

			if (stamina_ >= 0)
				return Status::kSuccess;
			else
				return Status::kFailure;

		}
	);

	BtLeaf* seek_earth = new BtLeaf( [this]()
		{
			return seekearth();
		}
	);

	BtLeaf* gather_wood = new BtLeaf( [this]()
		{
			return GatherWood();
		}
	);

	BtLeaf* back_home = new BtLeaf( [this]()
		{
			return Back_home();
		}
	);

	BtLeaf* refill_stamina = new BtLeaf( [this]()
		{
			stamina_ = 30;
			//std::cout << "Refill Stamina : " << stamina_ << std::endl;
			return Status::kFailure;
		}
	);

	BtSelector* main_select = new BtSelector();

	bt_sequence* gather_sequence = new bt_sequence();
	bt_sequence* home_sequence = new bt_sequence();

	main_select->AddNode(gather_sequence);
	main_select->AddNode(home_sequence);

	gather_sequence->AddNode(check_stamina);
	gather_sequence->AddNode(seek_earth);
	gather_sequence->AddNode(gather_wood);

	home_sequence->AddNode(back_home);
	home_sequence->AddNode(refill_stamina);

	bt_tree_.AttachNode(main_select);

}


Status Farmer::seekearth()
{
	sf::Vector2f closestEarth = tilemap_.GetClosestearth(getPosition()); 

	if (squaredMagnitude(closestEarth - path_.final_destination_) > std::numeric_limits<float>::epsilon()) // ici
	{
		//std::cout << "Recalculate path" << std::endl;
		Path p = astar::CalculatePath(tilemap_.GetWalkable(), last_destination(), closestEarth, 64);
		set_path(p);

		// - - - - - - - - - - - - - - -
		stamina_ -= p.GetSteps().size();
	}

	if (!path_.IsAvailable())
	{
		//std::cout << "Path not available" << std::endl;
		return Status::kFailure;
	}

	float sq_mag = squaredMagnitude(getPosition() - path_.final_destination_);
	if (sq_mag < std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Arrived !!!!!!" << std::endl;
		return Status::kSuccess;
	}
	else
	{
		//std::cout << "Not arrived yet" << std::endl;
		return Status::kRunning;
	}

}


Status Farmer::Back_home()
{

	sf::Vector2f homePosition = maison;

	if (squaredMagnitude(homePosition - path_.final_destination_) > std::numeric_limits<float>::epsilon())
	{
		Path p = astar::CalculatePath(tilemap_.GetWalkable(), last_destination(), homePosition, 64);
		set_path(p);
	}

	if (!path_.IsAvailable())
	{
		//std::cout << "Path not available" << std::endl;
		return Status::kFailure;
	}

	if (squaredMagnitude(getPosition() - path_.final_destination_) < std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Arrived at home !!!!!!" << std::endl;
		return Status::kSuccess;
	}
	else
	{
		//std::cout << "Not arrived yet at home" << std::endl;
		return Status::kRunning;
	}

}




behaviour_tree::Status Farmer::GatherWood()
{
	if (tilemap_.Gatherearther(getPosition()))
	{
		//std::cout << "Cutting trees" << std::endl;
		return Status::kSuccess;
	}

	//std::cout << "not Cutting trees" << std::endl;
	return Status::kFailure;
}

void Farmer::pantsballon()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f mouse_tile_coord;
	sf::Vector2f hovered_tile_coord;
	int tile_size = 64;


	mouse_tile_coord.x = static_cast<int>(std::floor(pos.x / tile_size));
	mouse_tile_coord.y = static_cast<int>(std::floor(pos.y / tile_size));

	hovered_tile_coord.x = static_cast<float>(mouse_tile_coord.x) * tile_size;
	hovered_tile_coord.y = static_cast<float>(mouse_tile_coord.y) * tile_size;

	bool water_ = tilemap_.IsPositionInWater(hovered_tile_coord);
	if (water_)
	{
		defineTexture(ResourceManager::Resource::KBallon);
	}
	else
	{
		defineTexture(ResourceManager::Resource::kMan3);
	}


}




void Farmer::Tick()
{
	pantsballon();
	walker::Tick();
	bt_tree_.Tick();
}

void Farmer::defineTexture(ResourceManager::Resource texture)
{
	shape_.setTexture(ResourceManager::Get().GetTexture(texture));
}

Farmer::Farmer(const Farmer& w) : walker(w), tilemap_(w.tilemap_), maison(w.maison)
{
	maison = w.maison;
	stamina_ = w.stamina_;
	InitiateBehaviour();
}