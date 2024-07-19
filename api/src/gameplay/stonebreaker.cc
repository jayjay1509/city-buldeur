#include "gameplay/stonebreaker.h"

#include <iostream>

#include "bttree/bt_leaf.h"
#include "bttree/BtNode.h"
#include "bttree/bt_seletor.h"
#include "bttree/bt_sequence.h"
#include "gameplay/astar.h"
#include "gameplay/sfml_vec2f.h"
#include "tilemaps/Tilemap.h"


stonebreaker::stonebreaker(float x, float y, float linear_speed, Tilemap& tilemap) :tilemap_(tilemap), walker(x, y, linear_speed)
{
	maison = getPosition();
	std::cout << maison.x << maison.y << "\n";
	rect_.setPosition(shape_.getGlobalBounds().getPosition());
	rect_.setSize(shape_.getGlobalBounds().getSize());
	defineTexture(ResourceManager::Resource::kMan2);
	InitiateBehaviour();
}




void stonebreaker::InitiateBehaviour()
{
	Path p = astar::CalculatePath(tilemap_.GetWalkable(), last_destination(), getPosition(), 64);
	set_path(p);

	BtLeaf* check_stamina = new BtLeaf( [this]()
		{

			//std::cout << "Check Stamina : " << stamina_ << std::endl;

			if (stamina_ >= 0)
				return Status::kSuccess;
			else
				return Status::kFailure;

		}
	);

	BtLeaf* seek_wood = new BtLeaf( [this]()
		{
			return seekstone();
		}
	);

	BtLeaf* gather_wood = new BtLeaf( [this]()
		{
			return Gatherstone();
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
	gather_sequence->AddNode(seek_wood);
	gather_sequence->AddNode(gather_wood);

	home_sequence->AddNode(back_home);
	home_sequence->AddNode(refill_stamina);

	bt_tree_.AttachNode(main_select);

}


Status stonebreaker::seekstone()
{
	sf::Vector2f closeststone = tilemap_.GetCloseststone(getPosition());

	if (squaredMagnitude(closeststone - path_.final_destination_) > std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Recalculate path" << std::endl;
		Path p = astar::CalculatePath(tilemap_.GetWalkable(), last_destination(), closeststone, 64);
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


Status stonebreaker::Back_home()
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




behaviour_tree::Status stonebreaker::Gatherstone()
{
	if (tilemap_.Gatherstone(getPosition()))
	{
		//std::cout << "Cutting trees" << std::endl;
		return Status::kSuccess;
	}

	//std::cout << "not Cutting trees" << std::endl;
	return Status::kFailure;
}

void stonebreaker::pantsballon()
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
		defineTexture(ResourceManager::Resource::kMan2);
	}


}




void stonebreaker::Tick()
{
	pantsballon();
	walker::Tick();
	bt_tree_.Tick();
}

void stonebreaker::defineTexture(ResourceManager::Resource texture)
{
	shape_.setTexture(ResourceManager::Get().GetTexture(texture));
}

stonebreaker::stonebreaker(const stonebreaker& w) : walker(w), tilemap_(w.tilemap_) , maison(w.maison)
{
	maison = w.maison;
	stamina_ = w.stamina_;
	InitiateBehaviour();
}