#include "gameplay/astar.h"
#include <unordered_set>

#include "gameplay/sfml_vec2f.h"




static  std::vector<sf::Vector2f> ConstructPath(const PathPoint& exitpoint,const PathPoint* vistided_points)
{
    std::vector<sf::Vector2f> path;
    PathPoint point = exitpoint;

    path.emplace_back(point.position());

    while (point.parent_index() != -1)
    {
        point = vistided_points[point.parent_index()];
        path.push_back(point.position());

    }
    std::reverse(path.begin(), path.end());
    return path;
}

template<>
struct std::hash<sf::Vector2f>
{
    std::size_t operator()(const sf::Vector2f& v) const noexcept
    {
        std::size_t h1 = std::hash<float>{}(v.x);
        std::size_t h2 = std::hash<float>{}(v.y);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

Path astar::CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_map_offset)
{

    Path path;
    sf::Vector2f rounded_end;
    rounded_end.x = end.x - std::fmod(end.x, static_cast<float>(tile_map_offset));
    rounded_end.y = end.y - std::fmod(end.y, static_cast<float>(tile_map_offset));

    sf::Vector2f rounded_start;
    rounded_start.x = start.x - std::fmod(start.x, static_cast<float>(tile_map_offset));
    rounded_start.y = start.y - std::fmod(start.y, static_cast<float>(tile_map_offset));

    positions.emplace_back(rounded_start);
    positions.emplace_back(rounded_end);

    std::priority_queue<PathPoint, std::vector<PathPoint>, std::greater<PathPoint>> opens;
    std::unordered_set<sf::Vector2f> open_list;
    std::unordered_set<sf::Vector2f> closed_list;
    std::vector<PathPoint> visited_points;

    opens.emplace(PathPoint{ 0, Magnitude(rounded_end - rounded_start), rounded_start, -1 });
    open_list.emplace(rounded_start);

    while (!opens.empty())
    {
        PathPoint current = opens.top();
        opens.pop();
        closed_list.emplace(current.position());

        open_list.erase(current.position());

        if (Magnitude(rounded_end - current.position()) <= std::numeric_limits<float>::epsilon())
        {
            path.setsteps(ConstructPath(current,visited_points.data()));
            //std::cout << "Found the path : nb steps = " << path.GetSteps().size() << std::endl;
            return path;
        }

        for (sf::Vector2f Neighbours : KNeighbours)
        {
            sf::Vector2f neighbourspos = current.position() + sf::Vector2f(Neighbours.x * tile_map_offset, Neighbours.y * tile_map_offset);

            auto found = std::find_if(positions.begin(), positions.end(), [&neighbourspos](sf::Vector2f& pos)
                {
                    return pos == neighbourspos;
                });

            if (found != positions.end())
            {
	            if (*found == current.position())
	            {
                    std::cerr << "pas ouf \n";
	            }
                bool is_in_closed = closed_list.contains(*found);
                bool is_in_open = open_list.contains(*found);
            

                if (!is_in_closed && !is_in_open)
                {
                    auto index = visited_points.size();
                    visited_points.push_back(current);

                    opens.emplace(current.g() + tile_map_offset, Magnitude(rounded_end - current.position()), *found, static_cast<int>(index));
                    open_list.emplace(*found);
                }
            }
        }

        if (open_list.empty() && !opens.empty())
        {
            std::cout << "Open list is empty, but opens is not. Ending the search to avoid infinite loop." << std::endl;
            break;
        }
    }

    std::cout << "Didn't find the path" << std::endl;
    std::cout << "Start : " << rounded_start.x << " " << rounded_start.y << std::endl;
    std::cout << "End : " << end.x << " " << end.y << std::endl;
    std::cout << "Rounded end : " << rounded_end.x << " " << rounded_end.y << std::endl;

    return path;
}