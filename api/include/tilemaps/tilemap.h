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
    sf::Vector2f GetClosestTree(sf::Vector2f pos);
    sf::Vector2f GetClosestearth(sf::Vector2f pos);
    sf::Vector2f GetCloseststone(sf::Vector2f pos);

    std::vector<sf::Vector2f> GetWalkable();

    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void SaveLevelToJson(const std::string& file_name);
    void LoadLevelFromJson(const std::string& file_name);

    [[nodiscard]] bool GatherTree(sf::Vector2f pos);
    bool Gatherearther(sf::Vector2f pos);
    bool Gatherstone(sf::Vector2f pos);
    Tile* GetTile(sf::Vector2f position);
    void FindStones();
    void FindStones2();


    std::function<void(Tile&)> ClickedTile;
    Tile* tileSelected_;

private:
    // Attributs privés
    std::vector<Tile> tiles_;
    std::vector<sf::Vector2f> Trees_;
    std::vector<sf::Vector2f> Trees_cut_;

    std::vector<sf::Vector2f> Stones_;
    std::vector<sf::Vector2f> Stones_cut_;

    std::vector<sf::Vector2f> earths_;
    std::vector<sf::Vector2f> earths_cut_;
   
    

    // Méthodes privées
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   
};

#endif






