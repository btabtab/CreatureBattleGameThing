#pragma once

#include "TwilightEngineCore/TwilightEngine.hpp"
#include "TwilightEngineCore/Point.hpp"

class GameCursor : public RenderObject2D
{
private:

public:
	GameCursor()
	{
	}

	void draw() override
	{
		DrawCircleLines(GetMouseX(), GetMouseY(), 6.f, WHITE);
	}

	void handleInputs() override
	{
	}

	void update() override
	{
	}

	std::string getType() override
	{
		return "GameCursor";
	}
};