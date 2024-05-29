#include <SFML/Graphics.hpp>
#include <maths/vec2i.h>
#include <ui/UIButton.h>

int main()
{
	core::Vec2i v;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	UiButton startButton(sf::Vector2f(100, 50), sf::Vector2f(100, 50), sf::Color::Red, sf::Vector2f(0.8f, 0.8f), sf::Color::Yellow, "Test", 50, sf::Color::Blue, sf::Vector2f(0.8f, 0.8f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			startButton.handleEvent(event);
		}



		window.clear();
		window.draw(startButton);
		window.display();
	}

	return 0;
}