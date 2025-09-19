#include <string>
#include <vector>
#include "TwilightEngineCore/TwilightEngine.hpp"

#include "Stats.hpp"
#include "Creature.hpp"
#include "Team.hpp"
#include "BattleScreen.hpp"

#include "FancyButton.hpp"

void TwilightEngine::userSetup()
{
	// collectResources(this);
	// Team player;
	// Team enemy;
	// addRenderObject(new BattleScreen(&player, &enemy, this));
}

void TwilightEngine::userLoop()
{
	if(IsKeyPressed(KEY_A))
	{
		Point<float> randomised_position(
										(GetScreenWidth() / 2) + GetRandomValue(-100, 100),
										(GetScreenHeight() / 2) + GetRandomValue(-100, 100)
									);
		addRenderObject(new TimedButton(30 * 3, 30, randomised_position));
	}
	if(IsKeyPressed(KEY_S))
	{
		Point<float> randomised_a(
								(GetScreenWidth() / 2) + GetRandomValue(-100, 100),
								(GetScreenHeight() / 2) + GetRandomValue(-100, 100)
								);
		Point<float> randomised_b(
								(GetScreenWidth() / 2) + (GetRandomValue(-100, 100)),
								(GetScreenHeight() / 2) + (GetRandomValue(-100, 100))
								);
		addRenderObject(new PathwayButton(randomised_a, randomised_b, GetRandomValue(60, 120)));
	}
}

int main(int argc, char* argv[])
{
	TwilightEngine(
					argc,
					argv,
					Point<float>(800, 800),
					std::string("Goblins of RAM pre-alpha")
					).enter();
	return 0;
}
