/*
	Jonathan Smoley
	CPSC 122, Fall 2021
	December 6, 2021
	PA6 Source File
	This program is a Battle Simulator
		between two players.
*/

#include "PA6_BattleHeader_jsmoley.h"

int main(void)
{
	// seed random number generator (before use in class(es))
	srand(time(0));

	// local variable declaration block
	int turn = 0;
	bool hit = false;
	string winner = "";
	InventoryItem item;
	Human p1("Joe");
	Ranger p2("Aragorn");

	// fill inventory with random items
	p1.inventoryTasks();
	p2.inventoryTasks();

	// welcome user
	printWelcome();

	// print player info
	cout << "The first participant is:\n" << endl;
	p1.printPlayerInfo();

	cout << "The second participant is:\n" << endl;
	p2.printPlayerInfo();

	// Battle!
	cout << "Let the battle begin!\n" << endl;

	// take attack turns until health is out for one fighter
	while(true)
	{
		// track which round this is in the battle
		turn++;

		// check of a player's health is all gone
		if(p1.getHealth() <= 0 || p2.getHealth() <= 0)
		{
			break;
		}
		else if(p1.getHealth() >= 0 || p2.getHealth() >= 0)
		{
			// display player stats before each turn
			p1.Player::printBattleCard(p1, p2, turn);

			// player 1 attacks player 2
			item = p1.battle();

			// run hit chance
			hit = p1.attackPlayerSuccess(p1, p2);

			// check if attack hit
			if(hit)
			{
				cout << p1.getName() << " attacks " << p2.getName() << " with a(n)" << item.weaponName << "!"
					<< " ...hits for " << (item.damage * p1.getMultiplier()) << "!" << endl;
				p2.setHealth(p2.getHealth() - (item.damage * p1.getMultiplier()));
				p1.setExperience(p1.getExperience() + (item.damage * p1.getMultiplier()));
			}
			else
			{
				cout << p1.getName() << " attacks " << p2.getName() << " with a(n)" << item.weaponName << "!"
					<< " ...misses!" << endl;
			}

			// player 2 attacks player 1
			item = p2.battle();

			// run hit chance
			hit = p2.attackPlayerSuccess(p2, p1);

			// check if attack hit
			if(hit)
			{
				cout << p2.getName() << " attacks " << p1.getName() << " with a(n)" << item.weaponName << "!"
					<< " ...hits for " << (item.damage * p2.getMultiplier()) << "!" << endl;
				p1.setHealth(p1.getHealth() - (item.damage * p2.getMultiplier()));
				p2.setExperience(p2.getExperience() + (item.damage * p2.getMultiplier()));
			}
			else
			{
				cout << p2.getName() << " attacks " << p1.getName() << " with a(n)" << item.weaponName << "!"
					<< " ...misses!" << endl;
			}

			cout << endl; // space out turns
		}
	}

	// find winner
	winner = findWinner(p1, p2);
	cout << winner << " wins!\n" << endl;

	// print ending player info
	cout << "Ending Info:\n" << endl;
	p1.printPlayerInfo();
	p2.printPlayerInfo();

	return 0;
}
