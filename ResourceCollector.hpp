#pragma once
#include "TwilightEngineCore/TwilightEngine.hpp"

enum class ResourceCollector
{
    BATTLE_BACKGROUND_A,
    BATTLE_UI_INFO_BOX,
    TEST_BUG_BACK_SPRITE
};

void collectResources(TwilightEngine* engine)
{
    engine->addTexture("battle_background_a.png", (int)ResourceCollector::BATTLE_BACKGROUND_A);
    engine->addTexture("battle_info_UI.png", (int)ResourceCollector::BATTLE_UI_INFO_BOX);
    engine->addTexture("big.png", (int)ResourceCollector::TEST_BUG_BACK_SPRITE);
}