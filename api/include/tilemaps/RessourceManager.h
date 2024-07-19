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
        kForetCoupe1,
        kSand1,
        kSnow1,
        kStone1,
        kStone2,
        kTerre1,
        kTerre2,
        kWater1,
        kMan,
        kMan2,
        kMan3,
        kMaison1,
        kMaison2,
        kMaison3,
        Kgreen,
        KBallon,
        KButtongren,
        KButtonred,
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








    