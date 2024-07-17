#ifndef path_H_
#define path_H_
#include <SFML/System/Vector2.hpp>
#include <queue>

class Path
{
public:
	bool IsEnden();
	bool IsAvailable();
	bool IsReady();

	sf::Vector2f getNextStep();
	void setsteps(std::vector<sf::Vector2f> steps);
	const std::queue<sf::Vector2f>& GetSteps();
	sf::Vector2f final_destination_;
	
private:
	bool is_available = false;
	sf::Vector2f nextstep_;

	std::queue<sf::Vector2f> step_;
	
	bool is_ready = true;
};
#endif
