#pragma once

#include <string>
#include "SFML/Graphics.hpp"

namespace Constants::SCREEN {
	constexpr unsigned int height = 1000;
	constexpr unsigned int width = 1000;

	const sf::VideoMode videoMode({ height, width });

	const std::string title = "OSU";

	constexpr float centerDivider = 2.f;
}

namespace Constants::TIMER {
	const sf::String timerText = "Time: ";

	constexpr sf::Time seconds = sf::seconds(30.f);	
	constexpr int intPrecision = 1000;
	constexpr int floatPrecision = 1000;
	
	constexpr sf::Vector2f pos(10.f, 10.f);

	constexpr sf::Time penalty = sf::seconds(1.f);
}

namespace Constants::TEXT {
	const sf::Font font = sf::Font("arial.ttf");

	const sf::String scoreWith0 = "Score: 0";
	const sf::String score = "Score: ";

	const sf::String yourTime = "Your time: ";

	const sf::String playAgain = "Click to play again!";

	//
	namespace POSITIONS {
		constexpr sf::Vector2u scoreTopRight = sf::Vector2u(120, 10); // actually -120 but it's U-vector 
		constexpr sf::Vector2f scoreCenter = sf::Vector2f(0.f, -30.f);

		constexpr sf::Vector2f playAgainCenter = sf::Vector2f(scoreCenter.x * 2.5, scoreCenter.y * 2.5);
	}
	//
}

namespace Constants::NUMS {
	constexpr float speedIncreaser = 0.2f;
	constexpr int shapesCnt = 10;

	// Circle shapes
	constexpr float minR = 50.f;
	constexpr int modR = 50;
	constexpr size_t points = 30Ui64; // for cirlce creation

	constexpr float minSpeedX = 0.5f;
	constexpr int modX = 2;

	constexpr float minSpeedY = 0.5f;
	constexpr int modY = 2;
	//
}