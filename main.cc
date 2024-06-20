#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#endif

#include <SFML/Graphics.hpp>
#include "ui/Ui_Button.h"
#include "tilemaps/Tilemap.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Tilemap");
    window.setFramerateLimit(60);

    // Setup the tilemap
    Tilemap map;
    map.Setup(sf::Vector2u(300, 300), sf::Vector2u(64, 64));

    // Load the map from JSON
   

    // Create a view
    sf::View view(sf::FloatRect(0, 0, 1200, 800)); // Size of the view
    view.setCenter(600, 400); // Center the view initially

    // Setup the start button
    UiButton startButton(sf::Vector2f(400, 100), sf::Color::Yellow);
    startButton.setScale(0.75f, 0.75f);
    startButton.callback_ = [&map]() {
        map.Generate();
        };

    while (window.isOpen()) {
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
        }

        // Move the view based on keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.move(-100, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(100, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.move(0, -100);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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


        window.clear();
        window.setView(view); // Set the view before drawing
        window.draw(map);
        window.draw(startButton);
        window.display();
    }

#ifdef TRACY_ENABLE
    FrameMark;
#endif


    return 0;
}
