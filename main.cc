#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

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
#include "gameplay/stonebreaker.h"
#include "gameplay/stonebreaker_manager.h"
#include "gameplay/woodman.h"
#include "gameplay/woodman_manager.h"


int main() {

    BuildingManager building_manager;
    woodmanManager woodman_manager;
    stonebreakerManager stone_manager;
    Farmer_Manager farmer_manager;
    //astar atar_astar;

    

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Tilemap");
    

    ChangeCursor::BasicCursor(window);

    window.setFramerateLimit(60);
    
    Tilemap map;


    sf::Vector2i mouse_pos;
    sf::Vector2f mouse_world_pos;
    sf::Vector2i mouse_tile_coord;
    sf::Vector2f hovered_tile_coord;

  
    
    
    map.Setup(sf::Vector2u(120, 120), sf::Vector2u(64, 64));

    map.LoadLevelFromJson("map.json");

    UiButton btn_generate(sf::Vector2f(50, 710), sf::Color::Yellow, "Generate");
    //btn_generate.setScale(0.5f, 0.5f);
   
	//map.Generate();

    //map.FindStones();

    woodman jay(4500, 500, 64, map);

    sf::Vector2f pos = sf::Vector2f(0, 0);

    Farmer jay2(4500, 500, 64, map, pos);

    stonebreaker jay3(4500, 500, 64, map);


   

    UiButton btn_activate_woodhouse(sf::Vector2f(300, 710), sf::Color::Yellow, "wood");
    //btn_activate_building.setScale(0.5f, 0.5f);
    btn_activate_woodhouse.callback_ = [&building_manager, &window, &map, &hovered_tile_coord, &woodman_manager]()
        {
            if (building_manager.GetActive())
            {
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
            }
            else
            {
                building_manager.SetActive(true);

                // Créer des lambdas pour les deux fonctions
                auto addWoodhouse = [&building_manager, &hovered_tile_coord](Tile& tile) {
                    building_manager.Addwoodhouse(tile, hovered_tile_coord);
                    };
                auto addWoodman = [&woodman_manager, &map](Tile& tile) {
                    woodman_manager.Addwoodman(tile, map);
                    };

                // Créer une fonction lambda qui appelle les deux lambdas
                map.ClickedTile = [addWoodhouse, addWoodman](Tile& tile) {
                    addWoodhouse(tile);
                    addWoodman(tile);
                    };

                ChangeCursor::BuildingCursor(window);
            }
        };

    UiButton btn_activate_stonehouse(sf::Vector2f(200, 710), sf::Color::Yellow, "stone");
    //btn_activate_building.setScale(0.5f, 0.5f);
    btn_activate_stonehouse.callback_ = [&building_manager, &window, &map, &hovered_tile_coord ,&stone_manager]()
        {
            if (building_manager.GetActive())
            {
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
            }
            else
            {
                building_manager.SetActive(true);

                // Créer des lambdas pour Addstonehouse et Addstonebreaker
                auto addStonehouse = [&building_manager, &hovered_tile_coord](Tile& tile) {
                    building_manager.Addstonehouse(tile, hovered_tile_coord);
                    };
                auto addStonebreaker = [&stone_manager, &map](Tile& tile) {
                    stone_manager.Addstonebreaker(tile, map);
                    };

                // Assigner une lambda à map.ClickedTile qui appelle les deux lambdas
                map.ClickedTile = [addStonehouse, addStonebreaker](Tile& tile) {
                    addStonehouse(tile);
                    addStonebreaker(tile);
                    };

                ChangeCursor::BuildingCursor(window);
            }
        };
   
    UiButton btn_activate_foodhouse(sf::Vector2f(400, 710), sf::Color::Yellow, "food");
    //btn_activate_building.setScale(0.5f, 0.5f);
    btn_activate_foodhouse.callback_ = [&building_manager, &window, &map, &hovered_tile_coord, &farmer_manager]()
        {
            if (building_manager.GetActive())
            {
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
            }
            else
            {
                building_manager.SetActive(true);

                // Créer des lambdas pour Addfoodhouse et AddFarmer
                auto addFoodhouse = [&building_manager, &hovered_tile_coord](Tile& tile) {
                    building_manager.Addfoodhouse(tile, hovered_tile_coord);
                    };
                auto addFarmer = [&farmer_manager, &map](Tile& tile) {
                    farmer_manager.AddFarmer(tile, map);
                    };

                // Assigner une lambda à map.ClickedTile qui appelle les deux lambdas
                map.ClickedTile = [addFoodhouse, addFarmer](Tile& tile) {
                    addFoodhouse(tile);
                    addFarmer(tile);
                    };

                ChangeCursor::BuildingCursor(window);
            }
        };
    
    sf::View view(sf::FloatRect(0, 0, 1200, 800));
    sf::View view_Hud(sf::FloatRect(0, 0, 1200, 800));
    

    view.setCenter(600, 400); 
    view_Hud.setCenter(600, 400); 

     
    UiButton startButton(sf::Vector2f(400, 100), sf::Color::Yellow, "salut");
    startButton.setScale(0.75f, 0.75f);
    startButton.callback_ = [&map]() {
        map.Generate();
        };



    UiButton woodmanButton(sf::Vector2f(500, 100), sf::Color::Green, "woodman");
    woodmanButton.setScale(0.75f, 0.75f);
    woodmanButton.callback_ = [&woodman_manager, &window, &map]() {
        map.ClickedTile = std::bind(&woodmanManager::Addwoodman, &woodman_manager, std::placeholders::_1, std::ref(map));
        };


    sf::RectangleShape hovered_tile;
    sf::Vector2f tile_size(map.playground_tile_offset_u_.x, map.playground_tile_offset_u_.y);
    hovered_tile.setSize(tile_size);
    hovered_tile.setFillColor(sf::Color(100, 100, 100, 180));
    hovered_tile.setOutlineColor(sf::Color::Green);
    hovered_tile.setOutlineThickness(-1);
    hovered_tile.setOrigin(0, 0);

    while (window.isOpen()) {

        jay.Tick();

        jay2.Tick();

        jay3.Tick();

	    for (auto& woodman : woodman_manager.woodmans_)
	    {
            woodman.Tick();
	    }

        for (auto& farmer : farmer_manager.farmers_)
        {
            farmer.Tick();
        }

        for (auto& stone : stone_manager.stonebreakers_)
        {
            stone.Tick();
        }

        

        // Calculate hovered tile position
    	mouse_pos = sf::Mouse::getPosition(window);
        mouse_world_pos = window.mapPixelToCoords(mouse_pos, view);

        mouse_tile_coord.x = static_cast<int>(std::floor(mouse_world_pos.x / tile_size.x));
        mouse_tile_coord.y = static_cast<int>(std::floor(mouse_world_pos.y / tile_size.y));

        hovered_tile_coord.x = static_cast<float>(mouse_tile_coord.x) * tile_size.x;
        hovered_tile_coord.y = static_cast<float>(mouse_tile_coord.y) * tile_size.y;
       

        hovered_tile.setPosition(hovered_tile_coord.x, hovered_tile_coord.y);

        //std::cout << "pos :" << hovered_tile_coord.x << "  :  " << hovered_tile_coord.y << "\n";

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
                window.setView(view); // Update the window with the new view
                break;
            default:
                break;
            }
            startButton.HandleEvent(event);
            woodmanButton.HandleEvent(event);
            btn_generate.HandleEvent(event);
            btn_activate_woodhouse.HandleEvent(event);
            btn_activate_stonehouse.HandleEvent(event);
            btn_activate_foodhouse.HandleEvent(event);
            map.HandleEvent(event,window);
        }
        
        sf::Vector2f postion;
        // Move the view based on keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            /*postion = sf::Vector2f(postion.x - 100000, postion.y);
            view.move(postion.x / 300, postion.y);
            window.setPosition(sf::Vector2i(window.getPosition().x + postion.x / 2560, window.getPosition().y));*/
            view.move(-100, 0);
            //view_Hud.move(-100, 0);
            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            /*postion = sf::Vector2f(postion.x + 100000, postion.y);
            view.move(postion.x / 300, postion.y);
            window.setPosition(sf::Vector2i(window.getPosition().x + postion.x / 2560, window.getPosition().y));*/
            view.move(100, 0);
            //view_Hud.move(100, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            /*postion = sf::Vector2f(postion.x , postion.y - 100000);
            view.move(postion.x , postion.y / 200);
            window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y + postion.y / 1600));*/
            view.move(0, -100);
            //view_Hud.move(0, -100);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            /*postion = sf::Vector2f(postion.x, postion.y + 100000);
            view.move(postion.x, postion.y / 200);
            window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y + postion.y / 1600));*/
            view.move(0, 100);
            //view_Hud.move(0, 100);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            map.LoadLevelFromJson("map.json");
            std::cout << "load map 1 \n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            map.SaveLevelToJson("map.json");
            std::cout << "save map 1 \n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            map.LoadLevelFromJson("map_1.json");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            map.SaveLevelToJson("map_1.json");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            map.LoadLevelFromJson("map_2.json");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            map.SaveLevelToJson("map_2.json");
        }

        //todo ne pas oublei de cheker que la caasse seletion pour aller sur la case walkable 
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            Tile* tile = map.GetTile(hovered_tile_coord);

            //tile->Set_Stone_2(TileType::kStone1);

        }

        window.clear();

        window.setView(view);
        window.draw(map);
       
        window.draw(building_manager);
        window.draw(woodman_manager);
        window.draw(farmer_manager);
        window.draw(stone_manager);
       
        window.draw(hovered_tile);
        window.draw(jay);
        window.draw(jay2);
        window.draw(jay3);
        

        window.setView(view_Hud);
        window.draw(startButton);
        window.draw(woodmanButton);
        window.draw(btn_generate);
        window.draw(btn_activate_foodhouse);
        window.draw(btn_activate_stonehouse);
        window.draw(btn_activate_woodhouse);
        window.setView(view);
        

        window.display();
    }

#ifdef TRACY_ENABLE
    FrameMark;
#endif


    return 0;
}


