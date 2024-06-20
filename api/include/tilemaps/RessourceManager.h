#ifndef API_GRAPHICS_RESOURCEMANAGER_H
#define API_GRAPHICS_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {

public:
	enum class Resource
	{
        foret_1,
        foret_2,
        foret_3,
        foret_4,
        foret_5,
        foret_6,
        foret_7,
        foret_8,
        foret_9,
        foret_10,
        foret_11,
        foret_12,
        foret_coupe_1,
        foret_coupe_2,
        foret_coupe_3,
        foret_coupe_4,
        caisse_1,
        caisse_2,
        caisse_3,
        caisse_4,
        route_1,
        route_2,
        route_3,
        route_4,
        route_5,
        route_6,
        route_7,
        route_8,
        route_9,
        route_10,
        route_11,
        route_12,
        route_13,
        route_14,
        route_15,
        route_16,
        route_17,
        sand_1,
        sand_2,
        snow_1,
        snow_2,
        stone_1,
        stone_2,
        terre_1,
        terre_2,
        water_1,
        water_2,
        End
	};

private:
	std::vector<sf::Texture> textures_;
	sf::Texture blankTexture_;

	void LoadAllTextures();

public:
	static ResourceManager& Get() {
		static ResourceManager instance_;
		return instance_;
	}


	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	sf::Texture& GetTexture(Resource resourceId);

};

#endif