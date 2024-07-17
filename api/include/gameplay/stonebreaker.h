#ifndef stonebreaker_
#define stonebreaker_




#include "walker.h"
#include "bttree/bt_tree.h"
#include "tilemaps/Tilemap.h"

class stonebreaker : public walker
{
	Tilemap& tilemap_;

	int stamina_ = 20;

	
public:
	behaviour_tree::BtTree bt_tree_;
	stonebreaker(const stonebreaker& w);

	stonebreaker(float x, float y, float linear_speed, Tilemap& tilemap);

	void InitiateBehaviour();
	behaviour_tree::Status seekstone();
	behaviour_tree::Status Back_home();
	behaviour_tree::Status Gatherstone();
	behaviour_tree::Status checkStamina();
	void Tick();

protected:
	void defineTexture(ResourceManager::Resource texture) override;
	
};




#endif
