#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "TwilightEngineCore/Renderables/RenderObject.hpp"
#include "TwilightEngineCore/Renderables/Sprite.hpp"
#include "TwilightEngineCore/TwilightEngine.hpp"
#include "Team.hpp"
#include "BattleInfoBox.hpp"

#include "ResourceCollector.hpp"

class BattleScreen : public RenderObject2D
{
private:
	Team* player;
	Team* enemy;

	Sprite* background;
	Sprite* info_boxes[2];

	BattleInfoBox* player_info;
	BattleInfoBox* enemy_info;
public:
	BattleScreen(
					Team* player,
					Team* enemy,
					TwilightEngine* engine,
					ResourceCollector texture_id = ResourceCollector::BATTLE_BACKGROUND_A
				):
	player(player),
	enemy(enemy),
	player_info(new BattleInfoBox(player->getCreature(0), Point<int>(GetScreenWidth() - 350, GetScreenHeight() - 300))),
	enemy_info(new BattleInfoBox(enemy->getCreature(0), Point<int>(0, 0)))
	{
		background = new Sprite((int)texture_id);
		info_boxes[0] = new Sprite(
								(int)ResourceCollector::BATTLE_UI_INFO_BOX,
								Point<int>(GetScreenWidth() - 350, GetScreenHeight() - 300)
							);
		info_boxes[1] = new Sprite(
								(int)ResourceCollector::BATTLE_UI_INFO_BOX,
								Point<int>(0, 0)
							);
		info_boxes[0]->setLayer(DrawLayer::FRONT);
		info_boxes[1]->setLayer(DrawLayer::FRONT);
		background->setLayer(DrawLayer::BACK);
		player_info->setLayer(DrawLayer::UI);
		engine->addRenderObject(player_info);
		enemy_info->setLayer(DrawLayer::UI);
		engine->addRenderObject(enemy_info);

		engine->addRenderObject(background);
		engine->addRenderObject(info_boxes[0]);
		engine->addRenderObject(info_boxes[1]);

		if(player == nullptr || enemy == nullptr)
		{
			std::cout << "[ Error ]\t::>>\t player[ " << player << " ] or enemy [ " << enemy << " ]== nullptr";
			exit(0);
		}

		if(player->getCreature(0) != nullptr)
		{
			engine->addRenderObject(player->getCreature(0)->getSprites().front());
		}
	}
	~BattleScreen()
	{
		background->deleteMe();
		info_boxes[0]->deleteMe();
		info_boxes[1]->deleteMe();
		player_info->deleteMe();
		enemy_info->deleteMe();
	}
	void draw() override
	{
		DrawText("Battle Screen", 10, 10, 10, BLACK);
	}
	void update() override
	{
	}
	void handleInputs() override
	{
		if(IsKeyDown(KEY_LEFT_ALT))
		{
			return;
		}
		if(IsKeyPressed(KEY_B))
		{
			deleteMe();
		}
		if(IsKeyPressed(KEY_U))
		{
			player->getCreature(0)->levelUp();
		}
	}
	std::string getType() override
	{
		return "BattleScreen";
	}
};