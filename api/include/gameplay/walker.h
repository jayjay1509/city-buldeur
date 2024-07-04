
#ifndef walker_
#define walker_
#include <chrono>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Path.h"
#include "sprite_entity.h"

class walker : public sf::Transformable , public SpriteEntity
{
	sf::Vector2f destination_ = {0,0};
	float linear_speed_;

	Path path_;
public:


	walker(float x, float y, float linear_speed);
	void set_destination(sf::Vector2f destination);
	void set_linear_speed(float linear_speed_);
	void set_path(const Path& path);
	void Tick();

	std::chrono::time_point<std::chrono::steady_clock> last_time ;
};


#endif
