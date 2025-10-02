#include <string>
#include <vector>
#include "TwilightEngineCore/TwilightEngine.hpp"

#include "Stats.hpp"
#include "Creature.hpp"
#include "Team.hpp"
#include "BattleScreen.hpp"

#include "FancyButton.hpp"
#include "MouseCursor.hpp"
#include "CaptureStyler.hpp"
void TwilightEngine::userSetup()
{
	collectResources(this);
	// Team player;
	// Team enemy;
	// addRenderObject(new BattleScreen(&player, &enemy, this));

	HideCursor();
	addRenderObject(new GameCursor());
	addRenderObject(new CaptureStyler());
}

PuzzleButtonScoreTracker tracker;

void TwilightEngine::userLoop()
{
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
