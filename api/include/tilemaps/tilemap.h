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



class Tilemap final : public sf::Drawable {

public:

    
    Tilemap();
    void set_time();

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
    void Findwater();
    void FindStones();
    void Findwood();
    void Findfood();
    void Remove(const sf::Vector2f& pos);

	//std::vector<sf::Vector2f> getTrees() 
	//{
 //       return Trees_;
 //   }

 //   std::vector<sf::Vector2f> getStones() 
 //   {
 //       return Stones_;
 //   }

 //   std::vector<sf::Vector2f> getEarths() 
 //   {
 //       return earths_;
 //   }

    std::function<void(Tile&)> ClickedTile;
    Tile* tileSelected_;
    void Tick();
    bool IsPositionInWater(const sf::Vector2f& pos);


    int getWood();
    int getFood();
    int getStone();
	int getday();
    int getmonth();
    int getyear();

    double getCutPercentageWood();
    double getCutPercentageStone();
    double getCutPercentageFood();

    void setWood(int val);
    void setfood(int val);
    void setstone(int val);

    void setDay(int val);
    void setMonth(int val);
    void setYear(int val);


    void setPercentage_wood(int val);
    void setPercentage_stone(int val) ;
    void setPercentage_food(int val) ;
   

private:
    int wood = 20;
    int food = 20;
    int stone = 20;
    int day;
	int month;
	int year;


    double cutPercentage_wood = 0 ;
    double cutPercentage_stone = 0;
    double cutPercentage_food = 0;

    bool foodover =  false;
    bool woodover = false;
    bool stoneover = false;




    // Attributs privés
    void RemoveIfFound(std::vector<sf::Vector2f>&, const sf::Vector2f& pos);
    
    void GrowTree();
    void Restone();
    void Refood();
   
    void Growstone();

    sf::Clock clock_;
    sf::Time interval_;
public:
    std::vector<Tile> tiles_;
    std::vector<sf::Vector2f> Trees_;
    std::vector<sf::Vector2f> Trees_cut_;
    std::vector<sf::Vector2f> Stones_;
    std::vector<sf::Vector2f> Stones_cut_;
    std::vector<sf::Vector2f> earths_;
    std::vector<sf::Vector2f> earths_cut_;
    std::vector<sf::Vector2f> water_;
    //shhhhhh vous avez rien vu 
private:   

    // Méthodes privées
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   
};

#endif






