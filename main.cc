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
#include "gameplay/Path.h"
#include "gameplay/woodman.h"
#include "gameplay/woodman_manager.h"


int main() {

    BuildingManager building_manager;
    woodmanManager woodman_manager;
    //astar atar_astar;

    

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Tilemap",sf::Style::None);
    window.setPosition(sf::Vector2i(0,0));

    ChangeCursor::BasicCursor(window);

    window.setFramerateLimit(60);
    
    Tilemap map;

    woodman jay(500, 500, 64);
    jay.set_destination(sf::Vector2f(0,0));
    
    map.Setup(sf::Vector2u(300, 300), sf::Vector2u(64, 64));

    map.LoadLevelFromJson("map.json");

    UiButton btn_generate(sf::Vector2f(50, 710), sf::Color::Yellow, "Generate");
    //btn_generate.setScale(0.5f, 0.5f);
   
    


   

    UiButton btn_activate_building(sf::Vector2f(200, 710), sf::Color::Yellow, "Build");
    //btn_activate_building.setScale(0.5f, 0.5f);
    btn_activate_building.callback_ = [&building_manager, &window, &map]()
        {
            if (building_manager.GetActive())
            {
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
            }
            else
            {
                building_manager.SetActive(true);
                map.ClickedTile = std::bind(&BuildingManager::AddBuilding, &building_manager, std::placeholders::_1);
                ChangeCursor::BuildingCursor(window);
            }
        };

    
    sf::View view(sf::FloatRect(0, 0, 1200, 800));
    view.zoom(2);
    sf::View view_Hud(sf::FloatRect(0, 0, 1200, 800));
    

    view.setCenter(300, 200); 
    view_Hud.setCenter(300, 200); 

     
    UiButton startButton(sf::Vector2f(400, 100), sf::Color::Yellow, "salut");
    startButton.setScale(0.75f, 0.75f);
    startButton.callback_ = [&map]() {
        map.Generate();
        };



    UiButton woodmanButton(sf::Vector2f(500, 100), sf::Color::Green, "woodman");
    woodmanButton.setScale(0.75f, 0.75f);
    woodmanButton.callback_ = [&woodman_manager, &window, &map]() {
        map.ClickedTile = std::bind(&woodmanManager::Addwoodman, &woodman_manager, std::placeholders::_1);
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

	    for (auto woodman : woodman_manager.woodmans_)
	    {
            woodman.Tick();
	    }


        // Calculate hovered tile position
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_world_pos = window.mapPixelToCoords(mouse_pos);
        sf::Vector2i mouse_tile_coord(static_cast<int>(std::floor(mouse_world_pos.x / tile_size.x)),
            static_cast<int>(std::floor(mouse_world_pos.y / tile_size.y)));

        hovered_tile.setPosition(static_cast<float>(mouse_tile_coord.x) * tile_size.x,
            static_cast<float>(mouse_tile_coord.y) * tile_size.y);

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
                break;
            default:
                break;
            }
            startButton.HandleEvent(event);
            woodmanButton.HandleEvent(event);
            btn_generate.HandleEvent(event);
            btn_activate_building.HandleEvent(event);
            map.HandleEvent(event);
        }
        sf::Vector2f postion;
        // Move the view based on keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            /*postion = sf::Vector2f(postion.x - 100000, postion.y);
            view.move(postion.x / 300, postion.y);
            window.setPosition(sf::Vector2i(window.getPosition().x + postion.x / 2560, window.getPosition().y));*/
            view.move(-100, 0);
            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            /*postion = sf::Vector2f(postion.x + 100000, postion.y);
            view.move(postion.x / 300, postion.y);
            window.setPosition(sf::Vector2i(window.getPosition().x + postion.x / 2560, window.getPosition().y));*/
            view.move(100, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            /*postion = sf::Vector2f(postion.x , postion.y - 100000);
            view.move(postion.x , postion.y / 200);
            window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y + postion.y / 1600));*/
            view.move(0, -100);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            /*postion = sf::Vector2f(postion.x, postion.y + 100000);
            view.move(postion.x, postion.y / 200);
            window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y + postion.y / 1600));*/
            view.move(0, 100);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            map.LoadLevelFromJson("map.json");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            map.SaveLevelToJson("map.json");
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
            sf::Vector2f destination(sf::Vector2f(mouse_world_pos.x, mouse_world_pos.y));
            Path p = astar::CalculatePath(map.GetWalkable(), jay.getPosition(), destination,64);
            jay.set_path(p);
            jay.set_destination(sf::Vector2f(0, 0));

        }

        window.clear();

        window.setView(view);
        window.draw(map);
       
        window.draw(building_manager);
        window.draw(woodman_manager);
       
        window.draw(hovered_tile);
        window.draw(jay);
        

        window.setView(view_Hud);
        window.draw(startButton);
        window.draw(woodmanButton);
        window.draw(btn_generate);
        window.draw(btn_activate_building);
        window.setView(view);
        

        window.display();
    }

#ifdef TRACY_ENABLE
    FrameMark;
#endif


    return 0;
}


