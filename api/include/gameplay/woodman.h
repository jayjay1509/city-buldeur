#ifndef woodman_
#define woodman_




#include "walker.h"
#include "bttree/bt_tree.h"
#include "tilemaps/Tilemap.h"

class woodman : public walker
{
	Tilemap& tilemap_;

	int stamina_ = 20;

	
public:
	behaviour_tree::BtTree bt_tree_;
	woodman(const woodman& w);

	woodman(float x, float y, float linear_speed, Tilemap& tilemap);

	void InitiateBehaviour();
	behaviour_tree::Status seekwood();
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
