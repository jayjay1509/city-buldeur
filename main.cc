#include <SFML/Graphics.hpp>
#include "ui/Ui_Button.h"
#include "tilemaps/Tilemap.h"
#include <iostream>

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

#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

const float MIN_ZOOM = 0.5f;
const float MAX_ZOOM = 3.0f;
const sf::Vector2f VIEW_SIZE(1200, 800);

int main() {

    BuildingManager building_manager;
    save save;
    woodmanManager woodman_manager;
    stonebreakerManager stone_manager;
    Farmer_Manager farmer_manager;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Tilemap");
    ChangeCursor::BasicCursor(window);
    window.setFramerateLimit(60);

    int food_for_build = 20;
    int stone_for_build = 20;
    int wood_for_build = 20;


    Tilemap map;
    map.Setup(sf::Vector2u(120, 120), sf::Vector2u(64, 64));
    save.LoadLevelFromJson("mapsave2.json", map, building_manager, woodman_manager, farmer_manager, stone_manager);
    //map.LoadLevelFromJson("map.json");

    sf::Vector2i mouse_pos;
    sf::Vector2f mouse_world_pos;
    sf::Vector2i mouse_tile_coord;
    sf::Vector2f hovered_tile_coord;

    sf::Vector2f tile_size(map.playground_tile_offset_u_.x, map.playground_tile_offset_u_.y);

   
    // btn_generate.setScale(0.5f, 0.5f);

    sf::Font font;
    sf::Text woodText;
    sf::Text foodText;
    sf::Text stoneText;
    sf::Text timeText;
    sf::Text cutPercentageWoodText_;
    sf::Text cutPercentageStoneText_;
    sf::Text cutPercentageFoodText_;

	font.loadFromFile("../resources/fonts/arial.ttf");
    woodText.setFont(font);
    woodText.setCharacterSize(24);
    woodText.setFillColor(sf::Color::Black);
    woodText.setPosition(10, 10); 

    foodText.setFont(font);
    foodText.setCharacterSize(24);
    foodText.setFillColor(sf::Color::Black);
    foodText.setPosition(10, 40); 

    stoneText.setFont(font);
    stoneText.setCharacterSize(24);
    stoneText.setFillColor(sf::Color::Black);
    stoneText.setPosition(10, 70);

    cutPercentageWoodText_.setFont(font);
    cutPercentageWoodText_.setCharacterSize(24);
    cutPercentageWoodText_.setFillColor(sf::Color::Black);
    cutPercentageWoodText_.setPosition(window.getSize().x - 200, 40);

    cutPercentageStoneText_.setFont(font);
    cutPercentageStoneText_.setCharacterSize(24);
    cutPercentageStoneText_.setFillColor(sf::Color::Black);
    cutPercentageStoneText_.setPosition(window.getSize().x - 200, 70);

    cutPercentageFoodText_.setFont(font);
    cutPercentageFoodText_.setCharacterSize(24);
    cutPercentageFoodText_.setFillColor(sf::Color::Black);
    cutPercentageFoodText_.setPosition(window.getSize().x - 200, 100);

    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::Black);
    timeText.setPosition(window.getSize().x - 350, 10);


    bool foodhouseActivateMode = false;
    bool foodhouseSec = false;
    bool woodhouseActivateMode = false;
    bool woodhouseSec = false;
    bool stonehouseActivateMode = false;
    bool stonehouseSec = false;



    UiButton btn_save(sf::Vector2f( window.getSize().x - 100, 750), sf::Color::Yellow, "save");

    btn_save.callback_ = [&save, &map, &building_manager]() {
        save.SaveLevelToJson("map.json", map, building_manager);
        };

    UiButton btn_reset(sf::Vector2f(window.getSize().x - 100, 650), sf::Color::Yellow, "reset");

    btn_reset.callback_ = [&save, &map, &building_manager, &woodman_manager, &farmer_manager, &stone_manager]() {
        save.LoadLevelFromJson("mapsave.json", map, building_manager, woodman_manager, farmer_manager, stone_manager);
        save.SaveLevelToJson("map.json", map, building_manager);
        };

    UiButton btn_activate_foodhouse(sf::Vector2f(400, 750), sf::Color::White, "food");
    btn_activate_foodhouse.callback_ = [&building_manager, &window, &foodhouseActivateMode, &btn_activate_foodhouse,&map, &food_for_build]()
        {
            if (map.getFood() >= food_for_build)
            {
                btn_activate_foodhouse.settexture_green();
                if (foodhouseActivateMode)
                {
                    foodhouseActivateMode = false;
                    building_manager.SetActive(false);
                    ChangeCursor::BasicCursor(window);
                }
                else
                {
                    foodhouseActivateMode = true;
                    ChangeCursor::BuildingCursor(window);
                    building_manager.SetActive(true);
                }
            }
            else
            {
                btn_activate_foodhouse.settexture_red();
            }
        };

    UiButton btn_activate_woodhouse(sf::Vector2f(250, 750), sf::Color::White, "wood");
    btn_activate_woodhouse.callback_ = [&building_manager, &window, &woodhouseActivateMode,&map,&wood_for_build , &btn_activate_woodhouse]()
        {
            if (map.getWood() >= wood_for_build)
            {
                btn_activate_woodhouse.settexture_green();
                if (woodhouseActivateMode)
                {
                    woodhouseActivateMode = false;
                    building_manager.SetActive(false);
                    ChangeCursor::BasicCursor(window);
                }
                else
                {
                    woodhouseActivateMode = true;
                    ChangeCursor::BuildingCursor(window);
                    building_manager.SetActive(true);
                }
            }
            else
            {
                btn_activate_woodhouse.settexture_red();
            }
        };

    UiButton btn_activate_stonehouse(sf::Vector2f(100, 750), sf::Color::White, "stone");
    btn_activate_stonehouse.callback_ = [&building_manager, &window, &stonehouseActivateMode,&map, &stone_for_build, &btn_activate_stonehouse]()
        {
            if (map.getWood() >= stone_for_build)
            {
                btn_activate_stonehouse.settexture_green();
                if (stonehouseActivateMode)
                {
                    stonehouseActivateMode = false;
                    building_manager.SetActive(false);
                    ChangeCursor::BasicCursor(window);
                }
                else
                {
                    stonehouseActivateMode = true;
                    ChangeCursor::BuildingCursor(window);
                    building_manager.SetActive(true);
                }
            }
            else
            {
                btn_activate_stonehouse.settexture_red();
            }
        };

    map.ClickedTile = [&building_manager, &farmer_manager, &woodman_manager, &stone_manager, &hovered_tile_coord, &map, &foodhouseActivateMode, &foodhouseSec, &woodhouseActivateMode, &woodhouseSec, &stonehouseActivateMode, &stonehouseSec, &window, &food_for_build,&stone_for_build ,&wood_for_build](Tile& tile)
        {
            if (foodhouseActivateMode && foodhouseSec)
            {
                building_manager.Addfoodhouse(tile, hovered_tile_coord, map);
                farmer_manager.AddFarmer(tile, map);
                foodhouseActivateMode = false;
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
                foodhouseSec = false;
                map.setfood(food_for_build);
                food_for_build += food_for_build;
            }
            else if (woodhouseActivateMode && woodhouseSec)
            {
                building_manager.Addwoodhouse(tile, hovered_tile_coord, map);
                woodman_manager.Addwoodman(tile, map);
                woodhouseActivateMode = false;
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
                woodhouseSec = false;
                map.setWood(wood_for_build);
                wood_for_build += wood_for_build;
            }
            else if (stonehouseActivateMode && stonehouseSec)
            {
                building_manager.Addstonehouse(tile, hovered_tile_coord, map);
                stone_manager.Addstonebreaker(tile, map);
                stonehouseActivateMode = false;
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
                stonehouseSec = false;
                map.setstone(stone_for_build);
                stone_for_build = stone_for_build * 1.2;
            }
            if (foodhouseActivateMode) foodhouseSec = true;
            if (woodhouseActivateMode) woodhouseSec = true;
            if (stonehouseActivateMode) stonehouseSec = true;
        };

    sf::View view(sf::FloatRect(0, 0, VIEW_SIZE.x, VIEW_SIZE.y));
    sf::View view_Hud(sf::FloatRect(0, 0, VIEW_SIZE.x, VIEW_SIZE.y));
    view.setCenter(VIEW_SIZE.x / 2, VIEW_SIZE.y / 2);
    view_Hud.setCenter(VIEW_SIZE.x / 2, VIEW_SIZE.y / 2);

    sf::RectangleShape hovered_tile;
    hovered_tile.setSize(tile_size);
    hovered_tile.setFillColor(sf::Color(100, 100, 100, 180));
    hovered_tile.setOutlineColor(sf::Color::Green);
    hovered_tile.setOutlineThickness(-1);
    hovered_tile.setOrigin(0, 0);

    while (window.isOpen()) {


        if (map.getFood() >= food_for_build) 
        {
            btn_activate_foodhouse.settexture_green();
        }
        else
        {
            btn_activate_foodhouse.settexture_red();
        }

        if (map.getStone() >= stone_for_build)
        {
            btn_activate_stonehouse.settexture_green();
        }
        else
        {
            btn_activate_stonehouse.settexture_red();
        }

        if (map.getWood() >= wood_for_build)
        {
            btn_activate_woodhouse.settexture_green();
        }
        else
        {
            btn_activate_woodhouse.settexture_red();
        }


        std::ostringstream oss;
        for (auto& woodman : woodman_manager.woodmans_) woodman.Tick();
        for (auto& farmer : farmer_manager.farmers_) farmer.Tick();
        for (auto& stone : stone_manager.stonebreakers_) stone.Tick();
        map.Tick();
        if (map.getmonth() == 0 && map.getyear() == 0)
        {
            map.set_time();
        }


        woodText.setString("Wood: " + std::to_string(map.getWood()));
        foodText.setString("Food: " + std::to_string(map.getFood()));
        stoneText.setString("Stone: " + std::to_string(map.getStone()));
        timeText.setString("Day: " + std::to_string(map.getday()) + " Month: " + std::to_string(map.getmonth()) + " Year: " + std::to_string(map.getyear()));
       

       
        oss << std::fixed << std::setprecision(2) << map.getCutPercentageWood();
        if (map.getCutPercentageWood() >= 50.0)
        {
            cutPercentageWoodText_.setColor(sf::Color::Red);
        }
        else
        {
            cutPercentageWoodText_.setColor(sf::Color::Black);
        }
        cutPercentageWoodText_.setString("Wood Cut %: " + oss.str());
        oss.str(""); 

      
        oss << std::fixed << std::setprecision(2) << map.getCutPercentageStone();
        if (map.getCutPercentageStone() >= 50.0)
        {
            cutPercentageStoneText_.setColor(sf::Color::Red);
        }
        else
        {
            cutPercentageStoneText_.setColor(sf::Color::Black);
        }
        cutPercentageStoneText_.setString("Stone Cut %: " + oss.str());
        oss.str(""); 

     
        oss << std::fixed << std::setprecision(2) << map.getCutPercentageFood();
        if (map.getCutPercentageFood() >= 50.0)
        {
            cutPercentageFoodText_.setColor(sf::Color::Red);
        }
        else
        {
            cutPercentageFoodText_.setColor(sf::Color::Black);
        }
        cutPercentageFoodText_.setString(" Food Cut %: " + oss.str());
        oss.str(""); 

        mouse_pos = sf::Mouse::getPosition(window);
        mouse_world_pos = window.mapPixelToCoords(mouse_pos, view);
        mouse_tile_coord.x = static_cast<int>(std::floor(mouse_world_pos.x / tile_size.x));
        mouse_tile_coord.y = static_cast<int>(std::floor(mouse_world_pos.y / tile_size.y));
        hovered_tile_coord.x = static_cast<float>(mouse_tile_coord.x) * tile_size.x;
        hovered_tile_coord.y = static_cast<float>(mouse_tile_coord.y) * tile_size.y;
        hovered_tile.setPosition(hovered_tile_coord.x, hovered_tile_coord.y);

#ifdef TRACY_ENABLE
        ZoneScoped;
#endif

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.delta > 0) {
                    view.zoom(0.9f); // Zoom in
                }
                else if (event.mouseWheelScroll.delta < 0) {
                    view.zoom(1.1f); // Zoom out
                }
                // Limiter le zoom
                float currentZoom = view.getSize().x / VIEW_SIZE.x;
                if (currentZoom < MIN_ZOOM) {
                    view.setSize(VIEW_SIZE * MIN_ZOOM);
                }
                else if (currentZoom > MAX_ZOOM) {
                    view.setSize(VIEW_SIZE * MAX_ZOOM);
                }
                window.setView(view); // Update the window with the new view
                break;

            }
            
            btn_activate_woodhouse.HandleEvent(event);
            btn_activate_stonehouse.HandleEvent(event);
            btn_activate_foodhouse.HandleEvent(event);
            map.HandleEvent(event, window);
            btn_save.HandleEvent(event);
            btn_reset.HandleEvent(event);
        }

        // Move the view based on keyboard input and constrain the movement
        sf::Vector2f moveDelta;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            moveDelta.x = -100;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            moveDelta.x = 100;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            moveDelta.y = -100;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            moveDelta.y = 100;
        }
        view.move(moveDelta);

        // Limiter le déplacement
                // Limiter le déplacement
        sf::FloatRect viewBounds = view.getViewport();
        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f viewSize = view.getSize();

        sf::Vector2f mapBounds(120* tile_size.x, 120 * tile_size.y);

        if (viewCenter.x - viewSize.x / 2 < 0)
            view.setCenter(viewSize.x / 2, viewCenter.y);
        if (viewCenter.x + viewSize.x / 2 > mapBounds.x)
            view.setCenter(mapBounds.x - viewSize.x / 2, viewCenter.y);
        if (viewCenter.y - viewSize.y / 2 < 0)
            view.setCenter(viewCenter.x, viewSize.y / 2);
        if (viewCenter.y + viewSize.y / 2 > mapBounds.y)
            view.setCenter(viewCenter.x, mapBounds.y - viewSize.y / 2);

        window.setView(view);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            save.LoadLevelFromJson("map.json", map, building_manager, woodman_manager, farmer_manager, stone_manager);
            std::cout << "load map 1 \n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            save.SaveLevelToJson("map.json", map, building_manager);
            std::cout << "save map 1 \n";
        }

        // Gestion des clics pour les différentes actions
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            /*Tile* tile = map.GetTile(hovered_tile_coord);
            map.GetTile(hovered_tile_coord)->Set_Stone(TileType::kStone1);*/
        }

        window.clear();

        window.setView(view);
        window.draw(map);
        window.draw(building_manager);
        window.draw(woodman_manager);
        window.draw(farmer_manager);
        window.draw(stone_manager);
        window.draw(hovered_tile);


       


        window.setView(view_Hud);
        window.draw(woodText);
        window.draw(foodText);
        window.draw(stoneText);
        window.draw(timeText);
        window.draw(cutPercentageWoodText_);
        window.draw(cutPercentageStoneText_);
        window.draw(cutPercentageFoodText_);
        window.draw(btn_activate_foodhouse);
        window.draw(btn_activate_stonehouse);
        window.draw(btn_activate_woodhouse);
        window.draw(btn_save);
        window.draw(btn_reset);
        window.setView(view);

        window.display();
    }

#ifdef TRACY_ENABLE
    FrameMark;
#endif

    return 0;
}





