#ifndef API_GRAPHICS_TILEMAP_H_
#define API_GRAPHICS_TILEMAP_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include "tilemaps/tile.h"

using json = nlohmann::json;

// Enumération des types de tuiles


class Tilemap final : public sf::Drawable {
public:
    // Constructeur par défaut
    Tilemap() = default;

    sf::Vector2u playground_size_u_;
    sf::Vector2u playground_tile_offset_u_;

    // Méthodes publiques
    void Setup(sf::Vector2u playground_size_u, sf::Vector2u playground_tile_offset_u);
    void Generate();

    std::vector<sf::Vector2f> GetWalkable();

    void HandleEvent(const sf::Event& event);
    void SaveLevelToJson(const std::string& file_name);
    void LoadLevelFromJson(const std::string& file_name);
    std::function<void(Tile&)> ClickedTile;
    Tile* tileSelected_;

private:
    // Attributs privés
    std::vector<Tile> tiles_;
   
    

    // Méthodes privées
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   
};

#endif






