#ifndef vec2f_
#define vec2f_

#include <SFML/System/Vector2.hpp>

#include "cmath"

[[nodiscard]] inline float squaredMagnitude(sf::Vector2f v) 
{
    return  (v.x * v.x + v.y * v.y);
}


[[nodiscard]] inline  float Magnitude(sf::Vector2f v) 
{
    return  std::sqrt(squaredMagnitude(v));
}



[[nodiscard]] inline sf::Vector2f  Normalized(sf::Vector2f v)
{

    float norm_x_ = v.x == 0 ? 0 : v.x / Magnitude(v);
    float norm_y_ = v.y == 0 ? 0 : v.y / Magnitude(v);

    return { norm_x_,norm_y_ };
}



#endif
