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
    loadTexture(Resource::kForetCoupe1, "../resources/kenny/PNG/Default size/Tile/foret_coupe 1.png");
    loadTexture(Resource::kSand1, "../resources/kenny/PNG/Default size/Tile/sable.png");
    loadTexture(Resource::kSnow1, "../resources/kenny/PNG/Default size/Tile/snow 1.png");
    loadTexture(Resource::kStone1, "../resources/kenny/PNG/Default size/Tile/stone 1.png");
    loadTexture(Resource::kStone2, "../resources/kenny/PNG/Default size/Tile/stone 2.png");
    loadTexture(Resource::kTerre1, "../resources/kenny/PNG/Default size/Tile/terre1.png");
    loadTexture(Resource::kTerre2, "../resources/kenny/PNG/Default size/Tile/terre2.png");
    loadTexture(Resource::kWater1, "../resources/kenny/PNG/Default size/Tile/water 1.png");
    loadTexture(Resource::kMan, "../resources/kenny/PNG/Default size/Tile/man.png");
    loadTexture(Resource::kMaison1, "../resources/kenny/PNG/Default size/Tile/maison1.png");
    loadTexture(Resource::kMaison2, "../resources/kenny/PNG/Default size/Tile/maison2.png");
    loadTexture(Resource::kMaison3, "../resources/kenny/PNG/Default size/Tile/maison3.png");
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

