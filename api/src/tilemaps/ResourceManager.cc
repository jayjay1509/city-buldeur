#include <direct.h>
#include <filesystem>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <Tracy/Tracy.hpp>


#include "tilemaps/RessourceManager.h"

ResourceManager::ResourceManager() {
    LoadAllTextures();
}

void ResourceManager::LoadAllTextures() {
#ifdef TRACY_ENABLE
    ZoneScoped;
    #endif
    textures_.resize(static_cast<size_t>(Resource::End));

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

    loadTexture(Resource::foret_1, "../resources/kenny/PNG/Default size/Tile/foret1.png");
    loadTexture(Resource::foret_2, "../resources/kenny/PNG/Default size/Tile/foret 2.png");
    loadTexture(Resource::foret_3, "../resources/kenny/PNG/Default size/Tile/foret 3.png");
    loadTexture(Resource::foret_4, "../resources/kenny/PNG/Default size/Tile/foret 4.png");
    loadTexture(Resource::foret_5, "../resources/kenny/PNG/Default size/Tile/foret 5.png");
    loadTexture(Resource::foret_6, "../resources/kenny/PNG/Default size/Tile/foret 6.png");
    loadTexture(Resource::foret_7, "../resources/kenny/PNG/Default size/Tile/foret 7.png");
    loadTexture(Resource::foret_8, "../resources/kenny/PNG/Default size/Tile/foret 8.png");
    loadTexture(Resource::foret_9, "../resources/kenny/PNG/Default size/Tile/foret 9.png");
    loadTexture(Resource::foret_10, "../resources/kenny/PNG/Default size/Tile/foret 10.png");
    loadTexture(Resource::foret_11, "../resources/kenny/PNG/Default size/Tile/foret 11.png");
    loadTexture(Resource::foret_12, "../resources/kenny/PNG/Default size/Tile/foret 12.png");
    loadTexture(Resource::foret_coupe_1, "../resources/kenny/PNG/Default size/Tile/foret_coupe 1.png");
    loadTexture(Resource::foret_coupe_2, "../resources/kenny/PNG/Default size/Tile/foret_coupe 2.png");
    loadTexture(Resource::foret_coupe_3, "../resources/kenny/PNG/Default size/Tile/foret_coupe 3.png");
    loadTexture(Resource::foret_coupe_4, "../resources/kenny/PNG/Default size/Tile/foret_coupe 4.png");
    loadTexture(Resource::caisse_1, "../resources/kenny/PNG/Default size/Tile/caisse_1.png");
    loadTexture(Resource::caisse_2, "../resources/kenny/PNG/Default size/Tile/caisse_2.png");
    loadTexture(Resource::caisse_3, "../resources/kenny/PNG/Default size/Tile/caisse_3.png");
    loadTexture(Resource::caisse_4, "../resources/kenny/PNG/Default size/Tile/caisse_4.png");
    loadTexture(Resource::route_1, "../resources/kenny/PNG/Default size/Tile/route 1.png");
    loadTexture(Resource::route_2, "../resources/kenny/PNG/Default size/Tile/route 2.png");
    loadTexture(Resource::route_3, "../resources/kenny/PNG/Default size/Tile/route 3.png");
    loadTexture(Resource::route_4, "../resources/kenny/PNG/Default size/Tile/route 4.png");
    loadTexture(Resource::route_5, "../resources/kenny/PNG/Default size/Tile/route 5.png");
    loadTexture(Resource::route_6, "../resources/kenny/PNG/Default size/Tile/route 6.png");
    loadTexture(Resource::route_7, "../resources/kenny/PNG/Default size/Tile/route 7.png");
    loadTexture(Resource::route_8, "../resources/kenny/PNG/Default size/Tile/route 8.png");
    loadTexture(Resource::route_9, "../resources/kenny/PNG/Default size/Tile/route 9.png");
    loadTexture(Resource::route_10, "../resources/kenny/PNG/Default size/Tile/route 10.png");
    loadTexture(Resource::route_11, "../resources/kenny/PNG/Default size/Tile/route 11.png");
    loadTexture(Resource::route_12, "../resources/kenny/PNG/Default size/Tile/route 12.png");
    loadTexture(Resource::route_13, "../resources/kenny/PNG/Default size/Tile/route 13.png");
    loadTexture(Resource::route_14, "../resources/kenny/PNG/Default size/Tile/route 14.png");
    loadTexture(Resource::route_15, "../resources/kenny/PNG/Default size/Tile/route 15.png");
    loadTexture(Resource::route_16, "../resources/kenny/PNG/Default size/Tile/route 16.png");
    loadTexture(Resource::route_17, "../resources/kenny/PNG/Default size/Tile/route 17.png");
    loadTexture(Resource::sand_1, "../resources/kenny/PNG/Default size/Tile/sable.png");
    loadTexture(Resource::sand_2, "../resources/kenny/PNG/Default size/Tile/sable2.png");
    loadTexture(Resource::snow_1, "../resources/kenny/PNG/Default size/Tile/snow 1.png");
    loadTexture(Resource::snow_2, "../resources/kenny/PNG/Default size/Tile/snow 2.png");
    loadTexture(Resource::stone_1, "../resources/kenny/PNG/Default size/Tile/stone 1.png");
    loadTexture(Resource::stone_2, "../resources/kenny/PNG/Default size/Tile/stone 2.png");
    loadTexture(Resource::terre_1, "../resources/kenny/PNG/Default size/Tile/terre1.png");
    loadTexture(Resource::terre_2, "../resources/kenny/PNG/Default size/Tile/terre 2.png");
    loadTexture(Resource::water_1, "../resources/kenny/PNG/Default size/Tile/water 1.png");
    loadTexture(Resource::water_2, "../resources/kenny/PNG/Default size/Tile/water 2.png");
}

sf::Texture& ResourceManager::GetTexture(Resource resourceId) {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    if (resourceId >= Resource::End) {
        return blankTexture_;
    }
    return textures_[static_cast<size_t>(resourceId)];
}