
#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_

#include <functional>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>


class UiButton : public sf::Drawable, public sf::Transformable
{

private:
	sf::Font font_;
	sf::Texture texture_;
	sf::Sprite sprite_;
	
	
	sf::Text text_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool ContainsMouse(const sf::Event& event) const;

public:

	void settexture_red();
	void settexture_green();
	
	UiButton(sf::Vector2f position, sf::Color colorBase, std::string text);
	void HandleEvent(const sf::Event& event);

	//void setScale(float factorX, float factorY);
	std::function<void()> callback_;

};

#endif // API_UI_UIBUTTON_H_

