#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

class UiButton : public sf::Drawable, sf::Transformable
{
	sf::Color buttonPressedColor_;
	sf::Vector2f buttonPressedSize_;
	sf::Vector2f buttonPressedSizeText_;

	sf::Font font_;
	sf::Text buttonText_;
	sf::Color colorButton_;
	sf::Color originalColor_;
	sf::Vector2f originalSize_;
	sf::Vector2f originalSizeText_;
	std::unique_ptr<sf::Shape> background_;

public:
	void InstanceShape(sf::Vector2f pos, sf::Color color, sf::Vector2f pressed_size, sf::Color pressed_color,
	                   std::string text, int character_size, sf::Color color_text,
	                   sf::Vector2f pressed_Character_size);
	UiButton(sf::Vector2f pos, sf::Vector2f size, sf::Color color, sf::Vector2f pressed_size, sf::Color pressed_color, std::string text, int character_size, sf::Color _color_text, sf::Vector2f pressed_Character_size);
	UiButton(sf::Vector2f pos, float radius, sf::Color color, sf::Vector2f pressed_size,sf::Color pressed_color, std::string text, int character_size, sf::Color _color_text, sf::Vector2f pressed_Character_size);


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void const handleEvent(const sf::Event& event);

};

#endif // API_UI_UIBUTTON_H_

