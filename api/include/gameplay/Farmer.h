#ifndef Farmer_
#define Farmer_




#include "walker.h"
#include "bttree/bt_tree.h"
#include "tilemaps/Tilemap.h"

class Farmer : public walker
{
	Tilemap& tilemap_;

	int stamina_ = 20;

	

	
public:
	behaviour_tree::BtTree bt_tree_;
	Farmer(const Farmer& w);

	Farmer(float x, float y, float linear_speed, Tilemap& tilemap, sf::Vector2f maison);

	void InitiateBehaviour();
	behaviour_tree::Status seekearth();
	behaviour_tree::Status Back_home();
	behaviour_tree::Status GatherWood();
	void pantsballon();
	behaviour_tree::Status checkStamina();
	void Tick();
	sf::Vector2f maison;

protected:
	void defineTexture(ResourceManager::Resource texture) override;
	
};




#endif
