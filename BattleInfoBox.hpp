#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "TwilightEngineCore/Renderables/RenderObject.hpp"
#include "TwilightEngineCore/Renderables/Sprite.hpp"
#include "TwilightEngineCore/TwilightEngine.hpp"
#include "Team.hpp"

#include "ResourceCollector.hpp"

class BattleInfoBox : public RenderObject2D
{
	private:
	Creature* stats_to_draw;
	Point<int> position;
	
	public:
	BattleInfoBox(Creature* bug, Point<int> position):
	stats_to_draw(bug),
	position(position)
	{
	}
	void draw() override
	{
		int x = position.getX() + 20;
		int y = position.getY() + 20;
		DrawText(stats_to_draw->getName().c_str(), x, y, 20, BLACK);
		y += 20;
		int health_bar_width = 0xff * ((float)stats_to_draw->getStats().getCurrentHealth() / (float)stats_to_draw->getStats().getHealth());
		Color health_bar_colour = { 0 };
		health_bar_colour.a = 0xff;
		health_bar_colour.r = 0xff - (0xff * ((float)stats_to_draw->getStats().getCurrentHealth() / (float)stats_to_draw->getStats().getHealth()));
		health_bar_colour.g = 0xff * ((float)stats_to_draw->getStats().getCurrentHealth() / (float)stats_to_draw->getStats().getHealth());
		DrawRectangle(x, y + 5, 0xff, 25, BLACK);
		DrawRectangle(x, y + 5, health_bar_width, 25, health_bar_colour);
		y += 40;
		std::string health_text = std::to_string(stats_to_draw->getStats().getCurrentHealth()) + " / " + std::to_string(stats_to_draw->getStats().getHealth()) + " HP";
		DrawText(health_text.c_str(), x, y, 20, BLACK);
		y += 40;
		DrawText(("Level: " + std::to_string(stats_to_draw->getLevel())).c_str(), x, y, 20, BLACK);
		y += 10;
		DrawRectangle(x, y + 5, (float)0xff * stats_to_draw->getEXPPercent(), 20, BLUE);
		// std::cout << stats_to_draw->getEXPPercent() << "\n";
	}
	std::string getType() override
	{
		return "BattleInfoBox";
	}
	void update() override
	{
	}
};