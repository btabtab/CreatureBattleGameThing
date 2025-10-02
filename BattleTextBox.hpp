#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "TwilightEngineCore/Renderables/RenderObject.hpp"
#include "TwilightEngineCore/Renderables/Sprite.hpp"
#include "TwilightEngineCore/TwilightEngine.hpp"
#include "Team.hpp"

#include "ResourceCollector.hpp"

class BattleTextBox : public RenderObject2D
{
private:

	Point<int> where;

	bool is_in_talk_mode;
	std::string current_text;
	std::string next_text;

	bool is_in_option_mode;
	std::string options[4];
	int highlighted_option;

	bool was_next_pressed;

	void handleOptionMode()
	{
		if(!is_in_option_mode || was_next_pressed)
		{
			return;
		}
		if(IsKeyPressed(KEY_DOWN))
		{
			highlighted_option++;
		}
		if(IsKeyPressed(KEY_UP))
		{
			highlighted_option--;
		}
		was_next_pressed = IsKeyPressed(KEY_ENTER);
	}
	void handleTalkMode()
	{
		if(!is_in_talk_mode || was_next_pressed)
		{
			return;
		}
		was_next_pressed = IsKeyPressed(KEY_ENTER);
	}

	void drawOptionMode()
	{
		if(!is_in_option_mode)
		{
			return;
		}
		for(int i = 0; i != 4; i++)
		{
			Color colour_to_draw_with = GRAY;
			if(i == highlighted_option)
			{
				colour_to_draw_with = BLACK;
			}
			DrawText(
					current_text.c_str(),
					where.getX() + 30,
					where.getY() + 30 + (30 * i),
					20,
					colour_to_draw_with);
		}
	}
	void drawTalkMode()
	{
		if(!is_in_talk_mode)
		{
			return;
		}
		DrawText(current_text.c_str(), where.getX() + 30, where.getY() + 30, 20, BLACK);
	}
public:
	BattleTextBox(Point<int> where_to_start = Point<int>(0, 0), std::string start_text = "none"):
	current_text(start_text),
	options(),
	where(where_to_start)
	{
		highlighted_option = 0;
		startTalking();

		options[0] = "ATTACK";
		options[1] = "ITEM";
		options[2] = "BUGS";
		options[3] = "RETREAT";
	}

	void startTalking()
	{
		is_in_talk_mode = true;
		is_in_option_mode = false;
	}

	void startChoosing()
	{
		is_in_option_mode = true;
		is_in_talk_mode = false;
	}
	bool getIfTextIsDone()
	{
		return was_next_pressed;
	}
	int getChosenOption()
	{
		return highlighted_option;
	}
	void draw() override
	{
		DrawRectangle(where.getX(), where.getY(), GetScreenWidth(), GetScreenHeight(), BLACK);
		DrawRectangle(where.getX() + 25, where.getY() + 25, GetScreenWidth() - 25, GetScreenHeight() - 25, WHITE);
		drawOptionMode();
		drawTalkMode();
	}
	void update() override
	{
		if(highlighted_option < 0)
		{
			highlighted_option = 3;
		}
		if(3 < highlighted_option)
		{
			highlighted_option = 0;
		}
	}
	void handleInputs() override
	{
		handleOptionMode();
		handleTalkMode();
	}
	std::string getType() override
	{
		return "BattleTextBox";
	}
};