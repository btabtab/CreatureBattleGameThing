#pragma once
#include <vector>
#include <string>
#include <iostream>


class Stats
{
	private:
	
	int current_health, max_health;
	int attack, defense;
	int special_attack, special_defense;

	public:
	Stats()
	{
		current_health = 5;
		max_health = 5;
		attack = 5;
		defense = 5;
		special_attack = 5;
		special_defense = 5;
	}
	std::vector<int> getStatsAsVector()
	{
		return
		{
			current_health,
			max_health,
			attack,
			defense,
			special_attack,
			special_defense,
		};
	}

	static std::vector<std::string> getStatsNamesAsVector()
	{
		return
		{
			"current_health",
			"max_health",
			"attack",
			"defense",
			"special_attack",
			"special_defense"
		};
	}
	int getCurrentHealth()	{ return current_health; }
	int getHealth()			{ return max_health; }
	int getAttack()			{ return attack; }
	int getDefense()		{ return defense; }
	int getSpecialAttack()	{ return special_attack; }
	int getSpecialDefense()	{ return special_defense; }

	void setCurrentHealth(int new_value)	{ current_health = new_value; }
	void setHealth(int new_value)			{ max_health = new_value; }
	void setAttack(int new_value)			{ attack = new_value; }
	void setDefense(int new_value)			{ defense = new_value; }
	void setSpecialAttack(int new_value)	{ special_attack = new_value; }
	void setSpecialDefense(int new_value)	{ special_defense = new_value; }

	void alterHealth(int amount_to_alter)
	{
		current_health += amount_to_alter;
		if(current_health < 0)
		{
			current_health = 0;
		}
		if(max_health < current_health)
		{
			current_health = max_health;
		}
	}
};
