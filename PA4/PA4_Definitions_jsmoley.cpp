/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 27, 2021
Assignment: PA4
Description: This is the definitions file
    for PA4, where function prototypes are
    defined for use in the source file.
Notes: I attempted the bonus in the header file!
*/

#include "PA4_Header_jsmoley.h"

/*************************************************************
* Function: PlayerCard()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: default constructor for the PlayerCard class,
*   calls the overloaded function for initialization
* Returns: N/A
* Pre: N/A
* Post: new PlayerCard object is initialized
*************************************************************/
PlayerCard::PlayerCard() : PlayerCard("", -1)
{
    // constructor delegation
}

/*************************************************************
* Function: PlayerCard()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: overloaded constructor that is used for 
*   constructor delegation in the default constructor to 
*   initialize a PlayerCard object
* Returns: N/A
* Pre: N/A
* Post: new PlayerCard object is initialized
*************************************************************/
PlayerCard::PlayerCard(string name, int id = -1) 
{
    playerId = id;
    playerName = name;
    totalScore = -1;
    gamesPlayed = -1;
    avgScore = -1.0;
}

/*************************************************************
* Function: ~PlayerCard()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: destructor/deconstructor for the PlayerCard
*   class, clears attributes of the PlayerCard object
* Returns: N/A
* Pre: N/A
* Post: N/A
*************************************************************/
PlayerCard::~PlayerCard()
{
    // clear data members (attributes) of current object
    // only has contents if DMA occurs
}

/*************************************************************
* Function: setPlayerId()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: private setter for the playerId attribute
* Input parameters: id to assign to playerId
* Returns: N/A
* Pre: new id is provided
* Post: new id is assigned to the playerId member attribute
*************************************************************/
void PlayerCard::setPlayerId(int id)
{
    playerId = id; 
}

/*************************************************************
* Function: setPlayerName()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: initialize the playerName attribute to some
*   string value
* Input parameters: N/A
* Returns: N/A
* Pre: N/A
* Post: initialized the current PlayerCard object's playerName
*   attribute
*************************************************************/
void PlayerCard::setPlayerName(string name)
{
    playerName = name;
}

/*************************************************************
* Function: setTotalScore()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: initialize a value to the totalScore attribute
* Input parameters: N/A
* Returns: N/A
* Pre: N/A
* Post: initialized the totalScore attribute of the current
*   PlayerCard object to have value
*************************************************************/
void PlayerCard::setTotalScore(int tot)
{
    totalScore = tot;
}

/*************************************************************
* Function: setGamesPlayed()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: initialize the gamesPlayed attribute with value
* Input parameters: N/A
* Returns: N/A
* Pre: N/A
* Post: current player card's gamesPlayed attribute is 
*   initialized
*************************************************************/
void PlayerCard::setGamesPlayed(int games)
{
    gamesPlayed = games;
}

/*************************************************************
* Function: setAvgScore()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: private setter for the avgScore attribute
* Input parameters: average to assign to avgScore
* Returns: N/A
* Pre: new average is calculated
* Post: new average is assigned to avgScore member attribute
*************************************************************/
void PlayerCard::setAvgScore(double avg) 
{
    avgScore = avg;
}

/*************************************************************
* Function: generatePlayerId()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: randomly generate player's ID, call ID setter
* Input parameters: N/A
* Returns: N/A
* Pre: N/A
* Post: playerId attribute is referenced and updated with
*   new random ID value
*************************************************************/
void PlayerCard::generatePlayerId(void)
{
    // randomly generated ID between 1000 and 9999
    int randomId = 1000 + rand() % ((9999 + 1) - 1000);

    setPlayerId(randomId);
}

/*************************************************************
* Function: generatePlayerId()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: overloaded function to use a provided ID value
* Input parameters: ID to update the playerId attibute with
* Returns: N/A
* Pre: ID is read in from the file and copied in at function
*   call.
* Post: playerId attribute is referenced and updated with
*   ID value from the file.
*************************************************************/
void PlayerCard::generatePlayerId(int id)
{
    setPlayerId(id);
}

/*************************************************************
* Function: updateAverageScore()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: calculate present average score using class
*   attributes, accounts for integer division by 0
* Input parameters: N/A
* Returns: N/A
* Pre: Call the private setter for avgScore and reference
*   totalScore and gamesPlayed values.
* Post: Changed the avgScore value using new totalScore
*   and gamesPlayed values to do so.
*************************************************************/
void PlayerCard::updateAverageScore(void)
{
    double avg = 0.0;
    int tot = getTotalScore(); // call to totalScore attribute
    int games = getGamesPlayed(); // call to gamesPlayed attribute

    if(games == 0) // account for division by 0
    {
        avg = 0.0;
    }
    else
    {
        avg = double(tot) / games;
    }

    // calls a private setter
    setAvgScore(avg);
}

/*************************************************************
* Function: fileAverageScore()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: access the avgScore attribute for updating,
*   [THIS IS TECHNICALLY AN OVERLOADED 'updateAverageScore()']
* Input parameters: new average to add
* Returns: N/A
* Pre: Call the private setter for avgScore and pass in new 
*   average value
* Post: Changed the avgScore value to be past player's average
*************************************************************/
void PlayerCard::fileAverageScore(double avg)
{
    // calls a private setter
    setAvgScore(avg);
}

/*************************************************************
* Function: importPlayerScoreCards()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: Reads in rows of player data from the file
*   and store them in a vector of PlayerCard objects.
* Input parameters: file access variable, vector to populate
* Returns: PlayerCard vector
* Pre: vector is empty and file has not been read from
* Post: file access is done and vector is populated
*************************************************************/
void importPlayerScoreCards(ifstream& inputFile, vector<PlayerCard>& scoreCards)
{
    PlayerCard tempPlayer;
    int playerCount = 0;
    
    while(!inputFile.eof())
    {
        int tempInt = 0;
        string firstName = "", lastName = "", fullName = "";
        double tempDouble = 0.0;
        
        // increment number of players (really size of vector)
        ++playerCount;
        
        // read in player card data for each player in file
        inputFile >> tempInt;
        
        // check if empty line has been reached
        if(inputFile.fail())
        {
            break;
        }
        else
        {
            // add a new object to the vector
            scoreCards.push_back(tempPlayer);

            // update id attribute with current player's id
            scoreCards.at(playerCount - 1).generatePlayerId(tempInt);

            // take in first & last name, concatenate into 1 string, and update playerName attribute
            inputFile >> firstName;
            inputFile >> lastName;
            fullName = firstName + " " + lastName;
            scoreCards.at(playerCount - 1).setPlayerName(fullName);

            // update score, games #, and average attributes with current player data
            inputFile >> tempInt;
            scoreCards.at(playerCount - 1).setTotalScore(tempInt);
            inputFile >> tempInt;
            scoreCards.at(playerCount - 1).setGamesPlayed(tempInt);
            inputFile >> tempDouble;
            scoreCards.at(playerCount - 1).fileAverageScore(tempDouble);
        }
    }
}

/*************************************************************
* Function: fileManagement()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: open or close file(s)
* Input parameters: file reference
* Returns: status of file operation
* Pre: file in one state (open/closed)
* Post: file in another state (open/closed)
*************************************************************/
bool fileManagement(ifstream& inputFile, string filename)
{
    // check if file is open or closed and change the state
    if(inputFile.is_open() == false)
    {
        inputFile.open(filename);

        if(inputFile.is_open() == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        inputFile.close();

        if(inputFile.is_open() == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/*************************************************************
* Function: welcomeMessage()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: prints the welcome message to the console
* Input parameters: N/A
* Returns: N/A
* Pre: N/A
* Post: content printed to console
*************************************************************/
void welcomeMessage(void)
{
    // simple output statements to the console at start of game
    cout << "\nWelcome to the game of darts!" << endl;
    cout << "It's completely skill-based and not random luck, I promise!" << endl;
    cout << "...\n*wink*" << endl;
}

/*************************************************************
* Function: initializePlayerScoreCard()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: Initializes a dart player card by calling
*   public methods of the PlayerCard class
* Input parameters: pointer to current PlayerCard
* Returns: N/A
* Pre: "empty" player card object to fill
* Post: player card object is now filled
*************************************************************/
void initializePlayerScoreCard(PlayerCard* card)
{
    string name = "";

    // generate a random ID for the player
    (*card).generatePlayerId();

    // ask user for a player name
    cout << "Please enter a player name (first and last separated by a space):" << endl;

    // grab the entire name (the line) and insert into the playerName attribute of card
    getline(cin, name);
    (*card).setPlayerName(name);

    // initialize running total and games played
    (*card).setTotalScore(0);
    (*card).setGamesPlayed(0);

    // initialize average score with new score and game # values
    (*card).updateAverageScore();
}

/*************************************************************
* Function: printPlayerScoreCard()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: Prints the contents of the player card
*   in a formattted manner if a player has actually played.
* Input parameters: constant reference to the player card 
*   object
* Returns: N/A
* Pre: newly populated object is passed in
* Post: nicely formatted player card is output
*************************************************************/
void printPlayerScoreCard(const PlayerCard& card)
{
    // output game card
    cout << "-----------------------|PID:" << card.getPlayerId()
        << "|" << endl;
    cout << card.getPlayerName() << "'s Score Card" << endl;
    cout << "---------------------------------" << endl;
    cout << "Games Played: " << card.getGamesPlayed() << endl;
    cout << "Running Score: " << card.getTotalScore() << endl;
    
    // check if any games have been played (for the average calculation)
    if(card.getGamesPlayed() > 0)
    {
        cout << "Average Score: " << fixed << setprecision(2) 
            << card.getAvgScore() << endl;
    }
    else
    {
        cout << "No games played" << endl;
    }
    cout << "---------------------------------" << endl;
}

/*************************************************************
* Function: dartsRound()
* Date Created: 10/27/21 
* Date Last Modified: 10/27/21
* Description: This function runs the actual game part where
*   a dart is "thrown".
* Input parameters: new PlayerCard object for user
* Returns: user's decision on whether or not to throw again
* Pre: user wanted to take another thrown of a dart
* Post: user's card is modified to match their new score(s)
*************************************************************/
char dartsRound(PlayerCard* card)
{
    char option = ' ';
    int hit = 0;

    // output each time a throw is made
    cout << "You throw a dart!" << endl;
    hit = rand() % 10; // the throw

    // notify player of the result
    if(hit < 11 && hit > 5)
    {
        cout << "Great Job! You hit a " << hit << ". That was a good throw!" << endl;
    }
    else if(hit < 6 && hit > 0)
    {
        cout << "Not too bad, you hit a " << hit << ". Maybe give it another go." << endl;
    }
    else
    {
        cout << "Here's the thing... you missed." << endl;
    }

    // modify the player's card values based on the hit
    (*card).setTotalScore((*card).getTotalScore() + hit);
    (*card).setGamesPlayed((*card).getGamesPlayed() + 1);
    (*card).updateAverageScore();

    // ask user thoughts on playing again
    cout << "Keep playing? (y/n) ";
    cin >> option;

    return option;
}

/*************************************************************
* Function: showPreviousCards()
* Date Created: 10/13/21 
* Date Last Modified: 10/14/21
* Description: output the data from the file in player card
*   format like the new player's
* Input parameters: vector of player card structs
* Returns: N/A
* Pre: vector hold data to be output in a vector of structs
* Post: console output is formatted and shown to user
*************************************************************/
void showPreviousCards(vector<PlayerCard> cards)
{
    for(int i = 0; i < cards.size(); i++)
        {
            printPlayerScoreCard(cards.at(i));
        }
}

/*************************************************************
* Function: choiceAnalysis()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: Evaluates which choice the user took.
* Input parameters: character representing that choice
* Returns: status of the choice (since y/n is boolean too)
* Pre: choice given
* Post: boolean attribute tells the program to continue/end
*************************************************************/
bool choiceAnalysis(char ch)
{
    bool status;

    if(ch == 'n')
        {
            status = false;
        }
    else if(ch == 'y')
        {
            status = true;
        }
    
    return status;
}
