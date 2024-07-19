
#ifndef API_SAVE_H_
#define API_SAVE_H_

#include "building_manager.h"
#include "Farmer_manager.h"
#include "stonebreaker_manager.h"
#include "woodman_manager.h"
#include "tilemaps/Tilemap.h"

class save 
{

public:

	void SaveLevelToJson(const std::string& file_name, Tilemap& tilemap, BuildingManager& building_manager);
	void LoadLevelFromJson(const std::string& file_name, Tilemap& tilemap, BuildingManager& building_manager, woodmanManager& woodman_manager, Farmer_Manager
	                       & farmer_manager, stonebreakerManager& stonebreaker);
};




#endif
