#include <ui/Ui_Button.h>

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <Tracy/Tracy.hpp>

#include "tilemaps/RessourceManager.h"


UiButton::UiButton(sf::Vector2f position, sf::Color colorBase, std::string text)
{

	setPosition(position);

	// Declare and load a font
	font_.loadFromFile("../resources/fonts/arial.ttf");
	//texture_.loadFromFile("../resources/sprites/yellow_button00.png");


	// Create a text
	text_ = sf::Text(text, font_);
	text_.setCharacterSize(18);
	text_.setFillColor(sf::Color::Black);
	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	sprite_.setScale(2.0f, 1.0f);
	//sf::FloatRect texSize = sf::FloatRect(texture_.get);
	sprite_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::KButtongren));
	sprite_.setOrigin(sprite_.getTexture()->getSize().x / 2.0f, sprite_.getTexture()->getSize().y / 2.0f);
	sprite_.setColor(colorBase);

	//initialScale_ = sf::Vector2f(0.5f, 0.5f);

}

void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	states.transform *= getTransform();

	target.draw(sprite_, states);
	target.draw(text_, states);

}

bool UiButton::ContainsMouse(const sf::Event& event) const
{
	// Get the position of the mouse click
	float mouseX = static_cast<float>(event.mouseButton.x) - getPosition().x;
	float mouseY = static_cast<float>(event.mouseButton.y) - getPosition().y;

	// Check if the mouse click is inside the drawable shape
	if (sprite_.getGlobalBounds().contains(mouseX, mouseY)) {
		return true;
	}
	else
	{
		return false;
	}
}

void UiButton::settexture_red()
{
	sprite_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::KButtonred));
}

void UiButton::settexture_green()
{
	sprite_.setTexture(ResourceManager::Get().GetTexture(ResourceManager::Resource::KButtongren));
}

void UiButton::HandleEvent(const sf::Event& event)
{

	// Check for mouse button pressed event
	if (event.type == sf::Event::MouseButtonReleased) {

		if (ContainsMouse(event))
		{
			setScale(getScale().x / 0.9f, getScale().y / 0.9f);

			// Check if the left mouse button is pressed
			if (event.mouseButton.button == sf::Mouse::Left) {
				// Code à faire pour le bouton ---------------------------------------------------
				if (callback_) {
					callback_();
				}
				else
				{
					std::cout << "No callback defined...";
				}
			}
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (ContainsMouse(event))
		{
			setScale(0.9f * getScale().x, 0.9f * getScale().y);
		}
	}



}

//void UiButton::setScale(float factorX, float factorY)
//{
//	std::cout << "Overide scale" << std::endl;
//	initialScale_.x = factorX;
//	initialScale_.y = factorY;
//
//	sf::Transformable::setScale(factorX, factorY);
//
//}


