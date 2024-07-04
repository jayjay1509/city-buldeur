
#include "gameplay/Path.h"

bool Path::IsEnden()
{
	return step_.empty();
}

bool Path::IsAvailable()
{
	return is_available;
}

bool Path::IsReady()
{
	return is_ready;
}

sf::Vector2f Path::getNextStep()
{

	if (!step_.empty())
	{
		nextstep_ = step_.front();
		step_.pop();
	}

	return nextstep_;
}

void Path::setsteps(std::vector<sf::Vector2f> steps)
{
	if (!steps.empty())
	{
		step_ = std::queue<sf::Vector2f>();
		for (auto step : steps)
		{
			step_.push(step);
		}
		
	}
	else
	{
		is_available = false;
	}
}


const std::queue<sf::Vector2f>& Path::GetSteps()
{
	return step_;
}