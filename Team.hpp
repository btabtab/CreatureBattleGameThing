#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "Creature.hpp"

class Team
{
private:
	Creature* creatures[6];
public:
	Team()
	{
        for(int i = 0; i != 6; i++)
        {
            creatures[i] = nullptr;
        }
		creatures[0] = new Creature("TestBug");
	}
    Creature* getCreature(int index)
    {
        return creatures[index];
    }
    ~Team()
    {
        for(int i = 0; i != 6; i++)
        {
            if(creatures[i] == nullptr)
            {
                delete creatures[i];
            }
        }
    }
};