
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
		final_destination_ = steps[steps.size() - 1];
		step_ = std::queue<sf::Vector2f>();
		

		for (auto step : steps)
		{
			step_.push(step);
		}
		is_available = true;
	}
	else
	{
		is_available = false;
		//final_destination_ = sf::Vector2f(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
}


const std::queue<sf::Vector2f>& Path::GetSteps()
{
	return step_;
}