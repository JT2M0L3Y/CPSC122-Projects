/*
	Jonathan Smoley
	CPSC 122, Fall 2021
	December 6, 2021
	PA6 Source File
	This is the header file for the
    PA6 battle simulator.
*/

#ifndef PA6_BATTLEHEADER_JSMOLEY_H
#define PA6_BATTLEHEADER_JSMOLEY_H

#include <iostream> //need for IO
#include <string> //need for string data type and member functions
#include <cstdlib> //need for random
#include <ctime> //need for random
#include <vector> //need for vector data type
#include <iomanip> //need to format output

using namespace std;

// Global constant to set upper limit on number of playerIds generated
const int MAX_ID_VALUE = 1000;

// This struct is used to populate possibleItems.
struct InventoryItem
{
	string weaponName;
	int damage;
};

//Global CONSTANT variable.
const vector<InventoryItem> possibleItems
{
	{"Sword", 20}, {"Axe", 10},
	{"Spear", 7}, {"Bow", 15},
	{"Rock", 3}, {"Torch", 5},
	{"Fork", 1}, {"Book", 0}
};

// Class for your inventory (stack structure)
class PlayerInventory
{
private:
	struct Stack
	{
		string weaponName;
		int damage;
		Stack *nextPtr;
	};

	Stack *topPtr;

public:
	PlayerInventory();
	~PlayerInventory();

	void push(InventoryItem item);
	void pop(InventoryItem &item);
	void displayAllItems(Stack *nodePtr); // recursive
	void empty();
	int size();
    bool isEmpty();

	// getter(s)
    Stack* getTop(void) { return topPtr; }
};

//Abstract Base Class
class Player
{
private:
	//static member variable keeping track of the number of players generated
    static int numPlayers;
	//static list of playerIds generated.
	static vector<int> playerIds;

protected:
	string subclass;
	string name;
	int playerId;
	int health;
	int experience;
	double multiplier;

	// inventory STACK
	PlayerInventory playerInventory;

	// playerId setter
	void setPlayerId(int id) { playerId = id; }

	// stat generator for health primarily
	int generateRandomStat(int min, int max) const;

	// check if PID exists already
	static bool playerIdIsInList(int id);

	// randomly produce a playerId
	int generatePlayerId(void) const;

public:
	// Default constructor
	Player() 
	{
		subclass = "Player";
		name = "";
		playerId = -1;
		health = -1;
		experience = 0;
		multiplier = 1.0;
		
		// increment # of players
		numPlayers++;
	}

	// Destructor
	~Player();

	// accessors/getters and mutators/setters
	void setName(string newName) { name = newName; }
	string getName(void) const { return name; };
	void setHealth(int h) { health = h; }
	int getHealth(void) const { return health; }
	int getPlayerId(void) const { return playerId; }
	void setExperience(int exp) { experience = exp; }
	int getExperience(void) const { return experience; }

	// Pure Virtual Functions
	// initializes a player of given name with randomly allocated stats
	virtual void initializePlayer(string newName) = 0;
	virtual void printPlayerClassInfo(void) const = 0; // prints class specific info

	//Virtual Functions
	virtual double getMultiplier(void) { return multiplier; } const

	// print all of a player's info
	virtual void printPlayerInfo(void) final
	{
		string skull = "\n    _____\n   /     \\\n  | () () |\n   \\  ^  /\n    |||||\n";
		string tombstone = "\n       ,-=-.\n      /  +  \\\n      | ~~~ |\n      |R.I.P|\n      |_____| \n";

		string healthValue = this->health > 0 ? to_string(this->health) : tombstone; //"~RIP~"
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>|PID:" << this->playerId << "|" << endl;
		cout << ">>" << this->name << "'s info" << endl;
		cout << "Health: " << healthValue << endl;
		cout << "Experience: " << this->experience << endl;
		cout << "---------------------------------" << endl;
		cout << "Class: " << this->subclass << endl;
		printPlayerClassInfo();
		cout << "_________________________________" << endl;
		cout << endl;
	}

	// Template Functions
	// print header for battle round's card
	template <class T1, class T2>
	static void printBattleCard(const T1& p1, const T2& p2, int turn)
	{
		cout << "|------- Turn " << turn << " -------|" << endl;
		cout << p1.getName() << "'s Health: " << p1.getHealth() 
			<< " - " << p2.getName() << "'s Health: " << p2.getHealth() 
			<< endl;
	}

	// check for player attack result
	template <class T1, class T2>
	bool attackPlayerSuccess(T1& p1, const T2& p2)
	{
		int odds = rand() % 10;
    	bool success = false; 

    	if (p2.subclass == "Ranger" && odds <= 6)
    	{
        	success = true; 
    	}
    	else if(p1.subclass == "Human" && odds <= 4)
    	{
        	success = true;
    	}
		
		return success;
	}

    // initialize playerInventory
	virtual void inventoryTasks(void) = 0;
};

// inherited class 1
class Human : public Player
{
private:
	int strength;
public:
	Human(string name) : Player()
	{
		initializePlayer(name);
	}
	~Human();

	void initializePlayer(string newName) override;
	void printPlayerClassInfo(void) const override;

	void setStrength(int s) { strength = s; }
	int getStrength(void) const { return strength; }

    void inventoryTasks(void) override;
	
	InventoryItem battle();
};

// inherited class 1.2
class Ranger : public Human
{
private:
	int dexterity;
public:
	Ranger(string name) : Human(name)
	{
		initializePlayer(name);
	}
	~Ranger();

	void initializePlayer(string newName) override;
	void printPlayerClassInfo(void) const override;
	double getMultiplier(void) override { return multiplier; }

	int getDexterity(void) const { return dexterity; }

    void inventoryTasks(void) override;
};

// function prototypes
void printWelcome(void);

string findWinner(Human &p1, Ranger &p2);

#endif