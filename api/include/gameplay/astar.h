#ifndef ASTAR_H_
#define ASTAR_H_

#include "Path.h"
#include "tilemaps/tilemap.h"
#include "sfml_vec2f.h"
#include <vector>
#include <array>


class PathPoint
{
private:  
    // g is distanc from start to pathpoint.
    float g_;
    //h = h is  estimated cost to goal heuristic function (distance to but).
    float h_;
    sf::Vector2f position_;
    int parent_ = -1;

    float f() const { return g_ + h_; }

   
public:


	float g() const
    {
        return g_;
    }

    const sf::Vector2f& position() const
    {
        return position_;
    }

    int  parent_index() const
    {
        return parent_;
    }


    PathPoint(float g, float h, sf::Vector2f position, int parent)
        : g_(g), h_(h), position_(position), parent_(parent) {}

    bool operator>(const PathPoint& other) const
    {
        return f() > other.f();
    }
};

const std::array<sf::Vector2f, 4> KNeighbours = {
    sf::Vector2f(0, 1),
    sf::Vector2f(1, 0),
    sf::Vector2f(0, -1),
    sf::Vector2f(-1, 0)
};

namespace astar //todo a retier 
{


    Path CalculatePath(std::vector<sf::Vector2f> position, sf::Vector2f start, sf::Vector2f end, int tile_map_offset);


};

#endif // ASTAR_H_

