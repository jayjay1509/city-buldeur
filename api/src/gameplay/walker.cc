#include "gameplay/walker.h"


#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "gameplay/sfml_vec2f.h"


walker::walker(float x, float y, float linear_speed) : SpriteEntity(x,y)
{
    setPosition(x, y);
    linear_speed_ = linear_speed;
    last_time = std::chrono::steady_clock::now();
    destination_.x = x;
    destination_.y = y;
}

void walker::set_destination(sf::Vector2f destination)
{

    destination_.x = destination.x;
    destination_.y = destination.y;

}

void walker::set_linear_speed(float linear_speed)
{
    linear_speed_ = linear_speed;
}

void walker::set_path(const Path& path)
{

    path_ = path;
}


void walker::Tick()
{
    
    const auto end{ std::chrono::steady_clock::now() };
    const std::chrono::duration<float> elapsed_seconds{ end - last_time };
    last_time = std::chrono::steady_clock::now();
    auto delta_time = elapsed_seconds;

    //std::cout << elapsed_seconds << std::endl;
    const sf::Vector2f actual_position = getPosition();
    const sf::Vector2f direction = Normalized(destination_ - actual_position);
    sf::Vector2f new_pos = sf::Vector2f(0, 0);

    if (path_.IsAvailable())
    {
        if (Magnitude(destination_ - actual_position) < 60) {

            new_pos = destination_;
            destination_ = path_.getNextStep();
        }
        else
        {
        	new_pos = actual_position + sf::Vector2f(direction.x * linear_speed_ * elapsed_seconds.count(), direction.y * linear_speed_ * elapsed_seconds.count());
        }
        setPosition(new_pos);
        shape_.setPosition(getPosition());
        rect_.setPosition(getPosition());
    }


}

Path walker::GetPath() const
{
    return path_;
}

sf::Vector2f walker::last_destination() const
{
    return destination_;
}
