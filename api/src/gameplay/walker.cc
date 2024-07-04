#include "gameplay/walker.h"


#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "gameplay/sfml_vec2f.h"


walker::walker(float x, float y, float linear_speed) : SpriteEntity(x,y)
{
    setPosition(x, y);
    linear_speed_ = linear_speed;
    last_time = std::chrono::steady_clock::now();
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

    if (path_.IsAvailable())
    {
        destination_ = path_.getNextStep();
    }
    else
    {
	    
    }
   

    //std::cout << elapsed_seconds << std::endl;
    const sf::Vector2f actual_position = getPosition();
    const sf::Vector2f direction = Normalized( destination_ - actual_position);



    if (Magnitude(destination_ - actual_position) < 10.0f) {
        
        setPosition(destination_);
        shape_.setPosition(getPosition());
        rect_.setPosition(getPosition());
        path_.is_available = true;
    }
    else
    {
        setPosition(actual_position + sf::Vector2f(direction.x * linear_speed_ * elapsed_seconds.count(), direction.y * linear_speed_ * elapsed_seconds.count()));

        shape_.setPosition(getPosition());
        rect_.setPosition(getPosition());
        path_.is_available = false;

    }

   

}
