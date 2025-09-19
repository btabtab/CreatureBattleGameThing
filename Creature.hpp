#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "ResourceCollector.hpp"
#include "Stats.hpp"

class Creature
{
private:
	std::string name;
	int level;
	int experience_to_next_level;
	Stats stats;

    Sprite* front;
    Sprite* back;

public:
	Creature(std::string name):
	name(name)
	{
        level = 0;
        levelUp();
        front = new Sprite((int)ResourceCollector::TEST_BUG_BACK_SPRITE);
	}
    std::vector<Sprite*> getSprites()
    {
        return
        {
            front,
            back
        };
    }
    Stats getStats()
    {
        return stats;
    }
	std::string getName()
	{
		return name;
	}
	void giveExperience(int exp_to_give)
	{
		experience_to_next_level -= exp_to_give;
		if(experience_to_next_level < 0)
		{
			levelUp();
		}
	}
	void levelUp()
	{
		this->level++;
		experience_to_next_level = (level * 10) - abs(experience_to_next_level);
        std::cout << "[ Log ]::> \"experience_to_next_level\" \t" << experience_to_next_level << "\n";
        std::cout << "[ Log ]::> \"experience_to_next_level\" as % \t" << getEXPPercent() << "\n";
	}
    double getEXPPercent()
    {
        return ((double)experience_to_next_level) / ((double)level * 10.f); 
    }
    int getLevel()
    {
        return level;
    }
};