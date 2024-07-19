#include "tilemaps/tilemap.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream> 
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>


#include "gameplay/Farmer.h"
#include "gameplay/sfml_vec2f.h"
#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif

//// Fix 1 : initiate static in the cc file
//sf::Vector2u Tilemap::playground_size_u_ = sf::Vector2u(15, 10);
//sf::Vector2u Tilemap::playground_tile_offset_u_ = sf::Vector2u(18, 18);

int generated = 0;

Tilemap::Tilemap() : interval_(sf::seconds(1))
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm* now_tm = std::localtime(&now_c);

	day = now_tm->tm_mday;
	month = now_tm->tm_mon + 1; 
	year = now_tm->tm_year + 1900;
}

void Tilemap::set_time()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm* now_tm = std::localtime(&now_c);

	day = now_tm->tm_mday;
	month = now_tm->tm_mon + 1;
	year = now_tm->tm_year + 1900;
}

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
				tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);
				Trees_.emplace_back(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);
				break;
			case TileType::kSand1: resource = ResourceManager::Resource::kSand1;
				tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);
				break;
			case TileType::kSnow1: resource = ResourceManager::Resource::kSnow1;
				tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);
				break;
			case TileType::kTerre1: resource = ResourceManager::Resource::kTerre1;
				tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);
				earths_.emplace_back(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);
				break;
			case TileType::kWater1: resource = ResourceManager::Resource::kWater1;
				water_.emplace_back(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);
				tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, false, tileType);
				break;
			case TileType::kStone1: resource = ResourceManager::Resource::kStone1;
				tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);
				Stones_.emplace_back(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);
				break;
			default: resource = ResourceManager::Resource::Kgreen;
				tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);
				break;
			}

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
	for (const auto& tile : tiles_)
	{
		target.draw(tile, states);
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
		wood++;
		auto tile = std::find_if(tiles_.begin(), tiles_.end(), [pos](const Tile& t) {return pos == t.Position(); });
		if (tile != tiles_.end())
		{
			tile->Set_Tree_cut(TileType::kForetCoupe1);
			
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
		food++;
		auto tile = std::find_if(tiles_.begin(), tiles_.end(), [pos](const Tile& t) {return pos == t.Position(); });
		if (tile != tiles_.end())
		{
			tile->Set_earther_cut(TileType::kTerre2);

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
		stone++;
		auto tile = std::find_if(tiles_.begin(), tiles_.end(), [pos](const Tile& t) {return pos == t.Position(); });
		if (tile != tiles_.end())
		{
			tile->Set_Stone_cut(TileType::kStone2);

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

void Tilemap::Findwater()
{
	water_.clear();
	int water = 0;

	for (auto& tile : tiles_) {
		if (tile.GetType() == TileType::kWater1) {
			std::cout << water <<" yo water is here \n";
			water++;
			water_.emplace_back(tile.Position());
		}
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

void Tilemap::Findwood() {
	Trees_.clear();

	for (auto& tile : tiles_) {
		if (tile.GetType() == TileType::kForet1) {
			Trees_.emplace_back(tile.Position());
		}
	}
}

void Tilemap::Findfood() {
	earths_.clear();

	for (auto& tile : tiles_) {
		if (tile.GetType() == TileType::kTerre1) {
			earths_.emplace_back(tile.Position());
		}
	}
}

void Tilemap::Remove(const sf::Vector2f& pos)
{
	RemoveIfFound(Trees_, pos);
	RemoveIfFound(Stones_, pos);
	RemoveIfFound(earths_, pos);
}


void Tilemap::RemoveIfFound(std::vector<sf::Vector2f>& vec, const sf::Vector2f& pos)
{
	auto it = std::remove_if(vec.begin(), vec.end(), [&](const sf::Vector2f& tile)
		{
			return tile.x == pos.x && tile.y == pos.y;
		});

	if (it != vec.end())
	{
		vec.erase(it, vec.end());
	}
}

void Tilemap::Tick() {

	if (clock_.getElapsedTime() >= interval_) 
	{
		day++;
		if (day > 30) 
		{
			day = 1;
			month++;
			if (month > 12) 
			{
				month = 1;
				year++;
			}
		}


		GrowTree();
		Restone();
		Refood();
		clock_.restart();
	}
}

void Tilemap::GrowTree() {
	if (Trees_cut_.empty()) {
		return; 
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, Trees_cut_.size() - 1);

	int index = dis(gen);
	sf::Vector2f position = Trees_cut_[index];

	size_t totalTrees = Trees_.size();
	size_t cutTrees = Trees_cut_.size();

	if (totalTrees == 0) {
		return;
	}

	cutPercentage_wood = static_cast<double>(cutTrees) / totalTrees * 100.0;

	if (cutPercentage_wood >= 90.0)
	{
		// Si 90% ou plus des arbres sont coupés, ne pas faire repousser les arbres
		//std::cout << "90% ou plus des arbres sont coupés. Pas de repousse d'arbre." << std::endl;
		woodover = true;
		return;
	}

	Trees_.emplace_back(position);

	Trees_cut_.erase(Trees_cut_.begin() + index);


	auto tile = std::find_if(tiles_.begin(), tiles_.end(), [position](const Tile& t) {
		return t.Position() == position;
		});

	if (tile != tiles_.end()) 
	{
		tile->Set_Tree(TileType::kTerre1); 
	}


	
}

void Tilemap::Restone()
{
	if (Stones_cut_.empty())
	{
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, Stones_cut_.size() - 1);

	int index = dis(gen);
	sf::Vector2f position = Stones_cut_[index];

	size_t totalstone = Stones_.size();
	size_t cutstone = Stones_cut_.size();

	if (totalstone == 0) {
		return;
	}

	cutPercentage_stone = static_cast<double>(cutstone) / totalstone * 100.0;

	if (cutPercentage_stone >= 90.0)
	{
		// Si 90% ou plus des arbres sont coupés, ne pas faire repousser les arbres
		//std::cout << "90% ou plus des arbres sont coupés. Pas de repousse d'arbre." << std::endl;
		stoneover = true;
		return;
	}


	Stones_.emplace_back(position);

	Stones_cut_.erase(Stones_cut_.begin() + index);


	auto tile = std::find_if(tiles_.begin(), tiles_.end(), [position](const Tile& t) {
		return t.Position() == position;
		});

	if (tile != tiles_.end())
	{
		tile->Set_Stone(TileType::kStone1);
	}


	
}




void Tilemap::Refood()
{
	if (earths_cut_.empty())
	{
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, earths_cut_.size() - 1);

	int index = dis(gen);
	sf::Vector2f position = earths_cut_[index];

	size_t totalfood = earths_.size();
	size_t cutfood = earths_cut_.size();

	if (totalfood == 0) {
		return;
	}

	cutPercentage_food = static_cast<double>(cutfood) / totalfood * 100.0;

	if (cutPercentage_food >= 90.0)
	{
		// Si 90% ou plus des arbres sont coupés, ne pas faire repousser les arbres
		//std::cout << "90% ou plus des arbres sont coupés. Pas de repousse d'arbre." << std::endl;
		foodover = true;
		return;
	}

	earths_.emplace_back(position);

	earths_cut_.erase(earths_cut_.begin() + index);

	auto tile = std::find_if(tiles_.begin(), tiles_.end(), [position](const Tile& t) {
		return t.Position() == position;
		});

	if (tile != tiles_.end())
	{
		tile->Set_earther(TileType::kTerre1);
	}
}

bool Tilemap::IsPositionInWater(const sf::Vector2f& pos) 
{
	for (const auto& waterPos : water_) {

		if (waterPos == pos) 
		{
			return true;
		}
	}
	return false;
}

int Tilemap::getWood()
{
	return wood;
}

int Tilemap::getFood()
{
	return food;
}

int Tilemap::getStone()
{
	return stone;
}

int Tilemap::getday()
{
	return day;
}

int Tilemap::getmonth()
{
	return month;
}

int Tilemap::getyear()
{
	return year;
}

double Tilemap::getCutPercentageWood() 
{
	return cutPercentage_wood;
}

double Tilemap::getCutPercentageStone() 
{
	return cutPercentage_stone;
}

double Tilemap::getCutPercentageFood() 
{
	return cutPercentage_food;
}

void Tilemap::setWood(int val)
{
	wood -= val;
}

void Tilemap::setfood(int val)
{
	food -= val;
}

void Tilemap::setstone(int val)
{
	stone -= val;
}

void Tilemap::setDay(int val)
{
	day = val;
}

void Tilemap::setMonth(int val)
{
	month = val;
}

void Tilemap::setYear(int val)
{
	year = val;
}
