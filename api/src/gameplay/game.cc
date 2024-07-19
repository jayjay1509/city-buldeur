#include "gameplay/game.h"
#include <iostream>
#include <iomanip>

const sf::Vector2f VIEW_SIZE(1200, 800);
const float MIN_ZOOM = 0.5f;
const float MAX_ZOOM = 5.0f;
const sf::Vector2f tile_size(64, 64);

Game::Game() :
    window(sf::VideoMode(1200, 800), "Tilemap"),
    btn_save(sf::Vector2f(window.getSize().x - 100, 750), sf::Color::Yellow, "save"),
    btn_reset(sf::Vector2f(window.getSize().x - 100, 650), sf::Color::Yellow, "reset"),
    btn_activate_foodhouse(sf::Vector2f(400, 750), sf::Color::White, "food"),
    btn_activate_woodhouse(sf::Vector2f(250, 750), sf::Color::White, "wood"),
    btn_activate_stonehouse(sf::Vector2f(100, 750), sf::Color::White, "stone"),
    foodhouseActivateMode(false),
    woodhouseActivateMode(false),
    stonehouseActivateMode(false)
{

    ChangeCursor::BasicCursor(window);
    window.setFramerateLimit(60);


  
    font.loadFromFile("../resources/fonts/arial.ttf");

    sf::Text loadingText;
    loadingText.setFont(font);
    loadingText.setString("Chargement...");
    loadingText.setCharacterSize(50);
    loadingText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = loadingText.getLocalBounds();
    loadingText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    loadingText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


    window.clear(sf::Color::White); 
    window.draw(loadingText);
    window.display();

    map.Setup(sf::Vector2u(120, 120), sf::Vector2u(64, 64));
    save.LoadLevelFromJson("map.json", map, building_manager, woodman_manager, farmer_manager, stone_manager);

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

    hovered_tile.setSize(tile_size);
    hovered_tile.setFillColor(sf::Color(100, 100, 100, 180));
    hovered_tile.setOutlineColor(sf::Color::Green);
    hovered_tile.setOutlineThickness(-1);
    hovered_tile.setOrigin(0, 0);


  
    btn_save.callback_ = [&]() {
        //std::cout << "btn_save callback invoked" << std::endl;
        save.SaveLevelToJson("map.json", map, building_manager);
        };

    btn_reset.callback_ = [&]() {
        ResetGame();
        };

    btn_activate_foodhouse.callback_ = [&]() {
        if (map.getFood() >= food_for_build) {
            btn_activate_foodhouse.settexture_green();
            foodhouseActivateMode = !foodhouseActivateMode;
            ChangeCursor::SetCursorMode(window, foodhouseActivateMode);
            building_manager.SetActive(foodhouseActivateMode);
            food_for_build = food_for_build * 1.2;
        }
        else {
            btn_activate_foodhouse.settexture_red();
        }
        };

    btn_activate_woodhouse.callback_ = [&]() {
        if (map.getWood() >= wood_for_build) {
            btn_activate_woodhouse.settexture_green();
            woodhouseActivateMode = !woodhouseActivateMode;
            ChangeCursor::SetCursorMode(window, woodhouseActivateMode);
            building_manager.SetActive(woodhouseActivateMode);
            wood_for_build = wood_for_build * 1.2;
        }
        else {
            btn_activate_woodhouse.settexture_red();
        }
        };

    btn_activate_stonehouse.callback_ = [&]() {
        if (map.getStone() >= stone_for_build) {
            btn_activate_stonehouse.settexture_green();
            stonehouseActivateMode = !stonehouseActivateMode;
            ChangeCursor::SetCursorMode(window, stonehouseActivateMode);
            building_manager.SetActive(stonehouseActivateMode);
            stone_for_build = stone_for_build * 1.2;
        }
        else {
            btn_activate_stonehouse.settexture_red();
        }
        };
        map.ClickedTile = [this](Tile& tile) {
            if (foodhouseActivateMode && foodhouseSec) {
                building_manager.Addfoodhouse(tile, hovered_tile_coord, map);
                farmer_manager.AddFarmer(tile, map);

                foodhouseActivateMode = false;
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
                foodhouseSec = false;
            }
            else if (woodhouseActivateMode && woodhouseSec) {
                building_manager.Addwoodhouse(tile, hovered_tile_coord, map);
                woodman_manager.Addwoodman(tile, map);

                woodhouseActivateMode = false;
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
                woodhouseSec = false;
            }
            else if (stonehouseActivateMode && stonehouseSec) {
                building_manager.Addstonehouse(tile, hovered_tile_coord, map);
                stone_manager.Addstonebreaker(tile, map);

                stonehouseActivateMode = false;
                building_manager.SetActive(false);
                ChangeCursor::BasicCursor(window);
                stonehouseSec = false;
            }

            if (foodhouseActivateMode) foodhouseSec = true;
            if (woodhouseActivateMode) woodhouseSec = true;
            if (stonehouseActivateMode) stonehouseSec = true;
            };
        
    view.setSize(VIEW_SIZE);
    view.setCenter(VIEW_SIZE.x / 2, VIEW_SIZE.y / 2);
    view_Hud.setSize(VIEW_SIZE);
    view_Hud.setCenter(VIEW_SIZE.x / 2, VIEW_SIZE.y / 2);
}

void Game::Run() {
    while (window.isOpen()) {
        HandleEvents();
        Update();
        Draw();
    }
}

void Game::HandleEvents() {
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
         
            break;
        }
        window.setView(view);
        btn_activate_woodhouse.HandleEvent(event);
        btn_activate_stonehouse.HandleEvent(event);
        btn_activate_foodhouse.HandleEvent(event);
        map.HandleEvent(event, window);
        btn_save.HandleEvent(event);
        btn_reset.HandleEvent(event);
    }
}

void Game::Update() {
    if (map.getFood() >= food_for_build) {
        btn_activate_foodhouse.settexture_green();
    }
    else {
        btn_activate_foodhouse.settexture_red();
    }

    if (map.getStone() >= stone_for_build) {
        btn_activate_stonehouse.settexture_green();
    }
    else {
        btn_activate_stonehouse.settexture_red();
    }

    if (map.getWood() >= wood_for_build) {
        btn_activate_woodhouse.settexture_green();
    }
    else {
        btn_activate_woodhouse.settexture_red();
    }

    std::ostringstream oss;
    for (auto& woodman : woodman_manager.woodmans_) woodman.Tick();
    for (auto& farmer : farmer_manager.farmers_) farmer.Tick();
    for (auto& stone : stone_manager.stonebreakers_) stone.Tick();
    map.Tick();

    if (map.getmonth() == 0 && map.getyear() == 0) {
        map.set_time();
    }

    woodText.setString("Wood: " + std::to_string(map.getWood()));
    foodText.setString("Food: " + std::to_string(map.getFood()));
    stoneText.setString("Stone: " + std::to_string(map.getStone()));
    timeText.setString("Day: " + std::to_string(map.getday()) + " Month: " + std::to_string(map.getmonth()) + " Year: " + std::to_string(map.getyear()));

    UpdateCutPercentageText(oss);

    mouse_pos = sf::Mouse::getPosition(window);
    mouse_world_pos = window.mapPixelToCoords(mouse_pos, view);
    mouse_tile_coord.x = static_cast<int>(std::floor(mouse_world_pos.x / tile_size.x));
    mouse_tile_coord.y = static_cast<int>(std::floor(mouse_world_pos.y / tile_size.y));
    hovered_tile_coord.x = static_cast<float>(mouse_tile_coord.x) * tile_size.x;
    hovered_tile_coord.y = static_cast<float>(mouse_tile_coord.y) * tile_size.y;
    hovered_tile.setPosition(hovered_tile_coord.x, hovered_tile_coord.y);

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

    ConstrainView();

    window.setView(view);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
        save.LoadLevelFromJson("map.json", map, building_manager, woodman_manager, farmer_manager, stone_manager);
        //std::cout << "load map 1 \n";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
        save.SaveLevelToJson("map.json", map, building_manager);
        //std::cout << "save map 1 \n";
    }
}

void Game::UpdateCutPercentageText(std::ostringstream& oss) {
    oss << std::fixed << std::setprecision(2) << map.getCutPercentageWood();
    cutPercentageWoodText_.setFillColor(map.getCutPercentageWood() >= 50.0 ? sf::Color::Red : sf::Color::Black);
    cutPercentageWoodText_.setString("Wood Cut %: " + oss.str());
    oss.str("");

    oss << std::fixed << std::setprecision(2) << map.getCutPercentageStone();
    cutPercentageStoneText_.setFillColor(map.getCutPercentageStone() >= 50.0 ? sf::Color::Red : sf::Color::Black);
    cutPercentageStoneText_.setString("Stone Cut %: " + oss.str());
    oss.str("");

    oss << std::fixed << std::setprecision(2) << map.getCutPercentageFood();
    cutPercentageFoodText_.setFillColor(map.getCutPercentageFood() >= 50.0 ? sf::Color::Red : sf::Color::Black);
    cutPercentageFoodText_.setString("Food Cut %: " + oss.str());
    oss.str("");
}

void Game::ConstrainView() {
    sf::FloatRect viewBounds = view.getViewport();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    sf::Vector2f mapBounds(120 * tile_size.x, 120 * tile_size.y);

    if (viewCenter.x - viewSize.x / 2 < 0)
        view.setCenter(viewSize.x / 2, viewCenter.y);
    if (viewCenter.x + viewSize.x / 2 > mapBounds.x)
        view.setCenter(mapBounds.x - viewSize.x / 2, viewCenter.y);
    if (viewCenter.y - viewSize.y / 2 < 0)
        view.setCenter(viewCenter.x, viewSize.y / 2);
    if (viewCenter.y + viewSize.y / 2 > mapBounds.y)
        view.setCenter(viewCenter.x, mapBounds.y - viewSize.y / 2);
}

void Game::Draw() {
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
    window.display();
}

void Game::ResetGame()
{
    save.LoadLevelFromJson("mapsave2.json", map, building_manager, woodman_manager, farmer_manager, stone_manager);
    map.setfood(20);
    map.setWood(20);
    map.setstone(20);
    map.setPercentage_wood(0);
    map.setPercentage_stone(0);
    map.setPercentage_food(0);
    map.set_time();
    save.SaveLevelToJson("map.json", map, building_manager);
}
