#include "tilemaps/tilemap.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream> 
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

#include "gameplay/sfml_vec2f.h"
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif

//// Fix 1 : initiate static in the cc file
//sf::Vector2u Tilemap::playground_size_u_ = sf::Vector2u(15, 10);
//sf::Vector2u Tilemap::playground_tile_offset_u_ = sf::Vector2u(18, 18);

int generated = 0;

void Tilemap::Setup(sf::Vector2u playground_size_u, sf::Vector2u playground_tile_offset_u)
{
	playground_size_u_ = playground_size_u;
	playground_tile_offset_u_ = playground_tile_offset_u;
}
struct ColorReference {
	sf::Color color;
	TileType type;
};

float colorDistance(const sf::Color& c1, const sf::Color& c2) {
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	return std::sqrt(static_cast<float>((c1.r - c2.r) * (c1.r - c2.r)
		+ (c1.g - c2.g) * (c1.g - c2.g)
		+ (c1.b - c2.b) * (c1.b - c2.b)
		+ (c1.a - c2.a) * (c1.a + c2.a)));
}

TileType mapColorToTileType(const sf::Color& color) {
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	static const std::array<ColorReference, (int)TileType::kEnd> colorReferences = { {
		{sf::Color(100, 169, 93, 100), TileType::kForet1},
		{sf::Color(186, 127, 67, 100), TileType::kTerre1},
		{sf::Color(171, 100, 248, 100), TileType::kWater1},
		{sf::Color(86, 92, 92, 100), TileType::kStone1},
	} };


	auto minDistance = std::numeric_limits<float>::max();
	TileType closestType = TileType::kWater1; // Valeur par défaut

	for (const auto& ref : colorReferences) {
		const float distance = colorDistance(color, ref.color);
		if (distance < minDistance) {
			minDistance = distance;
			closestType = ref.type;
		}
	}

	return closestType;
}



void resizeImage(const sf::Image& originalImage, sf::Image& resizedImage)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	const sf::Vector2u originalImageSize = originalImage.getSize();
	const sf::Vector2u resizedImageSize = resizedImage.getSize();

	for (unsigned int y = 0; y < resizedImageSize.y; ++y)
	{
		for (unsigned int x = 0; x < resizedImageSize.x; ++x)
		{
			// Calculate corresponding coordinates in the original image
			unsigned int origX = static_cast<unsigned int>(static_cast<double>(x) / resizedImageSize.x * originalImageSize.x);
			unsigned int origY = static_cast<unsigned int>(static_cast<double>(y) / resizedImageSize.y * originalImageSize.y);

			// Ensure coordinates are within bounds
			origX = std::min(origX, originalImageSize.x - 1);
			origY = std::min(origY, originalImageSize.y - 1);

			// Set pixel in the resized image
			resizedImage.setPixel(x, y, originalImage.getPixel(origX, origY));
		}
	}
}





void Tilemap::Generate()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	tiles_.clear();

#ifdef TRACY_ENABLE
	TracyCZoneN(loadimage, "load a image", true);
#endif
	//---- Things to measure


	sf::Image image;
	if (!image.loadFromFile("../resources/kenny/PNG/Default size/Tile/test8.png")) {
		std::cerr << "Error loading image." << std::endl;
		return;
	}

#ifdef TRACY_ENABLE
	TracyCZoneEnd(loadimage);
#endif


#ifdef TRACY_ENABLE
	TracyCZoneN(resizeiamge, "resize", true);
#endif
	// Create a resized image with the required dimensions
	sf::Image resizedImage;
	resizedImage.create(playground_size_u_.x * playground_tile_offset_u_.x, playground_size_u_.y * playground_tile_offset_u_.y);

	// Resize the original image
	resizeImage(image, resizedImage);


#ifdef TRACY_ENABLE
	TracyCZoneEnd(resizeiamge);
#endif

	unsigned int blockCountX = playground_size_u_.x;
	unsigned int blockCountY = playground_size_u_.y;
#ifdef TRACY_ENABLE
	TracyCZoneN(linkresouce, "linkresouce", true);
#endif
	for (unsigned int y = 0; y < blockCountY; ++y)
	{
		for (unsigned int x = 0; x < blockCountX; ++x)
		{
			// Use the resized image to get the pixel color
			sf::Color color = resizedImage.getPixel(x * playground_tile_offset_u_.x + playground_tile_offset_u_.x / 2, y * playground_tile_offset_u_.y + playground_tile_offset_u_.y / 2);
			TileType tileType = mapColorToTileType(color);

			ResourceManager::Resource resource;
			switch (tileType)
			{
				// la 2eme 
			case TileType::kForet1: resource = ResourceManager::Resource::kForet1;
				Trees_.emplace_back(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);
				break;
			case TileType::kSand1: resource = ResourceManager::Resource::kSand1;
				break;
			case TileType::kSnow1: resource = ResourceManager::Resource::kSnow1;
				break;
			case TileType::kTerre1: resource = ResourceManager::Resource::kTerre1;
				earths_.emplace_back(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);
				break;
			case TileType::kWater1: resource = ResourceManager::Resource::kWater1;
				break;
			case TileType::kStone1: resource = ResourceManager::Resource::kStone1;
				Stones_.emplace_back(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);
				break;
			default: resource = ResourceManager::Resource::kWater1;
				break;
			}

			tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);


		}
	}


#ifdef TRACY_ENABLE
	TracyCZoneEnd(linkresouce);
#endif
	tileSelected_ = &(*tiles_.begin());
	tileSelected_->Unselect();
}

sf::Vector2f Tilemap::GetClosestTree(sf::Vector2f pos)
{
	sf::Vector2f closestTree;

	float closest_tree_destination = std::numeric_limits<float>::infinity();

	std::for_each(Trees_.begin(), Trees_.end(), [&closest_tree_destination, &closestTree, pos](const sf::Vector2f& tree)
		{
			float sq_dist = squaredMagnitude(tree - pos);

			if (sq_dist < closest_tree_destination)
			{
				closestTree = tree;
				closest_tree_destination = sq_dist;
			}
		});

	return closestTree;
}


sf::Vector2f Tilemap::GetClosestearth(sf::Vector2f pos)
{
	sf::Vector2f closestearth;

	float closest_earth_destination = std::numeric_limits<float>::infinity();

	std::for_each(earths_.begin(), earths_.end(), [&closest_earth_destination, &closestearth, pos](const sf::Vector2f& tree)
		{
			float sq_dist = squaredMagnitude(tree - pos);

			if (sq_dist < closest_earth_destination)
			{
				closestearth = tree;
				closest_earth_destination = sq_dist;
			}
		});

	return closestearth;
}

sf::Vector2f Tilemap::GetCloseststone(sf::Vector2f pos)
{
	sf::Vector2f closeststone;

	float closest_stone_destination = std::numeric_limits<float>::infinity();

	std::for_each(Stones_.begin(), Stones_.end(), [&closest_stone_destination, &closeststone, pos](const sf::Vector2f& tree)
		{
			float sq_dist = squaredMagnitude(tree - pos);

			if (sq_dist < closest_stone_destination)
			{
				closeststone = tree;
				closest_stone_destination = sq_dist;
			}
		});

	return closeststone;
}


std::vector<sf::Vector2f> Tilemap::GetWalkable()
{
	std::vector<sf::Vector2f> walkables;


	std::for_each(tiles_.begin(), tiles_.end(), [&walkables](const Tile& t)
		{
			if (t.Walkable())
			{
				walkables.emplace_back(t.Position());
			}
		}
	);
	return walkables;

}

void Tilemap::HandleEvent(const sf::Event& event,const sf::RenderWindow& window)
{

	sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	// Snap mouse position to the grid
	sf::Vector2f mousePosition(
		static_cast<int>(worldPos.x / playground_tile_offset_u_.x) * playground_tile_offset_u_.x,
		static_cast<int>(worldPos.y / playground_tile_offset_u_.y) * playground_tile_offset_u_.y
	);

	//if (event.type == sf::Event::MouseMoved) {

	

		// Unselect all
		std::for_each(tiles_.begin(), tiles_.end(), [](Tile& t) {t.Unselect(); });

		auto tileFound = std::find_if(tiles_.begin(), tiles_.end(), [&mousePosition](Tile& t) {return t.Position() == mousePosition; });
		if (tileFound != tiles_.end()) {
			tileSelected_ = &(*tileFound);
			tileSelected_->Select();
		}

	


	if (event.type == sf::Event::MouseButtonReleased)
	{
		// Check if the left mouse button is pressed
		if (event.mouseButton.button == sf::Mouse::Left) {
			// Code à faire pour le bouton ---------------------------------------------------
			if (ClickedTile && tileSelected_) {
				ClickedTile(*tileSelected_);
			}
			else
			{
				std::cout << "No callback defined...";
			}
		}
	}

}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	// Draw all tiles
	for (const auto& tile : tiles_)
	{
		target.draw(tile, states);
	}

	/*
	 *Draw all walkable tiles

	auto tile = tiles_.begin();
	while (tile != tiles_.end())
	{
		tile = std::find_if(tile, tiles_.end(), [](const Tile& t) {return t.Walkable(); });
		if(tile != tiles_.end())
		{
			target.draw(*tile, states);
			++tile;
		}

	}
	*/

	/*
	 *Draw only the tiles that are in the view

	auto tile = tiles_.begin();
	while (tile != tiles_.end())
	{
		tile = std::find_if(tile, tiles_.end(), [](const Tile& t) {return t.Position().x > 20 && t.Position().x < 150; });
		if (tile >= tiles_.end())
			break;

		//
		target.draw(*tile, states);
		++tile;
	}
	*/
}



void Tilemap::SaveLevelToJson(const std::string& file_name)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	std::cout << "save map 1.1 \n";

	nlohmann::json json_level;
	json_level["Y_total"] = playground_size_u_.y;
	json_level["X_total"] = playground_size_u_.x;
	json_level["pixel_x"] = playground_tile_offset_u_.x;
	json_level["pixel_y"] = playground_tile_offset_u_.y;

	json_level["tiles"] = nlohmann::json::array();
	for (const auto& tile : tiles_)
	{
		nlohmann::json tileData;
		tileData["x"] = tile.Position().x;
		tileData["y"] = tile.Position().y;
		tileData["type"] = static_cast<int>(tile.GetType());
		json_level["tiles"].push_back(tileData);
	}

	json_level["trees"] = nlohmann::json::array();
	for (const auto& tree : Trees_)
	{
		nlohmann::json treeData;
		treeData["x"] = tree.x;
		treeData["y"] = tree.y;
		json_level["trees"].push_back(treeData);
	}

	json_level["trees_cut"] = nlohmann::json::array();
	for (const auto& tree_cut : Trees_cut_)
	{
		nlohmann::json treeCutData;
		treeCutData["x"] = tree_cut.x;
		treeCutData["y"] = tree_cut.y;
		json_level["trees_cut"].push_back(treeCutData);
	}

	json_level["earths"] = nlohmann::json::array();
	for (const auto& earths : earths_)
	{
		nlohmann::json earthsData;
		earthsData["x"] = earths.x;
		earthsData["y"] = earths.y;
		json_level["earths"].push_back(earthsData);
	}

	json_level["earths_cut"] = nlohmann::json::array();
	for (const auto& earths_cut : earths_cut_)
	{
		nlohmann::json earths_cutData;
		earths_cutData["x"] = earths_cut.x;
		earths_cutData["y"] = earths_cut.y;
		json_level["earths_cut"].push_back(earths_cutData);
	}

	json_level["stones"] = nlohmann::json::array();
	for (const auto& stones : Stones_)
	{
		nlohmann::json stonesData;
		stonesData["x"] = stones.x;
		stonesData["y"] = stones.y;
		json_level["stones"].push_back(stonesData);
	}

	json_level["stones_cut"] = nlohmann::json::array();
	for (const auto& stones_cut : Stones_cut_)
	{
		nlohmann::json stones_cutData;
		stones_cutData["x"] = stones_cut.x;
		stones_cutData["y"] = stones_cut.y;
		json_level["stones_cut"].push_back(stones_cutData);
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

void Tilemap::LoadLevelFromJson(const std::string& file_name)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	// Nettoyer les vecteurs de tuiles et d'arbres existants
	tiles_.clear();
	Trees_.clear();
	Trees_cut_.clear();

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
			playground_size_u_.y = json_level["Y_total"];
			playground_size_u_.x = json_level["X_total"];
			playground_tile_offset_u_.x = json_level["pixel_x"];
			playground_tile_offset_u_.y = json_level["pixel_y"];
		}
		else
		{
			std::cerr << "Missing or invalid playground dimensions or tile offset in JSON." << std::endl;
			return;
		}

		tiles_.reserve(playground_size_u_.x * playground_size_u_.y);

		auto tiles_array = json_level["tiles"];
		for (const auto& tile_data : tiles_array)
		{
			float x = tile_data["x"];
			float y = tile_data["y"];
			int type_int = tile_data["type"];

			if (type_int >= 0 && type_int < static_cast<int>(TileType::kEnd))
			{
				TileType type = static_cast<TileType>(type_int);

				if (type_int >= 0 && type_int < static_cast<int>(ResourceManager::Resource::kEnd))
				{
					ResourceManager::Resource resource = static_cast<ResourceManager::Resource>(type_int);
					tiles_.emplace_back(resource, x, y, true, type);
				}
			}
		}

		auto trees_array = json_level["trees"];
		for (const auto& tree_data : trees_array)
		{
			float x = tree_data["x"];
			float y = tree_data["y"];
			Trees_.emplace_back(x, y);
		}

		auto trees_cut_array = json_level["trees_cut"];
		for (const auto& tree_cut_data : trees_cut_array)
		{
			float x = tree_cut_data["x"];
			float y = tree_cut_data["y"];
			Trees_cut_.emplace_back(x, y);
		}

		auto earths_array = json_level["earths"];
		for (const auto& earths_data : earths_array)
		{
			float x = earths_data["x"];
			float y = earths_data["y"];
			earths_.emplace_back(x, y);
		}

		auto earths_cut_array = json_level["earths_cut"];
		for (const auto& earths_cut_data : earths_cut_array)
		{
			float x = earths_cut_data["x"];
			float y = earths_cut_data["y"];
			earths_cut_.emplace_back(x, y);
		}

		auto stones_array = json_level["stones"];
		for (const auto& stones_data : stones_array)
		{
			float x = stones_data["x"];
			float y = stones_data["y"];
			Stones_.emplace_back(x, y);
		}

		auto stones_cut_array = json_level["stones_cut"];
		for (const auto& stones_cut_data : stones_cut_array)
		{
			float x = stones_cut_data["x"];
			float y = stones_cut_data["y"];
			Stones_cut_.emplace_back(x, y);
		}

	}
	catch (const nlohmann::json::exception& e)
	{
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
	}
}

bool Tilemap::GatherTree(sf::Vector2f pos)
{

	auto tree = std::find_if(Trees_.begin(), Trees_.end(), [pos](const sf::Vector2f& t)
		{
			return pos == t;
		});


	if (tree != Trees_.end())
	{
		Trees_cut_.emplace_back(*tree);
		Trees_.erase(tree);
		auto tile = std::find_if(tiles_.begin(), tiles_.end(), [pos](const Tile& t) {return pos == t.Position(); });
		if (tile != tiles_.end())
		{
			tile->Set_Tree(TileType::kForetCoupe1);
			
		}
		return true;
	}
	else
	{
		return false;
	}


}

bool Tilemap::Gatherearther(sf::Vector2f pos)
{

	auto eather = std::find_if(earths_.begin(), earths_.end(), [pos](const sf::Vector2f& t)
		{
			return pos == t;
		});


	if (eather != earths_.end())
	{
		earths_cut_.emplace_back(*eather);
		earths_.erase(eather);
		auto tile = std::find_if(tiles_.begin(), tiles_.end(), [pos](const Tile& t) {return pos == t.Position(); });
		if (tile != tiles_.end())
		{
			tile->Set_earther(TileType::kTerre2);

		}
		return true;
	}
	else
	{
		return false;
	}


}


bool Tilemap::Gatherstone(sf::Vector2f pos)
{

	auto eather = std::find_if(Stones_.begin(), Stones_.end(), [pos](const sf::Vector2f& t)
		{
			return pos == t;
		});


	if (eather != Stones_.end())
	{
		Stones_cut_.emplace_back(*eather);
		Stones_.erase(eather);
		auto tile = std::find_if(tiles_.begin(), tiles_.end(), [pos](const Tile& t) {return pos == t.Position(); });
		if (tile != tiles_.end())
		{
			tile->Set_Stone(TileType::kStone2);

		}
		return true;
	}
	else
	{
		return false;
	}


}


Tile* Tilemap::GetTile(sf::Vector2f position)
{
	auto tileFound = std::find_if(tiles_.begin(), tiles_.end(), [&position](Tile& t) 
		{
		return t.Position() == position;
		});

	if (tileFound != tiles_.end()) 
	{
		return &(*tileFound);
	}
	else 
	{
		return nullptr;
	}
}


void Tilemap::FindStones() {
	Stones_.clear(); 

	for (auto& tile : tiles_) {
		if (tile.GetType() == TileType::kStone1) { 
			Stones_.emplace_back(tile.Position());
		}
	}
}









