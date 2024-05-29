#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <ui/UIButton.h>


UiButton::UiButton(sf::Vector2f pos, sf::Vector2f size, sf::Color color, sf::Vector2f pressed_size, 
                   sf::Color pressed_color, std::string text, int character_size, sf::Color _color_text, sf::Vector2f pressed_Character_size)
{
	background_ = std::make_unique<sf::RectangleShape>(size);
	InstanceShape(pos, color, pressed_size, pressed_color, text, character_size, _color_text, pressed_Character_size);
}

UiButton::UiButton(sf::Vector2f pos, float radius, sf::Color color, sf::Vector2f pressed_size, 
	sf::Color pressed_color, std::string text, int character_size, sf::Color _color_text, sf::Vector2f pressed_Character_size)
{
	background_ = std::make_unique<sf::CircleShape>(radius);
	InstanceShape(pos, color, pressed_size, pressed_color, text, character_size, _color_text, pressed_Character_size);
}

void UiButton::InstanceShape(sf::Vector2f pos, sf::Color color, sf::Vector2f pressed_size, sf::Color pressed_color, std::string text, int character_size, sf::Color color_text, sf::Vector2f pressed_Character_size)
{
	background_->setFillColor(color);
	background_->setPosition(pos);
	background_->setOrigin(background_->getGlobalBounds().width / 2.0f, background_->getGlobalBounds().height / 2.0f);

	if (!font_.loadFromFile("resources/font/light-arial.ttf")) {
		// Gérer l'erreur : impossible de charger la police
	}

	buttonText_.setFont(font_);
	buttonText_.setString(text);
	buttonText_.setCharacterSize(character_size);
	buttonText_.setFillColor(color_text);
	sf::FloatRect textRect = buttonText_.getLocalBounds();
	sf::FloatRect shapeRect = background_->getGlobalBounds();
	buttonText_.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	buttonText_.setPosition(shapeRect.left + shapeRect.width / 2.0f, shapeRect.top + shapeRect.height / 2.0f);
	buttonPressedColor_ = pressed_color;
	originalColor_ = background_->getFillColor();
	buttonPressedSize_ = pressed_size;
	originalSize_ = background_->getScale();
	buttonPressedSizeText_ = pressed_Character_size;
	originalSizeText_ = buttonText_.getScale();
}


void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(*background_, states);
	target.draw(buttonText_, states);

}

void const UiButton::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float mouseX = static_cast<float>(event.mouseButton.x);
			float mouseY = static_cast<float>(event.mouseButton.y);

			if (background_->getGlobalBounds().contains(mouseX, mouseY))
			{
				std::cout << "Start" << std::endl;
				background_->setFillColor(buttonPressedColor_);
				background_->setScale(buttonPressedSize_);
				buttonText_.setScale(buttonPressedSizeText_);
			}
		}
	}
	else
	{
		background_->setFillColor(originalColor_);
		background_->setScale(originalSize_);
		buttonText_.setScale(originalSizeText_);

	}
}

