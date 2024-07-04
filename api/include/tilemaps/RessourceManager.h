#ifndef API_GRAPHICS_RESOURCEMANAGER_H
#define API_GRAPHICS_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {

public:
    enum class Resource
    {
        kForet1,
        kForet2,
        kForet3,
        kForet4,
        kForet5,
        kForet6,
        kForet7,
        kForet8,
        kForet9,
        kForet10,
        kForet11,
        kForet12,
        kForetCoupe1,
        kForetCoupe2,
        kForetCoupe3,
        kForetCoupe4,
        kCaisse1,
        kCaisse2,
        kCaisse3,
        kCaisse4,
        kRoute1,
        kRoute2,
        kRoute3,
        kRoute4,
        kRoute5,
        kRoute6,
        kRoute7,
        kRoute8,
        kRoute9,
        kRoute10,
        kRoute11,
        kRoute12,
        kRoute13,
        kRoute14,
        kRoute15,
        kRoute16,
        kRoute17,
        kSand1,
        kSand2,
        kSnow1,
        kSnow2,
        kStone1,
        kStone2,
        kTerre1,
        kTerre2,
        kWater1,
        kWater2,
        kMan,
        kMaison1,
        kMaison2,
        kMaison3,
        kMaison4,
        kEnd
	};

    enum class CursorImage
    {
        kBasic,
        kBuild,
        kMax
    };

private:
	std::vector<sf::Texture> textures_;
    std::vector<sf::Image> cursor_images_;
	sf::Texture blankTexture_;
    sf::Image blank_cursor_image_;

	void LoadAllTextures();
    void LoadCursors();

public:

	ResourceManager();

	//~ResourceManager();

    static ResourceManager& Get();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	sf::Texture& GetTexture(Resource resourceId);
    sf::Image& GetCursor(CursorImage cursor_id);

};

#endif








    