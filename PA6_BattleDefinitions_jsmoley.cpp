/*
	Jonathan Smoley
	CPSC 122, Fall 2021
	December 6, 2021
	PA6 Source File
	This file is the function definitions file
    	for the PA6 Battle Simulator.
*/

#include "PA6_BattleHeader_jsmoley.h"

// define the static member variables
int Player::numPlayers = 0;
vector<int> Player::playerIds = {0};

// non-class functions

/*************************************************************
* Function: printWelcome() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function prints a welcome message.
* Input parameters: N/A
* Returns: N/A
* Pre: nothing in console
* Post: this message is printed to the console
*************************************************************/
void printWelcome(void)
{
	cout << "Welcome to the battle arena!" << endl;
	cout << "Today we will witness a battle between two Humans; one of the 21st Century and one of Tolkien's Third Age!" << endl;
}

/*************************************************************
* Function: findWinner() 
* Date Created: 12/6/21 
* Date Last Modified: 12/6/21
* Description: This function compares the health of both 
* 	players to determine a winner.
* Input parameters: first player, second player
* Returns: name of winner
* Pre: fighting is over
* Post: winner has been found
*************************************************************/
string findWinner(Human &p1, Ranger &p2)
{
	if (p1.getHealth() > p2.getHealth())
	{
		return p1.getName();
	}
	else if (p1.getHealth() < p2.getHealth())
	{
		return p2.getName();
	}
	else
	{
		return "No one";
	}
}

// base class functions

/*************************************************************
* Function: generateRandomStat() 
* Date Created: 12/3/21 
* Date Last Modified: 12/3/21
* Description: This function utilizes the random number
* 	generator and a min and max value to provide a random
* 	stat value.
* Input parameters: ints for min and max values
* Returns: a random integer between the min and max values
* Pre: player stat needs to be initialized
* Post: random value is assigned to the player stat
*************************************************************/
int Player::generateRandomStat(int min, int max) const
{
	return rand() % (max - min) + min;
}

/*************************************************************
* Function: playerIdIsInList() 
* Date Created: 12/3/21 
* Date Last Modified: 12/3/21
* Description: This function checks to see if a playerId has
* 	already been assigned to a player.
* Input parameters: id to check
* Returns: true if playerId is in list, false if not
* Pre: new ID has been made and needs to be checked
* Post: Id is determined to be either in list or not
*************************************************************/
bool Player::playerIdIsInList(int id)
{
	for (int i = 0; i < playerIds.size(); i++)
	{
		if (playerIds[i] == id)
		{
			return true;
		}
	}
	return false;
}

/*************************************************************
* Function: generatePlayerId() 
* Date Created: 12/3/21 
* Date Last Modified: 12/3/21
* Description: This function utilizes the cstdlib to randomly
* 	choose a value for the player's ID that is less than 1000.
* Input parameters: N/A
* Returns: int for playerId
* Pre: new player in need of ID
* Post: player's ID is generated
*************************************************************/
int Player::generatePlayerId(void) const
{
	int id = rand() % MAX_ID_VALUE;
	while(playerIdIsInList(id))
	{
		id = rand() % MAX_ID_VALUE;
	}
	playerIds.push_back(id);
	return id;
}

/*************************************************************
* Function: ~Player() 
* Date Created: 12/3/21 
* Date Last Modified: 12/3/21
* Description: This is the destructor for the Player class.
* Input parameters: N/A
* Returns: N/A
* Pre: object of derived Player class exists
* Post: said object is destroyed
*************************************************************/
Player::~Player()
{
	// does destructor stuff
	playerInventory.empty();
}

// inherited class 1 functions

/*************************************************************
* Function: inventoryTask() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function performs the inventory related
*   tasks.
* Input parameters: N/A
* Returns: N/A
* Pre: player's inventory is declared but empty
* Post: player's inventory now contains items and items shown
*************************************************************/
void Human::inventoryTasks(void)
{
	InventoryItem item;

	// fill the stack with items
	for (int i = 0; i < 11; i++)
	{
		
		item = possibleItems[rand() % possibleItems.size()];
		playerInventory.push(item);
	}

    cout << "Filled the list..." << endl;
    cout << "Demonstrating printing the list..." << endl;
    playerInventory.displayAllItems(playerInventory.getTop());
    cout << "Size: " << playerInventory.size() << "\n" << endl;

	playerInventory.pop(item);

    cout << "Demonstrating removing an item from the list..." << endl;
    playerInventory.displayAllItems(playerInventory.getTop());
    cout << "Size: " << playerInventory.size() << endl;
    cout << endl;
}

/*************************************************************
* Function: initializePlayer() 
* Date Created: 12/3/21 
* Date Last Modified: 12/3/21
* Description: This function sets the player's subclass, name,
*	ID, health, and experience given the derived class 'Human'.
* Input parameters: name of player
* Returns: N/A
* Pre: new player is declared
* Post: player has been given stats
*************************************************************/
void Human::initializePlayer(string newName)
{
	subclass = "Human";
	this->setName(newName);
	playerId = generatePlayerId();
	health = generateRandomStat(50, 150);
	experience = 0;
	strength = generateRandomStat(1, 10);
	multiplier = 1;
}

/*************************************************************
* Function: printPlayerClassInfo() 
* Date Created: 12/3/21 
* Date Last Modified: 12/3/21
* Description: This function prints any extra stats applied by
*	the object's class.
* Input parameters: N/A
* Returns: N/A
* Pre: a class object holds stats beyond printPlayerInfo()
* Post: extra stats are printed
*************************************************************/
void Human::printPlayerClassInfo(void) const
{
	cout << "Strength: " << strength << endl;
}

/*************************************************************
* Function: ~Human() 
* Date Created: 12/3/21 
* Date Last Modified: 12/3/21
* Description: This is the desructor for the Human class.
* Input parameters: N/A
* Returns: N/A
* Pre: object of class type 'Human' exists
* Post: said object no longer exists
*************************************************************/
Human::~Human()
{
	// destructor stuff
}

// inherited class 2 functions

/*************************************************************
* Function: inventoryTask() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function performs the inventory related
*   tasks.
* Input parameters: N/A
* Returns: N/A
* Pre: player's inventory is declared but empty
* Post: player's inventory now contains items and items shown
*************************************************************/
void Ranger::inventoryTasks(void)
{
    // fill the stack with items
    for (int i = 0; i < 10; i++)
    {
        InventoryItem item;
        item = possibleItems[rand() % (possibleItems.size())];
        playerInventory.push(item);
    }
}

/*************************************************************
* Function: initializePlayer() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function sets stats for the 1.2 class.
* Input parameters: name of fighter
* Returns: N/A
* Pre: fighter exists but is not initialized
* Post: fighter has stats
*************************************************************/
void Ranger::initializePlayer(string newName)
{
	Human::initializePlayer(newName);
	subclass = "Ranger";
	dexterity = generateRandomStat(10, 20);
	multiplier = 1.2;
	Human::setStrength(getStrength() * multiplier);
	Human::setHealth(getHealth() * multiplier);
}

/*************************************************************
* Function: initializePlayer() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function prints stats related to the 1.2
* 	class player.
* Input parameters: N/A
* Returns: N/A
* Pre: fighter has new stats
* Post: fighter's stats are printed
*************************************************************/
void Ranger::printPlayerClassInfo(void) const
{
	Human::printPlayerClassInfo();
	cout << "Dexterity: " << dexterity << endl;
	cout << "Damage Multiplier: " << multiplier << endl;
}

/*************************************************************
* Function: ~Ranger() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This is the destructor for the Ranger class.
* Returns: N/A
* Pre: Ranger class player exists
* Post: said player is destroyed
*************************************************************/
Ranger::~Ranger()
{
	// destructor stuff
}

// player inventory class functions

/*************************************************************
* Function: PlayerInventory() 
* Date Created: 12/1/21 
* Date Last Modified: 12/3/21
* Description: This is the constructor for the PlayerInventory
* 	class.
* Input parameters: size of stack
* Returns: N/A
* Pre: No inventory object exists
* Post: new inventory object is created
*************************************************************/
PlayerInventory::PlayerInventory()
{
	// initialize the stack
	topPtr = nullptr;
}

/*************************************************************
* Function: ~PlayerInventory() 
* Date Created: 12/1/21 
* Date Last Modified: 12/5/21
* Description: This is the destructor for the PlayerInventory
* 	class.
* Input parameters: N/A
* Returns: N/A
* Pre: Inventory object exists
* Post: Inventory object is destroyed
*************************************************************/
PlayerInventory::~PlayerInventory()
{
	// delete the stack
	Stack *nodePtr = nullptr, *nextNode = nullptr;

	nodePtr = topPtr;

	while(nodePtr != nullptr)
	{
		nodePtr = nodePtr->nextPtr;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

/*************************************************************
* Function: push() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function pushes a new item onto the top
* 	of the stack.
* Input parameters: item to add on top
* Returns: N/A
* Pre: Inventory is length n
* Post: Inventory is length n+1
*************************************************************/
void PlayerInventory::push(InventoryItem item)
{
	Stack *newNode = new Stack;
    newNode->weaponName = item.weaponName;
    newNode->damage = item.damage;

    if (isEmpty() == true)
    {
        topPtr = newNode;
        newNode->nextPtr = nullptr;
    }
    else
    {
        newNode->nextPtr = topPtr;
        topPtr = newNode;
    }
}

/*************************************************************
* Function: pop() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function removes the top items from the
* 	stack.
* Input parameters: item to remove
* Returns: N/A
* Pre: Inventory is length n
* Post: Inventory is length n-1
*************************************************************/
void PlayerInventory::pop(InventoryItem &item)
{
	Stack *tempPtr = nullptr;

	if(!isEmpty())
	{
		item.weaponName = topPtr->weaponName;
		item.damage = topPtr->damage;
		tempPtr = topPtr->nextPtr;
		delete topPtr;
		topPtr = tempPtr;
	}
}

/*************************************************************
* Function: displayAllItems() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function displays all items in the stack
* 	recursively.
* Input parameters: N/A
* Returns: N/A
* Pre: Stack object exists but is not passed as an argument
* Post: Contents of the Stack are displayed
*************************************************************/
void PlayerInventory::displayAllItems(Stack *nodePtr)
{
	// displaying items in the stack
	if (nodePtr != nullptr)
	{
        displayAllItems(nodePtr->nextPtr);
		cout << "Weapon: " << nodePtr->weaponName 
			<< " - " << nodePtr->damage << endl;
	}
}

/*************************************************************
* Function: empty() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function removed items from the list.
* Input parameters: N/A
* Returns: N/A
* Pre: Stack object contains items
* Post: Stack object is empty
*************************************************************/
void PlayerInventory::empty()
{
	// delete the stack
	Stack *nodePtr = nullptr, *nextNode = nullptr;

	nodePtr = topPtr;

	while(nodePtr != nullptr)
	{
		nextNode = nodePtr->nextPtr;
		// nodePtr = nodePtr->nextPtr;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

/*************************************************************
* Function: size() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function finds the size of the stack and
* 	returns it.
* Input parameters: N/A
* Returns: int for size of stack
* Pre: stack contains a # of items
* Post: # of items in stack is returned
*************************************************************/
int PlayerInventory::size()
{
	Stack *nodePtr = nullptr;
	int size = 0;

	nodePtr = topPtr;

	while(nodePtr != nullptr)
	{
		size++;
		nodePtr = nodePtr->nextPtr;
	}

	return size;
}

/*************************************************************
* Function: isEmpty() 
* Date Created: 12/5/21 
* Date Last Modified: 12/5/21
* Description: This function checks to see if the stack is
*   empty.
* Input parameters: N/A
* Returns: bool for if stack is empty or full
* Pre: stack is passed in
* Post: return true if stack is empty, false if not
*************************************************************/
bool PlayerInventory::isEmpty()
{
    if (topPtr == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// battle functions(s)

/*************************************************************
* Function: battleMove() 
* Date Created: 12/6/21 
* Date Last Modified: 12/6/21
* Description: This function grabs an item from the inventory
* 	stack for the Human to "use".
* Input parameters: N/A
* Returns: class pointer to the item
* Pre: fighter object needs an item to "use"
* Post: next item in list is passed into the fighter's use
*************************************************************/
InventoryItem Human::battle()
{
	InventoryItem item;

	playerInventory.pop(item);

	return item;

	// get the item from the stack
	// for (int i = 0; i < index; i++)
	// {
	// 	item = playerInventory.pop(playerInventory.getTop());
	// }

	// // player hit attempt
	// cout << attacker.getName() << " attacks " << defender.getName() << " with a(n)" << item.weaponName << "!";

	// // check if the attack hit; if so, subtract one's health and add to the other's experience
	// if(attacker.attackPlayerSuccess(attacker, defender))
	// {
	// 	cout << " ...hits for " << item.damage << "!" << endl;
	// 	defender.setHealth(defender.getHealth() - (item.damage * attacker.getMultiplier()));
	// 	attacker.setExperience(attacker.getExperience() + (item.damage * attacker.getMultiplier()));
	// }
	// else
	// {
	// 	cout << " ...misses!" << endl;
	// }

	// playerInventory.push(item);
}
