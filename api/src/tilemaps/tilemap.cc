#include "tilemaps/tilemap.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream> 
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
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
        {sf::Color(36, 162, 88, 100), TileType::kForet2},
        {sf::Color(35, 158, 86, 100), TileType::kForet3},
        {sf::Color(30, 142, 76, 100), TileType::kForet4},
        {sf::Color(38, 169, 93, 100), TileType::kForet5},
        {sf::Color(36, 160, 87, 100), TileType::kForet6},
        {sf::Color(35, 157, 86, 100), TileType::kForet7},
        {sf::Color(35, 157, 86, 100), TileType::kForet8},
        {sf::Color(31, 143, 77, 100), TileType::kForet9},
        {sf::Color(36, 162, 88, 100), TileType::kForet10},
        {sf::Color(38, 169, 93, 100), TileType::kForet11},
        {sf::Color(36, 160, 87, 100), TileType::kForet12},
        {sf::Color(37, 169, 93, 100), TileType::kForet1},
        {sf::Color(231, 248, 255, 255), TileType::kSnow1},
        {sf::Color(230, 248, 255, 255), TileType::kSnow2},
        {sf::Color(187, 128, 67, 150), TileType::kTerre2},
        {sf::Color(186, 127, 67, 100), TileType::kTerre1},
        {sf::Color(171, 229, 248, 220), TileType::kWater1},
        {sf::Color(170, 228, 248, 220), TileType::kWater2}
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
    if (!image.loadFromFile("../resources/kenny/PNG/Default size/Tile/test3.png")) {
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
            case TileType::kForet1: resource = ResourceManager::Resource::kForet1; break;
            case TileType::kForet2: resource = ResourceManager::Resource::kForet2; break;
            case TileType::kForet3: resource = ResourceManager::Resource::kForet3; break;
            case TileType::kForet4: resource = ResourceManager::Resource::kForet4; break;
            case TileType::kForet5: resource = ResourceManager::Resource::kForet5; break;
            case TileType::kForet6: resource = ResourceManager::Resource::kForet6; break;
            case TileType::kForet7: resource = ResourceManager::Resource::kForet7; break;
            case TileType::kForet8: resource = ResourceManager::Resource::kForet8; break;
            case TileType::kForet9: resource = ResourceManager::Resource::kForet9; break;
            case TileType::kForet10: resource = ResourceManager::Resource::kForet10; break;
            case TileType::kForet11: resource = ResourceManager::Resource::kForet11; break;
            case TileType::kForet12: resource = ResourceManager::Resource::kForet12; break;
            case TileType::kSand1: resource = ResourceManager::Resource::kSand1; break;
            case TileType::kSand2: resource = ResourceManager::Resource::kSand2; break;
            case TileType::kSnow1: resource = ResourceManager::Resource::kSnow1; break;
            case TileType::kSnow2: resource = ResourceManager::Resource::kSnow2; break;
            case TileType::kTerre1: resource = ResourceManager::Resource::kTerre1; break;
            case TileType::kTerre2: resource = ResourceManager::Resource::kTerre2; break;
            case TileType::kWater1: resource = ResourceManager::Resource::kWater1; break;
            case TileType::kWater2: resource = ResourceManager::Resource::kWater2; break;
            case TileType::kMan: resource = ResourceManager::Resource::kMan; break;
            case TileType::kMaison1: resource = ResourceManager::Resource::kMaison1; break;
            case TileType::kMaison2: resource = ResourceManager::Resource::kMaison2; break;
            case TileType::kMaison3: resource = ResourceManager::Resource::kMaison3; break;
            case TileType::kMaison4: resource = ResourceManager::Resource::kMaison4; break;
            default: resource = ResourceManager::Resource::kWater1; break;
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

void Tilemap::HandleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved) {

        sf::Vector2f mousePosition = sf::Vector2f(
            event.mouseMove.x - event.mouseMove.x % playground_tile_offset_u_.x,
            event.mouseMove.y - event.mouseMove.y % playground_tile_offset_u_.y
        );


        // Unselect all
        std::for_each(tiles_.begin(), tiles_.end(), [](Tile& t) {t.Unselect(); });

        auto tileFound = std::find_if(tiles_.begin(), tiles_.end(), [&mousePosition](Tile& t) {return t.Position() == mousePosition; });
        if (tileFound != tiles_.end()) {
            tileSelected_ = &(*tileFound);
            tileSelected_->Select();
        }

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
    }
    catch (const nlohmann::json::exception& e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}
