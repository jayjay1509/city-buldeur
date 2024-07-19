#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "ui/Ui_Button.h"
#include "tilemaps/Tilemap.h"
#include "gameplay/astar.h"
#include "gameplay/building_manager.h"
#include "gameplay/change_cursor.h"
#include "gameplay/Farmer.h"
#include "gameplay/Farmer_manager.h"
#include "gameplay/Path.h"
#include "gameplay/save.h"
#include "gameplay/stonebreaker.h"
#include "gameplay/stonebreaker_manager.h"
#include "gameplay/woodman.h"
#include "gameplay/woodman_manager.h"

class Game {
public:
    Game();
    void Run();

private:
    void HandleEvents();
    void Update();
    void UpdateCutPercentageText(std::ostringstream& oss);
    void ConstrainView();
    void Draw();
    void ResetGame();
    
    sf::RenderWindow window;
    Tilemap map;
    BuildingManager building_manager;
    save save;
    woodmanManager woodman_manager;
    stonebreakerManager stone_manager;
    Farmer_Manager farmer_manager;

    UiButton btn_save;
    UiButton btn_reset;
    UiButton btn_activate_foodhouse;
    UiButton btn_activate_woodhouse;
    UiButton btn_activate_stonehouse;

    sf::RectangleShape hovered_tile;

    sf::Vector2i mouse_pos;
    sf::Vector2f mouse_world_pos;
    sf::Vector2i mouse_tile_coord;
    sf::Vector2f hovered_tile_coord;

    int food_for_build = 20;
    int stone_for_build = 20;
    int wood_for_build = 20;

    sf::Font font;
    sf::Text woodText;
    sf::Text foodText;
    sf::Text stoneText;
    sf::Text timeText;
    sf::Text cutPercentageWoodText_;
    sf::Text cutPercentageStoneText_;
    sf::Text cutPercentageFoodText_;

    sf::View view;
    sf::View view_Hud;

    bool foodhouseActivateMode = false;
    bool foodhouseSec = false;

    bool woodhouseActivateMode = false;
    bool woodhouseSec = false;

    bool stonehouseActivateMode = false;
    bool stonehouseSec = false;
};

#endif // GAME_H
