#include <direct.h>
#include <filesystem>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <Tracy/Tracy.hpp>


#include "tilemaps/RessourceManager.h"

ResourceManager::ResourceManager() {
    LoadAllTextures();
    LoadCursors();
}

void ResourceManager::LoadAllTextures() {
#ifdef TRACY_ENABLE
    ZoneScoped;
    #endif
    textures_.resize(static_cast<size_t>(Resource::kEnd));

    auto loadTexture = [this](Resource resource, const std::string& filepath) {
        std::cerr << "Attempting to load texture: " << filepath << std::endl;
        if (!textures_[static_cast<size_t>(resource)].loadFromFile(filepath)) {
            std::cerr << "Error loading texture: " << filepath << std::endl;
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                std::cerr << "Current working directory: " << cwd << std::endl;
            }
            else {
                std::cerr << "Unable to get current working directory." << std::endl;
            }
            std::cerr << "Ensure that the file path is correct and the file exists." << std::endl;
        }
        else {
            std::cerr << "Successfully loaded texture: " << filepath << std::endl;
        }
        };

    blankTexture_.create(64, 64); // Create a simple blank texture
    blankTexture_.setSmooth(true);

    loadTexture(Resource::kForet1, "../resources/kenny/PNG/Default size/Tile/foret1.png");
    loadTexture(Resource::kForet2, "../resources/kenny/PNG/Default size/Tile/foret 2.png");
    loadTexture(Resource::kForet3, "../resources/kenny/PNG/Default size/Tile/foret 3.png");
    loadTexture(Resource::kForet4, "../resources/kenny/PNG/Default size/Tile/foret 4.png");
    loadTexture(Resource::kForet5, "../resources/kenny/PNG/Default size/Tile/foret 5.png");
    loadTexture(Resource::kForet6, "../resources/kenny/PNG/Default size/Tile/foret 6.png");
    loadTexture(Resource::kForet7, "../resources/kenny/PNG/Default size/Tile/foret 7.png");
    loadTexture(Resource::kForet8, "../resources/kenny/PNG/Default size/Tile/foret 8.png");
    loadTexture(Resource::kForet9, "../resources/kenny/PNG/Default size/Tile/foret 9.png");
    loadTexture(Resource::kForet10, "../resources/kenny/PNG/Default size/Tile/foret 10.png");
    loadTexture(Resource::kForet11, "../resources/kenny/PNG/Default size/Tile/foret 11.png");
    loadTexture(Resource::kForet12, "../resources/kenny/PNG/Default size/Tile/foret 12.png");
    loadTexture(Resource::kForetCoupe1, "../resources/kenny/PNG/Default size/Tile/foret_coupe 1.png");
    loadTexture(Resource::kForetCoupe2, "../resources/kenny/PNG/Default size/Tile/foret_coupe 2.png");
    loadTexture(Resource::kForetCoupe3, "../resources/kenny/PNG/Default size/Tile/foret_coupe 3.png");
    loadTexture(Resource::kForetCoupe4, "../resources/kenny/PNG/Default size/Tile/foret_coupe 4.png");
    loadTexture(Resource::kCaisse1, "../resources/kenny/PNG/Default size/Tile/caisse_1.png");
    loadTexture(Resource::kCaisse2, "../resources/kenny/PNG/Default size/Tile/caisse_2.png");
    loadTexture(Resource::kCaisse3, "../resources/kenny/PNG/Default size/Tile/caisse_3.png");
    loadTexture(Resource::kCaisse4, "../resources/kenny/PNG/Default size/Tile/caisse_4.png");
    loadTexture(Resource::kRoute1, "../resources/kenny/PNG/Default size/Tile/route 1.png");
    loadTexture(Resource::kRoute2, "../resources/kenny/PNG/Default size/Tile/route 2.png");
    loadTexture(Resource::kRoute3, "../resources/kenny/PNG/Default size/Tile/route 3.png");
    loadTexture(Resource::kRoute4, "../resources/kenny/PNG/Default size/Tile/route 4.png");
    loadTexture(Resource::kRoute5, "../resources/kenny/PNG/Default size/Tile/route 5.png");
    loadTexture(Resource::kRoute6, "../resources/kenny/PNG/Default size/Tile/route 6.png");
    loadTexture(Resource::kRoute7, "../resources/kenny/PNG/Default size/Tile/route 7.png");
    loadTexture(Resource::kRoute8, "../resources/kenny/PNG/Default size/Tile/route 8.png");
    loadTexture(Resource::kRoute9, "../resources/kenny/PNG/Default size/Tile/route 9.png");
    loadTexture(Resource::kRoute10, "../resources/kenny/PNG/Default size/Tile/route 10.png");
    loadTexture(Resource::kRoute11, "../resources/kenny/PNG/Default size/Tile/route 11.png");
    loadTexture(Resource::kRoute12, "../resources/kenny/PNG/Default size/Tile/route 12.png");
    loadTexture(Resource::kRoute13, "../resources/kenny/PNG/Default size/Tile/route 13.png");
    loadTexture(Resource::kRoute14, "../resources/kenny/PNG/Default size/Tile/route 14.png");
    loadTexture(Resource::kRoute15, "../resources/kenny/PNG/Default size/Tile/route 15.png");
    loadTexture(Resource::kRoute16, "../resources/kenny/PNG/Default size/Tile/route 16.png");
    loadTexture(Resource::kRoute17, "../resources/kenny/PNG/Default size/Tile/route 17.png");
    loadTexture(Resource::kSand1, "../resources/kenny/PNG/Default size/Tile/sable.png");
    loadTexture(Resource::kSand2, "../resources/kenny/PNG/Default size/Tile/sable2.png");
    loadTexture(Resource::kSnow1, "../resources/kenny/PNG/Default size/Tile/snow 1.png");
    loadTexture(Resource::kSnow2, "../resources/kenny/PNG/Default size/Tile/snow 2.png");
    loadTexture(Resource::kStone1, "../resources/kenny/PNG/Default size/Tile/stone 1.png");
    loadTexture(Resource::kStone2, "../resources/kenny/PNG/Default size/Tile/stone 2.png");
    loadTexture(Resource::kTerre1, "../resources/kenny/PNG/Default size/Tile/terre1.png");
    loadTexture(Resource::kTerre2, "../resources/kenny/PNG/Default size/Tile/terre 2.png");
    loadTexture(Resource::kWater1, "../resources/kenny/PNG/Default size/Tile/water 1.png");
    loadTexture(Resource::kWater2, "../resources/kenny/PNG/Default size/Tile/water 2.png");
    loadTexture(Resource::kMan, "../resources/kenny/PNG/Default size/Tile/man.png");
    loadTexture(Resource::kMaison1, "../resources/kenny/PNG/Default size/Tile/maison1.png");
    loadTexture(Resource::kMaison2, "../resources/kenny/PNG/Default size/Tile/maison2.png");
    loadTexture(Resource::kMaison3, "../resources/kenny/PNG/Default size/Tile/maison3.png");
    loadTexture(Resource::kMaison4, "../resources/kenny/PNG/Default size/Tile/maison4.png");
}

void ResourceManager::LoadCursors()
{

    cursor_images_.clear();
    cursor_images_.resize(static_cast<int>(CursorImage::kMax));

    //cursors_.emplace_back();
    cursor_images_.at(static_cast<int>(CursorImage::kBasic)).loadFromFile("../resources/kenny/PNG/Default size/Tile/pointe.png");
    cursor_images_.at(static_cast<int>(CursorImage::kBuild)).loadFromFile("../resources/kenny/PNG/Default size/Tile/pointe_2.png");
    

}

ResourceManager& ResourceManager::Get()
{
    static ResourceManager instance_;
    return instance_;
}

sf::Texture& ResourceManager::GetTexture(Resource resourceId) {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    if (resourceId >= Resource::kEnd) {
        return blankTexture_;
    }
    return textures_[static_cast<size_t>(resourceId)];
}


sf::Image& ResourceManager::GetCursor(CursorImage cursor_id)
{
    if (static_cast<int>(cursor_id) < cursor_images_.size()) {
        return cursor_images_.at(static_cast<int>(cursor_id));
    }
    else
    {
        return blank_cursor_image_;
    }



}

