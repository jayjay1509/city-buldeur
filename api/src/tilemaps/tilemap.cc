#include "tilemaps/tilemap.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream> 
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <Tracy/Tracy.hpp>

//// Fix 1 : initiate static in the cc file
//sf::Vector2u Tilemap::playground_size_u_ = sf::Vector2u(15, 10);
//sf::Vector2u Tilemap::playground_tile_offset_u_ = sf::Vector2u(18, 18);



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
    static const std::array<ColorReference, (int)TileType::End> colorReferences = { {
        {sf::Color(36, 162, 88, 100), TileType::foret_2},
        {sf::Color(35, 158, 86, 100), TileType::foret_3},
        {sf::Color(30, 142, 76, 100), TileType::foret_4},
        {sf::Color(38, 169, 93, 100), TileType::foret_5},
        {sf::Color(36, 160, 87, 100), TileType::foret_6},
        {sf::Color(35, 157, 86, 100), TileType::foret_7},
        {sf::Color(35, 157, 86, 100), TileType::foret_8},
        {sf::Color(31, 143, 77, 100), TileType::foret_9},
        {sf::Color(36, 162, 88, 100), TileType::foret_10},
        {sf::Color(38, 169, 93, 100), TileType::foret_11},
        {sf::Color(36, 160, 87, 100), TileType::foret_12},
        {sf::Color(37, 169, 93, 100), TileType::foret_1},
        {sf::Color(231, 248, 255, 255), TileType::snow_1},
        {sf::Color(230, 248, 255, 255), TileType::snow_2},
        {sf::Color(187, 128, 67, 150), TileType::terre_2},
        {sf::Color(186, 127, 67, 100), TileType::terre_1},
        {sf::Color(171, 229, 248, 220), TileType::water_1},
        {sf::Color(170, 228, 248, 220), TileType::water_2}
    } };
    

    auto minDistance = std::numeric_limits<float>::max();
    TileType closestType = TileType::water_1; // Valeur par défaut

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
    sf::Image image;
    if (!image.loadFromFile("../resources/kenny/PNG/Default size/Tile/test3.png")) {
        std::cerr << "Error loading image." << std::endl;
        return;
    }

    // Create a resized image with the required dimensions
    sf::Image resizedImage;
    resizedImage.create(playground_size_u_.x * playground_tile_offset_u_.x, playground_size_u_.y * playground_tile_offset_u_.y);

    // Resize the original image
    resizeImage(image, resizedImage);

    unsigned int blockCountX = playground_size_u_.x;
    unsigned int blockCountY = playground_size_u_.y;

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
            case TileType::foret_1: resource = ResourceManager::Resource::foret_1; break;
            case TileType::foret_2: resource = ResourceManager::Resource::foret_2; break;
            case TileType::foret_3: resource = ResourceManager::Resource::foret_3; break;
            case TileType::foret_4: resource = ResourceManager::Resource::foret_4; break;
            case TileType::foret_5: resource = ResourceManager::Resource::foret_5; break;
            case TileType::foret_6: resource = ResourceManager::Resource::foret_6; break;
            case TileType::foret_7: resource = ResourceManager::Resource::foret_7; break;
            case TileType::foret_8: resource = ResourceManager::Resource::foret_8; break;
            case TileType::foret_9: resource = ResourceManager::Resource::foret_9; break;
            case TileType::foret_10: resource = ResourceManager::Resource::foret_10; break;
            case TileType::foret_11: resource = ResourceManager::Resource::foret_11; break;
            case TileType::foret_12: resource = ResourceManager::Resource::foret_12; break;
            case TileType::sand_1: resource = ResourceManager::Resource::sand_1; break;
            case TileType::sand_2: resource = ResourceManager::Resource::sand_2; break;
            case TileType::snow_1: resource = ResourceManager::Resource::snow_1; break;
            case TileType::snow_2: resource = ResourceManager::Resource::snow_2; break;
            case TileType::terre_1: resource = ResourceManager::Resource::terre_1; break;
            case TileType::terre_2: resource = ResourceManager::Resource::terre_2; break;
            case TileType::water_1: resource = ResourceManager::Resource::water_1; break;
            case TileType::water_2: resource = ResourceManager::Resource::water_2; break;
            default: resource = ResourceManager::Resource::water_1; break;
            }

            tiles_.emplace_back(resource, x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y, true, tileType);
        }
    }
}



void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

    for (const auto& tile : tiles_)
    {
        target.draw(tile, states);
    }

}


void Tilemap::SaveLevelToJson(const std::string& file_name)
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

    nlohmann::json json_level;
    json_level["Y_total"] = playground_size_u_.y;
    json_level["x_total"] = playground_size_u_.x;
	json_level["pixel.x"] = playground_tile_offset_u_.y;
    json_level["pixel.y"] = playground_tile_offset_u_.x;




    json_level["tiles"] = nlohmann::json::array();

    for (const auto& tile : tiles_)
    {
        json tileData;
        
        tileData["x"] = tile.Position().x;
        tileData["y"] = tile.Position().y;

        int toto = static_cast<int>(tile.GetType());
        tileData["type"] = toto;

        json_level["tiles"].push_back(tileData);

    }

    //Write the formatted JSON to the file
    std::ofstream file(file_name);
    file << json_level.dump(4);
    file.close();
}


void Tilemap::LoadLevelFromJson(const std::string& file_name)
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    // Nettoyer le vecteur de tuiles existant
    tiles_.clear();

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

        
        if (json_level.contains("Y_total") && json_level.contains("x_total"))
        {
            playground_size_u_.y = json_level["Y_total"];
            playground_size_u_.x = json_level["x_total"];
        }
        else
        {
            std::cerr << "Missing or invalid playground dimensions in JSON." << std::endl;
            return;
        }

        if (json_level.contains("pixel.x") && json_level.contains("pixel.y"))
        {
            playground_tile_offset_u_.y = json_level["pixel.x"];
            playground_tile_offset_u_.x = json_level["pixel.y"];
        }
        else
        {
            std::cerr << "Missing or invalid playground tile offset in JSON." << std::endl;
            return;
        }

        
        tiles_.reserve(playground_size_u_.x * playground_size_u_.y);

        
        auto tiles_array = json_level["tiles"];
        for (auto& tile_data : tiles_array)
        {
            
            float x = tile_data["x"];
            float y = tile_data["y"];
            int type_int = tile_data["type"];

            
            if (type_int >= 0 && type_int < static_cast<int>(TileType::End))
            {
                TileType type = static_cast<TileType>(type_int);

                
                if (type_int >= 0 && type_int < static_cast<int>(ResourceManager::Resource::End))
                {
                    ResourceManager::Resource resource = static_cast<ResourceManager::Resource>(type_int);

                    
                    tiles_.emplace_back(resource, x, y, true, type);
                }
            }
        }
    }
    catch (const nlohmann::json::exception& e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}
