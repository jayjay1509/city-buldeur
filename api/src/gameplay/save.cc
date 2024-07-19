#include "gameplay/save.h"
#include <fstream> 

#include "gameplay/building_manager.h"
#include "gameplay/Farmer_manager.h"
#include "gameplay/stonebreaker_manager.h"
#include "gameplay/woodman_manager.h"

void save::SaveLevelToJson(const std::string& file_name, Tilemap& tilemap ,BuildingManager& building_manager)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	std::cout << "save map 1.1 \n";

	nlohmann::json json_level;
	json_level["Y_total"] = tilemap.playground_size_u_.y;
	json_level["X_total"] = tilemap.playground_size_u_.x;
	json_level["pixel_x"] = tilemap.playground_tile_offset_u_.x;
	json_level["pixel_y"] = tilemap.playground_tile_offset_u_.y;

	json_level["wood"] = tilemap.getWood();
	json_level["food"] = tilemap.getFood();
	json_level["stone"] = tilemap.getStone();
	json_level["day"] = tilemap.getday();
	json_level["month"] = tilemap.getmonth();
	json_level["year"] = tilemap.getyear();

	json_level["tiles"] = nlohmann::json::array();
	for (const auto& tile : tilemap.tiles_)
	{
		nlohmann::json tileData;
		tileData["x"] = tile.Position().x;
		tileData["y"] = tile.Position().y;
		tileData["type"] = static_cast<int>(tile.GetType());
		tileData["walkable"] = tile.Walkable();
		json_level["tiles"].push_back(tileData);
	}

	json_level["trees"] = nlohmann::json::array();
	for (const auto& tree : tilemap.Trees_)
	{
		nlohmann::json treeData;
		treeData["x"] = tree.x;
		treeData["y"] = tree.y;
		json_level["trees"].push_back(treeData);
	}

	json_level["trees_cut"] = nlohmann::json::array();
	for (const auto& tree_cut : tilemap.Trees_cut_)
	{
		nlohmann::json treeCutData;
		treeCutData["x"] = tree_cut.x;
		treeCutData["y"] = tree_cut.y;
		json_level["trees_cut"].push_back(treeCutData);
	}

	json_level["earths"] = nlohmann::json::array();
	for (const auto& earths : tilemap.earths_)
	{
		nlohmann::json earthsData;
		earthsData["x"] = earths.x;
		earthsData["y"] = earths.y;
		json_level["earths"].push_back(earthsData);
	}

	json_level["earths_cut"] = nlohmann::json::array();
	for (const auto& earths_cut : tilemap.earths_cut_)
	{
		nlohmann::json earths_cutData;
		earths_cutData["x"] = earths_cut.x;
		earths_cutData["y"] = earths_cut.y;
		json_level["earths_cut"].push_back(earths_cutData);
	}

	json_level["stones"] = nlohmann::json::array();
	for (const auto& stones : tilemap.Stones_)
	{
		nlohmann::json stonesData;
		stonesData["x"] = stones.x;
		stonesData["y"] = stones.y;
		json_level["stones"].push_back(stonesData);
	}

	json_level["stones_cut"] = nlohmann::json::array();
	for (const auto& stones_cut : tilemap.Stones_cut_)
	{
		nlohmann::json stones_cutData;
		stones_cutData["x"] = stones_cut.x;
		stones_cutData["y"] = stones_cut.y;
		json_level["stones_cut"].push_back(stones_cutData);
	}

	json_level["water"] = nlohmann::json::array();
	for (const auto& water : tilemap.water_)
	{
		nlohmann::json WaterData;
		WaterData["x"] = water.x;
		WaterData["y"] = water.y;
		json_level["water"].push_back(WaterData);
	}

	json_level["woodhouses"] = nlohmann::json::array();
	for (const auto& woodhouse_pos : building_manager.GetWoodhousePositions()) {
		nlohmann::json houseData;
		houseData["x"] = woodhouse_pos.x;
		houseData["y"] = woodhouse_pos.y;
		json_level["woodhouses"].push_back(houseData);
	}

	json_level["stonehouses"] = nlohmann::json::array();
	for (const auto& stonehouse_pos : building_manager.GetStonehousePositions()) {
		nlohmann::json houseData;
		houseData["x"] = stonehouse_pos.x;
		houseData["y"] = stonehouse_pos.y;
		json_level["stonehouses"].push_back(houseData);
	}

	json_level["foodhouses"] = nlohmann::json::array();
	for (const auto& foodhouse_pos : building_manager.GetFoodhousePositions()) {
		nlohmann::json houseData;
		houseData["x"] = foodhouse_pos.x;
		houseData["y"] = foodhouse_pos.y;
		json_level["foodhouses"].push_back(houseData);
	}

	// Écrire le JSON formaté dans le fichier
	std::ofstream file(file_name);
	if (file.is_open()) {
		file << json_level.dump(4);
		file.close();
	}
	else {
		std::cerr << "Failed to open file for writing: " << file_name << std::endl;
	}
}

void save::LoadLevelFromJson(const std::string& file_name, Tilemap& tilemap , BuildingManager& building_manager,woodmanManager& woodman_manager,Farmer_Manager& farmer_manager,stonebreakerManager& stonebreaker)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	tilemap.tiles_.clear();
	tilemap.Trees_.clear();
	tilemap.Trees_cut_.clear();
	tilemap.Stones_.clear();
	tilemap.Stones_cut_.clear();
	tilemap.earths_.clear();
	tilemap.earths_cut_.clear();
	woodman_manager.woodmans_.clear();
	farmer_manager.farmers_.clear();
	stonebreaker.stonebreakers_.clear();
	building_manager.ClearAll();

	std::cout << "load map 1 \n";


	// Ouvrir le fichier JSON
	std::ifstream file(file_name);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << file_name << std::endl;
		return;
	}

	try
	{
		nlohmann::json json_level;
		file >> json_level;
		file.close();

		if (json_level.contains("Y_total") && json_level.contains("X_total") &&
			json_level.contains("pixel_x") && json_level.contains("pixel_y"))
		{
			tilemap.playground_size_u_.y = json_level["Y_total"];
			tilemap.playground_size_u_.x = json_level["X_total"];
			tilemap.playground_tile_offset_u_.x = json_level["pixel_x"];
			tilemap.playground_tile_offset_u_.y = json_level["pixel_y"];
		}
		else
		{
			std::cerr << "Missing or invalid playground dimensions or tile offset in JSON." << std::endl;
			return;
		}

		if (json_level.contains("wood")) tilemap.setWood(json_level["wood"]);
		if (json_level.contains("food")) tilemap.setfood(json_level["food"]);
		if (json_level.contains("stone")) tilemap.setstone(json_level["stone"]);
		//if (json_level.contains("day")) tilemap.setDay(json_level["day"]);
		//if (json_level.contains("month")) tilemap.setMonth(json_level["month"]) ;
		//if (json_level.contains("year")) tilemap.setYear(json_level["year"]) ;

		tilemap.tiles_.reserve(tilemap.playground_size_u_.x * tilemap.playground_size_u_.y);

		auto tiles_array = json_level["tiles"];
		for (const auto& tile_data : tiles_array)
		{
			float x = tile_data["x"];
			float y = tile_data["y"];
			int type_int = tile_data["type"];
			bool walkable = tile_data["walkable"];

			if (type_int >= 0 && type_int < static_cast<int>(TileType::kEnd))
			{
				TileType type = static_cast<TileType>(type_int);

				if (type_int >= 0 && type_int < static_cast<int>(ResourceManager::Resource::kEnd))
				{
					ResourceManager::Resource resource = static_cast<ResourceManager::Resource>(type_int);
					tilemap.tiles_.emplace_back(resource, x, y, walkable, type);
				}
			}
		}

		auto trees_array = json_level["trees"];
		for (const auto& tree_data : trees_array)
		{
			float x = tree_data["x"];
			float y = tree_data["y"];
			tilemap.Trees_.emplace_back(x, y);
		}

		auto trees_cut_array = json_level["trees_cut"];
		for (const auto& tree_cut_data : trees_cut_array)
		{
			float x = tree_cut_data["x"];
			float y = tree_cut_data["y"];
			tilemap.Trees_cut_.emplace_back(x, y);
		}

		auto earths_array = json_level["earths"];
		for (const auto& earths_data : earths_array)
		{
			float x = earths_data["x"];
			float y = earths_data["y"];
			tilemap.earths_.emplace_back(x, y);
		}

		auto earths_cut_array = json_level["earths_cut"];
		for (const auto& earths_cut_data : earths_cut_array)
		{
			float x = earths_cut_data["x"];
			float y = earths_cut_data["y"];
			tilemap.earths_cut_.emplace_back(x, y);
		}

		auto stones_array = json_level["stones"];
		for (const auto& stones_data : stones_array)
		{
			float x = stones_data["x"];
			float y = stones_data["y"];
			tilemap.Stones_.emplace_back(x, y);
		}

		auto stones_cut_array = json_level["stones_cut"];
		for (const auto& stones_cut_data : stones_cut_array)
		{
			float x = stones_cut_data["x"];
			float y = stones_cut_data["y"];
			tilemap.Stones_cut_.emplace_back(x, y);
		}

		auto water_array = json_level["water"];
		for (const auto& WaterData : water_array)
		{
			float x = WaterData["x"];
			float y = WaterData["y"];
			tilemap.water_.emplace_back(x, y);
		}

		auto woodhouses_array = json_level["woodhouses"];
		for (const auto& houseData : woodhouses_array) {
			float x = houseData["x"];
			float y = houseData["y"];
			building_manager.Addwoodhouse(*tilemap.GetTile (sf::Vector2f(x, y)), sf::Vector2f(x, y), tilemap);
			woodman_manager.Addwoodman(*tilemap.GetTile(sf::Vector2f(x, y)), tilemap);
		}

		auto stonehouses_array = json_level["stonehouses"];
		for (const auto& houseData : stonehouses_array) {
			float x = houseData["x"];
			float y = houseData["y"];
			building_manager.Addstonehouse(*tilemap.GetTile(sf::Vector2f(x, y)), sf::Vector2f(x, y), tilemap);
			stonebreaker.Addstonebreaker(*tilemap.GetTile(sf::Vector2f(x, y)), tilemap);
		}

		auto foodhouses_array = json_level["foodhouses"];
		for (const auto& houseData : foodhouses_array) {
			float x = houseData["x"];
			float y = houseData["y"];
			building_manager.Addfoodhouse(*tilemap.GetTile(sf::Vector2f(x, y)), sf::Vector2f(x, y), tilemap);
			farmer_manager.AddFarmer(*tilemap.GetTile(sf::Vector2f(x, y)), tilemap);
		}

	}
	catch (const nlohmann::json::exception& e)
	{
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
	}
}